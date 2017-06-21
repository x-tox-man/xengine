//
//  GAME_ENGINE_REBORNTests.m
//  GAME-ENGINE-REBORNTests
//
//  Created by Christophe Bernard on 15/10/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#import <XCTest/XCTest.h>

#include "CORE_MATH_QUATERNION.h"
#include "CORE_MATH_MATRIX.h"
#include "CORE_MATH_VECTOR.h"
#include "CORE_MATH_RAY.h"
#include "CORE_HELPERS_SCALAR.h"
#include "CORE_MATH_SHAPE.h"
#include "CORE_DATA_STREAM.h"
#include "TestClass.h"
#include "TestClass2.h"
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
#include "GRAPHIC_OBJECT_RESOURCE_LOADER.h"
#include "GRAPHIC_MESH_MANAGER.h"
#include "GRAPHIC_FONT.h"
#include "GRAPHIC_GLYPH.h"
#include "FONT_EDITOR.h"

#include <vector>

@interface GAME_ENGINE_REBORNTests : XCTestCase

@end

@implementation GAME_ENGINE_REBORNTests {
    CORE_FILESYSTEM file_system;
}

- (void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
    
    file_system.Initialize( "/Users/christophebernard/Develop/Project/game-engine/RESOURCES/" );
    
    CORE_FILESYSTEM::SetDefaultFilesystem( file_system );
}

- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

-(void) testVirtualTemplate {
    
    [self measureBlock:^{
        
        float f = 0.0f;
        
        for (int i = 0; i < 10000; i++ ) {
            TestTemplate< TestTemplateSpecialized > tmpl;
            
            f += tmpl.Initialize();
        }
        
        printf( "%f\n", f );
    }];
}

-(void) testVirtualTemplate2 {
    [self measureBlock:^{
        
        float f = 0.0f;
        
        for (int i = 0; i < 10000; i++ ) {
            TestTemplateSpecialized tmpl;
            
            f += tmpl.Initialize();
        }
        
        printf( "%f\n", f );
    }];
}

-(void) testVirtualTemplate3 {
    [self measureBlock:^{
        
        float f = 0.0f;
        
        for (int i = 0; i < 10000; i++ ) {
            TestTemplateSpecialized tmpl;
            
            f += tmpl.test();
        }
        
        printf( "%f\n", f );
    }];
}

-(void) testVirtualTemplate4 {
    [self measureBlock:^{
        
        float f = 0.0f;
        
        for (int i = 0; i < 10000; i++ ) {
            
            f += TestTemplateSpecialized::Initialize();
        }
        
        printf( "%f\n", f );
    }];
}

-(void) testFonts {
    
    NSString * font_name = [NSString stringWithFormat:@"Arial Black" ];
    NSArray * dirs = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:@"/Library/Fonts" error:nil];
    NSArray * fonts = [dirs filteredArrayUsingPredicate:[NSPredicate predicateWithFormat:@"self contains[cd] %@", font_name ]];
    
    if ( [fonts count] > 0 ) {
        FONT_EDITOR
            editor;
        FONT_DESCRIPTOR
            descriptor;
        
        CORE_FILESYSTEM_PATH
        image_target_path( CORE_FILESYSTEM_PATH::FindFilePath( "arial_black_12", "png", "FONTS" ) ),
        font_target_path( CORE_FILESYSTEM_PATH::FindFilePath( "arial_black_12", "fxb", "FONTS" ) );
        
        descriptor.color[0] = 255;
        descriptor.color[1] = 255;
        descriptor.color[2] = 255;
        descriptor.color[3] = 255;
        
        descriptor.Size = 12;
        
        int string_size = strlen( " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789&é\"'\(§è!çà)-" );
        char * string = (char *) CORE_MEMORY_ALLOCATOR_Allocate (string_size);
        memcpy(string, " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789&é\"'\(§è!çà)-", string_size );
        
        descriptor.CharacterSet.resize( string_size );
        
        for (int i = 0; i < string_size; i++ ) {
            
            descriptor.CharacterSet[ i ] = string[i];
        }
        
        NSString * filename = [NSString stringWithFormat:@"/Library/Fonts/"];
        filename = [filename stringByAppendingString:[fonts objectAtIndex:0] ];
        
        editor.CompileFont(512, 512, [filename cStringUsingEncoding:NSASCIIStringEncoding], descriptor, image_target_path, font_target_path );
    }
}

