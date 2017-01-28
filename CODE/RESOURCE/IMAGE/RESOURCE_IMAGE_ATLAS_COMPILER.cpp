//
//  RESOURCE_IMAGE_ATLAS_COMPILER.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 22/06/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "RESOURCE_IMAGE_ATLAS_COMPILER.h"
#include "RESOURCE_IMAGE.h"
#include "RESOURCE_IMAGE_PNG_WRITER.h"
#include "GRAPHIC_TEXTURE_ATLAS.h"
#include "CORE_DATA_STREAM.h"
#include "CORE_MEMORY.h"

RESOURCE_IMAGE_ATLAS_COMPILER::RESOURCE_IMAGE_ATLAS_COMPILER() :
    SortedImageTable(),
    RootNode( NULL ) {
    
}

RESOURCE_IMAGE_ATLAS_COMPILER::~RESOURCE_IMAGE_ATLAS_COMPILER() {

}

bool SortFunction( RESOURCE_IMAGE * lhs, RESOURCE_IMAGE * rhs ) {
    
    return lhs->GetImageInfo().Height * lhs->GetImageInfo().Width > rhs->GetImageInfo().Height * rhs->GetImageInfo().Width;
}

/**
 * @see http://www.blackpawn.com/texts/lightmaps/default.html
 */
RESOURCE_IMAGE_ATLAS_COMPILER::NODE * RESOURCE_IMAGE_ATLAS_COMPILER::NODE::Insert( RESOURCE_IMAGE * img ) {

    if ( Childs[0] != NULL ) {
        
        RESOURCE_IMAGE_ATLAS_COMPILER::NODE * new_node = Childs[0]->Insert( img );
        
        if ( new_node != NULL ) {
            
            new_node->Image = img;
            
            return new_node;
        }
        
        return Childs[1]->Insert( img );
    }
    else {
        
        if ( Image != NULL ) {
            
            return NULL;
        }
        
        if ( Rec.Size[ 0 ] < img->GetImageInfo().Width || Rec.Size[ 1 ] < img->GetImageInfo().Height ) {
            
            return NULL;
        }
        else if(  Rec.Size[ 0 ] == img->GetImageInfo().Width && Rec.Size[ 1 ] == img->GetImageInfo().Height ) {
            
            Image = img;
            
            return this;
        }
        else {
            
            Childs[ 0 ] = new RESOURCE_IMAGE_ATLAS_COMPILER::NODE();
            Childs[ 1 ] = new RESOURCE_IMAGE_ATLAS_COMPILER::NODE();
            
            int dw = Rec.Size[ 0 ] - img->GetImageInfo().Width;
            int dh = Rec.Size[ 1 ] - img->GetImageInfo().Height;
            
            CORE_MATH_VECTOR
                center,
                size;
            
            if ( dw > dh ) {
                
                center[0] = Rec.Center[0] - Rec.Size[0] * 0.5f + img->GetImageInfo().Width * 0.5f;
                center[1] = Rec.Center[1];
                
                size[0] = img->GetImageInfo().Width;
                size[1] = Rec.Size[ 1 ];
                
                Childs[0]->Rec.Center = center;
                Childs[0]->Rec.Size = size;
                
                //FIX 001-Atlas +1 px for image center
                center[0] = Rec.Center[0] + Rec.Size[0] * 0.5f - dw * 0.5f + 1;
                center[1] = Rec.Center[1] + 1;
                
                size[0] = dw;
                size[1] = Rec.Size[ 1 ];
                
                Childs[1]->Rec.Center = center;
                Childs[1]->Rec.Size = size;
            }
            else {
                
                center[0] = Rec.Center[0];
                center[1] = Rec.Center[1] - Rec.Size[1] * 0.5f + img->GetImageInfo().Height * 0.5f;
                
                size[0] = Rec.Size[ 0 ];
                size[1] = img->GetImageInfo().Height;
                
                Childs[0]->Rec.Center = center;
                Childs[0]->Rec.Size = size;
                
                //FIX 001-Atlas +1 px for image center
                center[0] = Rec.Center[0] + 1;
                center[1] = Rec.Center[1] + Rec.Size[1] * 0.5f - dh * 0.5f + 1;
                
                size[0] = Rec.Size[ 0 ];
                size[1] = dh;
                
                Childs[1]->Rec.Center = center;
                Childs[1]->Rec.Size = size;
            }
            
            return Childs[0]->Insert( img );
        }
    }
}

/* if we're not a leaf then
(try inserting into first child)
newNode = child[0]->Insert( img )
if newNode != NULL return newNode

(no room, insert into second)
return child[1]->Insert( img )

else

(if there's already a lightmap here, return)
 if imageID != NULL return NULL
 
 (if we're too small, return)
  if img doesn't fit in pnode->rect
  return NULL
  
  (if we're just right, accept)
   if img fits perfectly in pnode->rect
   return pnode
   
   (otherwise, gotta split this node and create some kids)
   pnode->child[0] = new Node
   pnode->child[1] = new Node
   
   (decide which way to split)
   dw = rc.width - img.width
   dh = rc.height - img.height
   
   if dw > dh then
   child[0]->rect = Rectangle(rc.left, rc.top,
                              rc.left+width-1, rc.bottom)
   child[1]->rect = Rectangle(rc.left+width, rc.top,
                              rc.right, rc.bottom)
   else
   child[0]->rect = Rectangle(rc.left, rc.top,
                              rc.right, rc.top+height-1)
   child[1]->rect = Rectangle(rc.left, rc.top+height,
                              rc.right, rc.bottom)
   
   (insert into first child we created)
   return Insert( img, pnode->child[0] )
*/

