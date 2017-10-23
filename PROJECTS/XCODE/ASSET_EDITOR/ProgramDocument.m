//
//  ProgramDocument.m
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 6/05/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#import "ProgramDocument.h"
#import "CORE_APPLICATION.h"
#include "CORE_MATH_QUATERNION.h"
#include "CORE_MATH_MATRIX.h"
#include "CORE_MATH_VECTOR.h"
#include "CORE_MATH_RAY.h"
#include "CORE_HELPERS_SCALAR.h"
#include "CORE_MATH_SHAPE.h"
#include "CORE_DATA_STREAM.h"
#include "CORE_ABSTRACT_PROGRAM_LUA.h"
#include "CORE_ABSTRACT_PROGRAM_MANAGER.h"
#include "ScriptEntity.h"
#include "RESOURCE.h"
#include "RESOURCE_IMAGE.h"
#include "RESOURCE_IMAGE_ATLAS_COMPILER.h"
#include "RESOURCE_IMAGE_PNG_LOADER.h"
#include "RESOURCE_IMAGE_PNG_WRITER.h"
#include "CORE_ABSTRACT_PROGRAM_RUNTIME_MANAGER.h"
#include "CORE_DATA_BUFFER.h"
#include "GRAPHIC_OBJECT.h"
#include "GRAPHIC_MESH_MANAGER.h"
#include "GRAPHIC_FONT.h"
#include "GRAPHIC_GLYPH.h"
#include "FONT_EDITOR.h"
#include "ASSET_EDITOR.h"

@interface ProgramDocument () {
    std::vector< RESOURCE_IMAGE *>
        images;
    CORE_FILESYSTEM
        DefaultFileystem;
}
@end

@implementation ProgramDocument

- (instancetype)init {
    self = [super init];
    if (self) {
        // Add your subclass-specific initialization here.
    }
    return self;
}

- (void)makeWindowControllers {
    // Override to return the Storyboard file name of the document.
    
    // Create the File Open Dialog class.
    NSOpenPanel* openDlg = [NSOpenPanel openPanel];
    
    // Enable the selection of files in the dialog.
    [openDlg setTitle:@"Select your starting resource directectory"];
    [openDlg setCanChooseFiles:YES];
    
    
    // Enable the selection of directories in the dialog.
    [openDlg setCanChooseDirectories:YES];
    NSString * DirectoryPath = @"";
    
    // Display the dialog.  If the OK button was pressed,
    // process the files.
    if ( [openDlg runModal] == NSModalResponseOK )
    {
        // Get an array containing the full filenames of all
        // files and directories selected.
        NSArray* files = [openDlg filenames];
        
        DirectoryPath =[files objectAtIndex:0];
        
        NSString * ext = [DirectoryPath pathExtension];
        
        //Project is found
        if ( ext != nil && [ext length] > 0 && [ext isEqualToString:@"pjx"] ) {
            
            
            DirectoryPath = [DirectoryPath stringByDeletingLastPathComponent];
            DirectoryPath = [DirectoryPath stringByAppendingString:@"/"];
            DefaultFileystem.Initialize( [DirectoryPath cStringUsingEncoding:NSASCIIStringEncoding] );
            
            ASSET_EDITOR * editor = (ASSET_EDITOR *) &CORE_APPLICATION::GetApplicationInstance();
            
            CORE_FILESYSTEM_PATH path( [[files objectAtIndex:0] cStringUsingEncoding:NSASCIIStringEncoding]);
            
            editor->Load( path );
        }
        else {
            DirectoryPath = [DirectoryPath stringByAppendingString:@"/"];
            DirectoryPath = [DirectoryPath stringByAppendingString:@"/"];
            DefaultFileystem.Initialize( [DirectoryPath cStringUsingEncoding:NSASCIIStringEncoding] );
        }
    }
    
    CORE_FILESYSTEM::SetDefaultFilesystem( DefaultFileystem );
    
    [self addWindowController:[[NSStoryboard storyboardWithName:@"Main" bundle:nil] instantiateControllerWithIdentifier:@"Document Window Controller"]];
    
    
}

- (NSData *)dataOfType:(NSString *)typeName error:(NSError **)outError {
    // Insert code here to write your document to data of the specified type. If outError != NULL, ensure that you create and set an appropriate error when returning nil.
    // You can also choose to override -fileWrapperOfType:error:, -writeToURL:ofType:error:, or -writeToURL:ofType:forSaveOperation:originalContentsURL:error: instead.
    if (*outError) {
        *outError = [NSError errorWithDomain:NSOSStatusErrorDomain code:unimpErr userInfo:nil];
        
        return nil;
    }
    else {
        
        auto editor = ( (ASSET_EDITOR*) &ASSET_EDITOR::GetApplicationInstance());
        CORE_DATA_STREAM stream;
        editor->Save( stream );
        
        NSData * data = [[NSData alloc] initWithBytes:stream.GetMemoryBuffer() length:stream.GetOffset()];
        
        return data;
    }
}

- (BOOL)readFromData:(NSData *)data ofType:(NSString *)typeName error:(NSError **)outError {
    // Insert code here to read your document from the given data of the specified type. If outError != NULL, ensure that you create and set an appropriate error when returning NO.
    // You can also choose to override -readFromFileWrapper:ofType:error: or -readFromURL:ofType:error: instead.
    // If you override either of these, you should also override -isEntireFileLoaded to return NO if the contents are lazily loaded.
    if (outError) {
        *outError = [NSError errorWithDomain:NSOSStatusErrorDomain code:unimpErr userInfo:nil];
    }
    return NO;
}

+ (BOOL)autosavesInPlace {
    return YES;
}

@end