-(void) testFonts2 {
    
    NSString * font_name = [NSString stringWithFormat:@"Arial Black" ];
    NSArray * dirs = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:@"/Library/Fonts" error:nil];
    NSArray * fonts = [dirs filteredArrayUsingPredicate:[NSPredicate predicateWithFormat:@"self contains[cd] %@", font_name ]];
    
    if ( [fonts count] > 0 ) {
        
        FONT_EDITOR
            editor;
        FONT_DESCRIPTOR
            descriptor;
        
        CORE_FILESYSTEM_PATH
        image_target_path( CORE_FILESYSTEM_PATH::FindFilePath( "arial_black_20", "png", "FONTS" ) ),
        font_target_path( CORE_FILESYSTEM_PATH::FindFilePath( "arial_black_20", "fxb", "FONTS" ) );
        
        descriptor.color[0] = 255;
        descriptor.color[1] = 255;
        descriptor.color[2] = 255;
        descriptor.color[3] = 255;
        
        descriptor.Size = 20;
        
        int string_size = strlen( " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!" );
        char * string = (char *) CORE_MEMORY_ALLOCATOR_Allocate (string_size);
        memcpy(string, " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!", string_size );
        
        descriptor.CharacterSet.resize( string_size );
        
        for (int i = 0; i < string_size; i++ ) {
            
            descriptor.CharacterSet[ i ] = string[i];
        }
        
        NSString * filename = [NSString stringWithFormat:@"/Library/Fonts/"];
        filename = [filename stringByAppendingString:[fonts objectAtIndex:0] ];
        
        editor.CompileFont(512, 512, [filename cStringUsingEncoding:NSASCIIStringEncoding], descriptor, image_target_path, font_target_path );
    }
}