void RESOURCE_IMAGE_ATLAS_COMPILER::Compile( const char * destination_path, const std::vector< RESOURCE_IMAGE * > & resource_image_table ) {
    
    int
        max_height = 0,
        max_width = 0,
        pixels_total = 0;
    
    SortedImageTable = resource_image_table;
    
    std::sort( SortedImageTable.begin(), SortedImageTable.end(), SortFunction );
    
    for ( int i = 0; i < SortedImageTable.size(); i++ ) {
        
        const GRAPHIC_TEXTURE_INFO & image_info = SortedImageTable[ i ]->GetImageInfo();
        
        if ( max_height < image_info.Height ) {
            
            max_height = image_info.Height;
        }
        
        if ( max_width < image_info.Width ) {
            
            max_width = image_info.Width;
        }
        
        pixels_total += image_info.Width * image_info.Height;
    }
    
    pixels_total += pixels_total * 0.1f;
    
    RootNode = new RESOURCE_IMAGE_ATLAS_COMPILER::NODE;
    
    int side_size = sqrt( ( double ) pixels_total );
    
    side_size--;
    side_size |= side_size >> 1;
    side_size |= side_size >> 2;
    side_size |= side_size >> 4;
    side_size |= side_size >> 8;
    side_size |= side_size >> 16;
    side_size++;
    
    RESOURCE_IMAGE * atlas_texture = new RESOURCE_IMAGE;
    
    atlas_texture->SetImageRawData( CORE_MEMORY_ALLOCATOR::Allocate( side_size * side_size * 4 ) );
    atlas_texture->GetImageInfo().Height = side_size;
    atlas_texture->GetImageInfo().Width = side_size;
    atlas_texture->GetImageInfo().ImageType = GRAPHIC_TEXTURE_IMAGE_TYPE_RGBA;
    atlas_texture->GetImageInfo().PixelSize = 0;
    atlas_texture->GetImageInfo().ColorChannelWidth = 8;
    
    RootNode->Rec.Center = CORE_MATH_VECTOR( side_size * 0.5f, side_size * 0.5f );
    RootNode->Rec.Size = CORE_MATH_VECTOR( side_size, side_size );
    
    GRAPHIC_TEXTURE_ATLAS atlas;
    
    for ( int i = 0; i < SortedImageTable.size(); i++ ) {
        
        NODE * result = RootNode->Insert( SortedImageTable[i] );
        
        if ( result != NULL ) {
            
            atlas_texture->Blit(
                SortedImageTable[i],
                result->Rec.Center[0] - result->Rec.Size[0] * 0.5f,
                result->Rec.Center[1] - result->Rec.Size[1] * 0.5f,
                result->Image->GetImageInfo().Width,
                result->Image->GetImageInfo().Height,
                0 );
            
            CORE_MATH_VECTOR left;
            
            left[0] = (result->Rec.Center[0] - result->Rec.Size[0] * 0.5f) / atlas_texture->GetImageInfo().Width;
            left[1] = (result->Rec.Center[1] - result->Rec.Size[1] * 0.5f) / atlas_texture->GetImageInfo().Height;
            
            CORE_MATH_VECTOR normalized_size;
            
            normalized_size = result->Rec.Size;
            
            normalized_size[0] = result->Rec.Size[0] / atlas_texture->GetImageInfo().Width;
            normalized_size[1] = result->Rec.Size[1] / atlas_texture->GetImageInfo().Height;
            
            atlas.AddTexture( SortedImageTable[i]->GetIdentifier(), normalized_size, left );
        }
        else {
            
            CORE_RUNTIME_Abort();
        }
    }
    
    CORE_DATA_STREAM
        stream( 128 );
    
    stream.Open();
    stream.ResetOffset();
    
    XS_CLASS_SERIALIZER< GRAPHIC_TEXTURE_ATLAS >::Serialize< std::true_type >( atlas, stream );
    
    stream.Close();
    
    char * destination_extention = (char *) CORE_MEMORY_ALLOCATOR_Allocate( strlen( destination_path ) + 4 );

    strcpy(destination_extention, destination_path);
    strcat(destination_extention, ".iax\0" );
    
    FILE * file = fopen( destination_extention, "wb" );
    
    if ( !file ) {
        
        CORE_RUNTIME_Abort();
    }
    
    int bytes_written = (int) fwrite(stream.GetMemoryBuffer(), sizeof( char ), (int)stream.GetOffset(), file );
    
    fclose( file );
    
    if ( bytes_written != stream.GetOffset() ) {
        
        CORE_RUNTIME_Abort();
    }
    
    RESOURCE_IMAGE_PNG_WRITER writer;
    
    char * destination_extention2 = (char *) CORE_MEMORY_ALLOCATOR_Allocate( strlen( destination_path ) + 4 );
    
    strcpy(destination_extention2, destination_path);
    strcat(destination_extention2, ".png" );
    
    writer.Write( destination_extention2, atlas_texture );

	CORE_MEMORY_ALLOCATOR_Free( destination_extention );
	CORE_MEMORY_ALLOCATOR_Free( destination_extention2 );
}