-(void) testTextureAtlas {
    
    std::vector< RESOURCE_IMAGE *> images;
    
    RESOURCE_IMAGE_ATLAS_COMPILER atlas_compiler;
    
    RESOURCE_IMAGE_PNG_LOADER loader;
    RESOURCE_IMAGE_PNG_WRITER writer;
    
    images.resize(18);
    
    images[0] = (RESOURCE_IMAGE *) loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( "flowers" , "png", "TEXTURES" ) );
    images[1] = (RESOURCE_IMAGE *)loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( "tulips" , "png", "TEXTURES" ) );
    images[2] = (RESOURCE_IMAGE *)loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( "aa427350402" , "png", "TEXTURES" ) );
    images[3] = (RESOURCE_IMAGE *)loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( "aa449206906" , "png", "TEXTURES" ) );
    images[4] = (RESOURCE_IMAGE *)loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( "game-controller" , "png", "TEXTURES" ) );
    images[5] = (RESOURCE_IMAGE *)loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( "button_start" , "png", "TEXTURES" ) );
    images[6] = (RESOURCE_IMAGE *)loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( "Create_Server_button" , "png", "TEXTURES" ) );
    images[7] = (RESOURCE_IMAGE *)loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( "fireButton" , "png", "TEXTURES" ) );
    images[8] = (RESOURCE_IMAGE *)loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( "Game_Boy-Button-Start" , "png", "TEXTURES" ) );
    images[9] = (RESOURCE_IMAGE *)loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( "game-controller-icone-4947-96" , "png", "TEXTURES" ) );
    
    images[10] = (RESOURCE_IMAGE *)loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( "agua-games-button" , "png", "TEXTURES" ) );
    images[11] = (RESOURCE_IMAGE *)loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( "icn-modal-close" , "png", "TEXTURES" ) );
    images[12] = (RESOURCE_IMAGE *)loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( "Perspective-Button-Games-icon" , "png", "TEXTURES" ) );
    images[13] = (RESOURCE_IMAGE *)loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( "Playstation-Button-C" , "png", "TEXTURES" ) );
    images[14] = (RESOURCE_IMAGE *)loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( "remote-logoff" , "png", "TEXTURES" ) );
    images[15] = (RESOURCE_IMAGE *)loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( "SearchButton" , "png", "TEXTURES" ) );
    images[16] = (RESOURCE_IMAGE *)loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( "Sound On" , "png", "TEXTURES" ) );
    images[17] = (RESOURCE_IMAGE *)loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( "Xbox_360_X" , "png", "TEXTURES" ) );
    images[18] = (RESOURCE_IMAGE *)loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( "frameBorder" , "png", "TEXTURES" ) );
    
    
    images[0]->SetIdentifier( CORE_HELPERS_UNIQUE_IDENTIFIER( "flowers" ) );
    images[1]->SetIdentifier( CORE_HELPERS_UNIQUE_IDENTIFIER( "tulips" ) );
    images[2]->SetIdentifier( CORE_HELPERS_UNIQUE_IDENTIFIER( "aa427350402" ) );
    images[3]->SetIdentifier( CORE_HELPERS_UNIQUE_IDENTIFIER( "aa449206906" ) );
    images[4]->SetIdentifier( CORE_HELPERS_UNIQUE_IDENTIFIER( "game-controller" ) );
    images[5]->SetIdentifier( CORE_HELPERS_UNIQUE_IDENTIFIER( "button_start" ) );
    images[6]->SetIdentifier( CORE_HELPERS_UNIQUE_IDENTIFIER( "Create_Server_button" ) );
    images[7]->SetIdentifier( CORE_HELPERS_UNIQUE_IDENTIFIER( "fireButton" ) );
    images[8]->SetIdentifier( CORE_HELPERS_UNIQUE_IDENTIFIER( "Game_Boy-Button-Start" ) );
    images[9]->SetIdentifier( CORE_HELPERS_UNIQUE_IDENTIFIER( "game-controller-icone-4947-96" ) );
    images[10]->SetIdentifier( CORE_HELPERS_UNIQUE_IDENTIFIER( "agua-games-button" ) );
    images[11]->SetIdentifier( CORE_HELPERS_UNIQUE_IDENTIFIER( "icn-modal-close" ) );
    images[12]->SetIdentifier( CORE_HELPERS_UNIQUE_IDENTIFIER( "MW::stop_lobby_button" ) );
    images[13]->SetIdentifier( CORE_HELPERS_UNIQUE_IDENTIFIER( "MW::start_client_button" ) );
    images[14]->SetIdentifier( CORE_HELPERS_UNIQUE_IDENTIFIER( "MW::start_server_button" ) );
    images[15]->SetIdentifier( CORE_HELPERS_UNIQUE_IDENTIFIER( "MW::start_lobby_button" ) );
    images[16]->SetIdentifier( CORE_HELPERS_UNIQUE_IDENTIFIER( "Sound On" ) );
    images[17]->SetIdentifier( CORE_HELPERS_UNIQUE_IDENTIFIER( "OW" ) );
    images[18]->SetIdentifier( CORE_HELPERS_UNIQUE_IDENTIFIER( "FrameBorder" ) );
    
    //images[0]->Blit(images[1], 0, 100, 5, 5, 0);
    
    //writer.Write( "/Users/christophebernard/Develop/Project/game-engine/RESOURCES/TEXTURES/blit.png", images[0] );
    
    atlas_compiler.Compile( "/Users/christophebernard/Develop/Project/game-engine/RESOURCES/TEXTURES/atlas_test", images );
}

-(void) testCoreData {
    
    CORE_DATA_BUFFER
        buffer,
        buffer2;
    
    CORE_DATA_STREAM stream;
    
    char * test = (char *) CORE_MEMORY_ALLOCATOR_Allocate( (int) strlen("1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567\0"));
    
    buffer.SetSections( 1 );
    buffer.InitializeWithMemory( 128, 1, (void*) test );
    
    stream.Open();
    
    XS_CLASS_SERIALIZER< CORE_DATA_BUFFER >::Serialize<std::true_type>( buffer, stream );
    
    stream.Close();
    
    stream.ResetOffset();
    
    stream.Open();
    
    XS_CLASS_SERIALIZER< CORE_DATA_BUFFER >::Serialize<std::false_type>( buffer2, stream );
    
    stream.Close();
    
    XCTAssert( buffer2.GetSize() == buffer.GetSize() );
    XCTAssert( strcmp( (char*)buffer2.getpointerAtIndex(0, 0), (char*) buffer.getpointerAtIndex(0, 0)) == 0 );
}

- (void) testCompileCollada {
    
    
    /*{
        CORE_FILESYSTEM_PATH path = CORE_FILESYSTEM_PATH::FindFilePath( "untitled2" , "dae", "MODELS" );
        CORE_FILESYSTEM_PATH destintation_path = CORE_FILESYSTEM_PATH::FindFilePath( "untitled2" , "smx", "MODELS" );
        
        GRAPHIC_MESH_MANAGER::GetInstance().Compile(path, destintation_path, 0, GRAPHIC_MESH_TYPE_OpenCollada );
    }*/
    
    {
        CORE_FILESYSTEM_PATH path = CORE_FILESYSTEM_PATH::FindFilePath( "Chris" , "dae", "MODELS" );
        CORE_FILESYSTEM_PATH destintation_path = CORE_FILESYSTEM_PATH::FindFilePath( "Chris" , "smx", "MODELS" );
        
        GRAPHIC_MESH_MANAGER::GetInstance().Compile(path, destintation_path, 0, GRAPHIC_MESH_TYPE_OpenCollada );
    }
    
    {
        CORE_FILESYSTEM_PATH path = CORE_FILESYSTEM_PATH::FindFilePath( "DefenderLingerie00" , "dae", "MODELS" );
        CORE_FILESYSTEM_PATH destintation_path = CORE_FILESYSTEM_PATH::FindFilePath( "DefenderLingerie00" , "smx", "MODELS" );
        
        GRAPHIC_MESH_MANAGER::GetInstance().Compile(path, destintation_path, 0, GRAPHIC_MESH_TYPE_OpenCollada );
    }
    
    {
        CORE_FILESYSTEM_PATH path = CORE_FILESYSTEM_PATH::FindFilePath( "T_34_85" , "dae", "MODELS" );
        CORE_FILESYSTEM_PATH destintation_path = CORE_FILESYSTEM_PATH::FindFilePath( "T_34_85" , "smx", "MODELS" );
        
        GRAPHIC_MESH_MANAGER::GetInstance().Compile(path, destintation_path, 0, GRAPHIC_MESH_TYPE_OpenCollada );
    }
    
    {
        CORE_FILESYSTEM_PATH path = CORE_FILESYSTEM_PATH::FindFilePath( "Primitives" , "dae", "MODELS" );
        CORE_FILESYSTEM_PATH destintation_path = CORE_FILESYSTEM_PATH::FindFilePath( "Primitives" , "smx", "MODELS" );
        
        GRAPHIC_MESH_MANAGER::GetInstance().Compile(path, destintation_path, 0, GRAPHIC_MESH_TYPE_OpenCollada );
    }
    
    {
        CORE_FILESYSTEM_PATH path = CORE_FILESYSTEM_PATH::FindFilePath( "MoulinNoAnim" , "dae", "MODELS" );
        CORE_FILESYSTEM_PATH destintation_path = CORE_FILESYSTEM_PATH::FindFilePath( "MoulinNoAnim" , "smx", "MODELS" );
        
        GRAPHIC_MESH_MANAGER::GetInstance().Compile(path, destintation_path, 0, GRAPHIC_MESH_TYPE_OpenCollada );
    }
    
    {
        CORE_FILESYSTEM_PATH path = CORE_FILESYSTEM_PATH::FindFilePath( "moulin" , "DAE", "MODELS" );
        CORE_FILESYSTEM_PATH destintation_path = CORE_FILESYSTEM_PATH::FindFilePath( "moulin" , "smx", "MODELS" );
        
        GRAPHIC_MESH_MANAGER::GetInstance().Compile(path, destintation_path, 0, GRAPHIC_MESH_TYPE_OpenCollada );
    }
    
    {
        CORE_FILESYSTEM_PATH path = CORE_FILESYSTEM_PATH::FindFilePath( "cyl" , "dae", "MODELS" );
        CORE_FILESYSTEM_PATH destintation_path = CORE_FILESYSTEM_PATH::FindFilePath( "cyl" , "smx", "MODELS" );
        
        GRAPHIC_MESH_MANAGER::GetInstance().Compile(path, destintation_path, 0, GRAPHIC_MESH_TYPE_OpenCollada );
    }
    {
        CORE_FILESYSTEM_PATH path = CORE_FILESYSTEM_PATH::FindFilePath( "thor" , "dae", "MODELS" );
        CORE_FILESYSTEM_PATH destintation_path = CORE_FILESYSTEM_PATH::FindFilePath( "thor" , "smx", "MODELS" );
        
        GRAPHIC_MESH_MANAGER::GetInstance().Compile(path, destintation_path, 0, GRAPHIC_MESH_TYPE_OpenCollada );
    }
    {
        CORE_FILESYSTEM_PATH path = CORE_FILESYSTEM_PATH::FindFilePath( "untitled" , "dae", "MODELS" );
        CORE_FILESYSTEM_PATH destintation_path = CORE_FILESYSTEM_PATH::FindFilePath( "untitled" , "smx", "MODELS" );
        
        GRAPHIC_MESH_MANAGER::GetInstance().Compile(path, destintation_path, 0, GRAPHIC_MESH_TYPE_OpenCollada );
    }
    {
        CORE_FILESYSTEM_PATH path = CORE_FILESYSTEM_PATH::FindFilePath( "Ironman" , "dae", "MODELS" );
        CORE_FILESYSTEM_PATH destintation_path = CORE_FILESYSTEM_PATH::FindFilePath( "Ironman" , "smx", "MODELS" );
        
        GRAPHIC_MESH_MANAGER::GetInstance().Compile(path, destintation_path, 0, GRAPHIC_MESH_TYPE_OpenCollada );
    }
    {
        CORE_FILESYSTEM_PATH path = CORE_FILESYSTEM_PATH::FindFilePath( "mesh2" , "dae", "MODELS" );
        CORE_FILESYSTEM_PATH destintation_path = CORE_FILESYSTEM_PATH::FindFilePath( "mesh2" , "smx", "MODELS" );
        
        GRAPHIC_MESH_MANAGER::GetInstance().Compile(path, destintation_path, 0, GRAPHIC_MESH_TYPE_OpenCollada );
    }
}

-(void) testBlit {
    
    std::vector< RESOURCE_IMAGE *> images;
    RESOURCE_IMAGE_PNG_WRITER writer;
    RESOURCE_IMAGE_PNG_LOADER loader;
    
    images.resize(2);
    
    images[0] = (RESOURCE_IMAGE *) loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( "flowers" , "png", "TEXTURES" ) );
    images[1] = (RESOURCE_IMAGE *)loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( "tulips" , "png", "TEXTURES" ) );
    
    images[0]->Blit(images[1], 0, 100, 5, 5, 0);
    
    writer.Write( "/Users/christophebernard/Develop/Project/game-engine/RESOURCES/TEXTURES/blit.png", images[0] );
}

-(void) testSerialization {
    
    TestClass
        test_class;
    TestClass2
        test_class2;
    TestClass2
        test_class3;
    
    CORE_DATA_STREAM
        stream( 128 );
    
    test_class2.TestChar = 'r';
    test_class2.TestInt = 123;
    test_class2.TestInnerClass.TestInt = 321;
    test_class2.TestCharArray = (char *) CORE_MEMORY_ALLOCATOR_Allocate( 32 );
    strcpy(test_class2.TestCharArray, "azertyuiopmlkjhg\0");
    test_class2.TestVector.resize(1);
    
    test_class2.TestVector[0].TestInt = 69;
    
    test_class2.Initialize();
    
    test_class2.TestInnerClassPtr->TestInt = 765;
    
    stream.Open();
    
    XS_CLASS_SERIALIZER< TestClass2 >::Serialize< std::true_type >( test_class2, stream );
    
    stream.ResetOffset();
    
    XS_CLASS_SERIALIZER< TestClass2 >::Serialize< std::false_type >( test_class3, stream );
    
    XCTAssert( test_class2.TestChar == test_class3.TestChar );
    XCTAssert( test_class2.TestFloat == test_class3.TestFloat );
    XCTAssert( test_class2.TestInt == test_class3.TestInt );
    XCTAssert( test_class2.TestInnerClass.TestInt == test_class3.TestInnerClass.TestInt );
    XCTAssert( strncmp( test_class2.TestCharArray, test_class3.TestCharArray, strlen( test_class2.TestCharArray ) ) == 0 );
    XCTAssert( test_class2.TestVector[0].TestInt == test_class3.TestVector[0].TestInt );
    XCTAssert(test_class2.TestInnerClassPtr->TestInt == test_class3.TestInnerClassPtr->TestInt);
    
    stream.Close();
}

-(void) testScriptingEngine {
    
    ScriptEntity entity;
    
    CORE_ABSTRACT_PROGRAM_RUNTIME_MANAGER::GetInstance().Initialize();
    
    entity.Initialize("/Users/christophebernard/Develop/Project/game-engine/RESOURCES/SCRIPTS/game.lua");
}

@end
