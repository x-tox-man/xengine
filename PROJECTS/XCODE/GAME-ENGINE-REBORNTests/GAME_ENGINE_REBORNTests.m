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
#include "GRAPHIC_MESH_MANAGER.h"
#include "GRAPHIC_FONT.h"
#include "GRAPHIC_GLYPH.h"
#include "FONT_EDITOR.h"

#include <vector>

CORE_FILESYSTEM file_system;

@interface GAME_ENGINE_REBORNTests : XCTestCase

@end

@implementation GAME_ENGINE_REBORNTests

- (void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
    
    file_system.Initialize( "/Users/CBE/DevelopProjects/game-engine/RESOURCES/" );
    
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
        char * string = (char *) malloc (string_size);
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
        char * string = (char *) malloc (string_size);
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
    
    images[0] = (RESOURCE_IMAGE *) loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( "flowers" , "png", "IMAGES/" ) );
    images[1] = (RESOURCE_IMAGE *)loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( "tulips" , "png", "IMAGES/" ) );
    images[2] = (RESOURCE_IMAGE *)loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( "aa427350402" , "png", "IMAGES/" ) );
    images[3] = (RESOURCE_IMAGE *)loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( "aa449206906" , "png", "IMAGES/" ) );
    images[4] = (RESOURCE_IMAGE *)loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( "game-controller" , "png", "IMAGES/" ) );
    images[5] = (RESOURCE_IMAGE *)loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( "button_start" , "png", "IMAGES/" ) );
    images[6] = (RESOURCE_IMAGE *)loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( "Create_Server_button" , "png", "IMAGES/" ) );
    images[7] = (RESOURCE_IMAGE *)loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( "fireButton" , "png", "IMAGES/" ) );
    images[8] = (RESOURCE_IMAGE *)loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( "Game_Boy-Button-Start" , "png", "IMAGES/" ) );
    images[9] = (RESOURCE_IMAGE *)loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( "game-controller-icone-4947-96" , "png", "IMAGES/" ) );
    
    images[10] = (RESOURCE_IMAGE *)loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( "agua-games-button" , "png", "IMAGES/" ) );
    images[11] = (RESOURCE_IMAGE *)loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( "icn-modal-close" , "png", "IMAGES/" ) );
    images[12] = (RESOURCE_IMAGE *)loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( "Perspective-Button-Games-icon" , "png", "IMAGES/" ) );
    images[13] = (RESOURCE_IMAGE *)loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( "Playstation-Button-C" , "png", "IMAGES/" ) );
    images[14] = (RESOURCE_IMAGE *)loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( "remote-logoff" , "png", "IMAGES/" ) );
    images[15] = (RESOURCE_IMAGE *)loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( "SearchButton" , "png", "IMAGES/" ) );
    images[16] = (RESOURCE_IMAGE *)loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( "Sound On" , "png", "IMAGES/" ) );
    images[17] = (RESOURCE_IMAGE *)loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( "Xbox_360_X" , "png", "IMAGES/" ) );
    images[18] = (RESOURCE_IMAGE *)loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( "frameBorder" , "png", "IMAGES/" ) );
    
    
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
    
    //writer.Write( "/Users/CBE/DevelopProjects/game-engine/RESOURCES/IMAGES/blit.png", images[0] );
    
    atlas_compiler.Compile( "/Users/CBE/DevelopProjects/game-engine/RESOURCES/IMAGES/atlas_test", images );
}

-(void) testCoreData {
    
    CORE_DATA_BUFFER
        buffer,
        buffer2;
    
    CORE_DATA_STREAM stream;
    
    char * test = (char *) CORE_MEMORY_ALLOCATOR_Allocate( (int) strlen("1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567\0"));
    
    buffer.Setsections( 1 );
    buffer.InitializeWithMemory( 128, 1, (void*) test );
    
    stream.Open();
    
    XS_CLASS_SERIALIZER< CORE_DATA_BUFFER >::Serialize<std::true_type>( buffer, stream );
    
    stream.Close();
    
    stream.ResetOffset();
    
    stream.Open();
    
    XS_CLASS_SERIALIZER< CORE_DATA_BUFFER >::Serialize<std::false_type>( buffer2, stream );
    
    stream.Close();
    
    XCTAssert( buffer2.Getsize() == buffer.Getsize() );
    XCTAssert( strcmp( (char*)buffer2.getpointerAtIndex(0, 0), (char*) buffer.getpointerAtIndex(0, 0)) == 0 );
}

- (void) testCompileCollada {
    
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
        CORE_FILESYSTEM_PATH path = CORE_FILESYSTEM_PATH::FindFilePath( "Chris" , "dae", "MODELS" );
        CORE_FILESYSTEM_PATH destintation_path = CORE_FILESYSTEM_PATH::FindFilePath( "Chris" , "smx", "MODELS" );
        
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
    
    images[0] = (RESOURCE_IMAGE *) loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( "flowers" , "png", "IMAGES/" ) );
    images[1] = (RESOURCE_IMAGE *)loader.Load( CORE_FILESYSTEM_PATH::FindFilePath( "tulips" , "png", "IMAGES/" ) );
    
    images[0]->Blit(images[1], 0, 100, 5, 5, 0);
    
    writer.Write( "/Users/CBE/DevelopProjects/game-engine/RESOURCES/IMAGES/blit.png", images[0] );
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
    test_class2.TestCharArray = (char *) malloc( 32);
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
    
    entity.Initialize("/Users/CBE/DevelopProjects/game-engine/RESOURCES/SCRIPTS/game.lua");
}

- (void) testIdentityMatrix {
    
    float matrix[16];
    float matrix_result[16];
    float matrix_result2[16];
    
    matrix_result2[0] = 1.0f;
    matrix_result2[1] = 0.0f;
    matrix_result2[2] = 0.0f;
    matrix_result2[3] = 0.0f;
    
    matrix_result2[4] = 0.0f;
    matrix_result2[5] = 1.0f;
    matrix_result2[6] = 0.0f;
    matrix_result2[7] = 0.0f;
    
    matrix_result2[8] = 0.0f;
    matrix_result2[9] = 0.0f;
    matrix_result2[10] = 1.0f;
    matrix_result2[11] = 0.0f;
    
    matrix_result2[12] = 0.0f;
    matrix_result2[13] = 0.0f;
    matrix_result2[14] = 0.0f;
    matrix_result2[15] = 1.0f;
    
    GLOBAL_IDENTITY_MATRIX( matrix );
    GLOBAL_IDENTITY_MATRIX( matrix_result );
    
    XCTAssert( GLOBAL_EQUALS_MATRIX( matrix, matrix_result ) );
    XCTAssert( GLOBAL_EQUALS_MATRIX( matrix, matrix_result2 ) );
}

- (void)testRotationXMatrix {
    
    float matrix[16];
    float matrix_result[16];
    
    GLOBAL_IDENTITY_MATRIX( matrix );
    GLOBAL_IDENTITY_MATRIX( matrix_result );
    
    matrix_result[5] = cosf(M_PI);
    matrix_result[6] = -sinf(M_PI);
    
    matrix_result[9] = sinf(M_PI);
    matrix_result[10] = cosf(M_PI);
    
    GLOBAL_ROTATE_MATRIX( matrix, M_PI, 0.0f, 0.0f );
    
    XCTAssert( GLOBAL_EQUALS_MATRIX( matrix, matrix_result ) );
}

- (void)testQuaternionMatrix {
    
    CORE_MATH_MATRIX mat;
    float matrix_result[16];
    CORE_MATH_QUATERNION quaternion;
    CORE_MATH_QUATERNION quaternion2;
    
    mat.XRotate(0.33f);
    mat.YRotate(0.124f);
    mat.ZRotate(0.76f);
    mat.XRotate(0.22f);
    mat.YRotate(-0.14f);
    mat.ZRotate(0.39f);
    
    quaternion.FromMatrix( mat.GetRow(0) );
    
    quaternion.ToMatrix( matrix_result );
    
    quaternion2.FromMatrix( matrix_result );
    
    XCTAssert( GLOBAL_EQUALS_MATRIX(mat.GetRow(0), matrix_result) );
              
    XCTAssert( quaternion == quaternion2 );
}

- (void)testRotatedQuaternionMatrix {
    
    float matrix[16];
    float matrix_result[16];
    CORE_MATH_QUATERNION quaternion;
    CORE_MATH_QUATERNION quaternion2;
    
    GLOBAL_IDENTITY_MATRIX(matrix);
    
    GLOBAL_ROTATE_MATRIX(matrix, 50.0f, 0.0f, 0.0f);
    
    quaternion.FromMatrix( matrix );
    
    quaternion.ToMatrix( matrix_result );
    
    XCTAssert( GLOBAL_EQUALS_MATRIX(matrix, matrix_result) );
}

-(void) testQuaternionInit2 {
    
    [self measureBlock:^{
            // Put the code you want to measure the time of here.
        CORE_MATH_QUATERNION quat;
        
        for (int i = 0; i < 1; i++) {
            
            quat.X( i * 0.0f );
            quat.Y( i * 1.0f );
            quat.Z( i * 2.0f );
            quat.W( i * 3.0f );
            
            XCTAssert(quat.X() == 0.0f* i && quat.Y() == 1.0f* i && quat.Z() == 2.0f* i && quat.W() == 3.0f* i );
        }
    }];
}

-(void) testQuaternionInit3 {
    
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
        
        CORE_MATH_QUATERNION quat;
        
        for (int i = 0; i < 1; i++) {
            quat[0] = i * 0.0f;
            quat[1] = i * 1.0f;
            quat[2] = i * 2.0f;
            quat[3] = i * 3.0f;
            
            XCTAssert(quat.X() == 0.0f* i && quat.Y() == 1.0f* i && quat.Z() == 2.0f* i && quat.W() == 3.0f* i );
        }
    }];
    
    //XCTAssert(quat.X == 0.0f && quat.Y == 1.0f && quat.Z == 0.0f && quat.W == 3.0f );
}

-(void) testMatrixIdentity {
    
    CORE_MATH_MATRIX identity( CORE_MATH_MATRIX::Identity);
    
    XCTAssert( identity[0] == 1.0f);
    XCTAssert( identity[1] == 0.0f);
    XCTAssert( identity[2] == 0.0f);
    XCTAssert( identity[3] == 0.0f);
    
    XCTAssert( identity[4] == 0.0f);
    XCTAssert( identity[5] == 1.0f);
    XCTAssert( identity[6] == 0.0f);
    XCTAssert( identity[7] == 0.0f);
    
    XCTAssert( identity[8] == 0.0f);
    XCTAssert( identity[9] == 0.0f);
    XCTAssert( identity[10] == 1.0f);
    XCTAssert( identity[11] == 0.0f);
    
    XCTAssert( identity[12] == 0.0f);
    XCTAssert( identity[13] == 0.0f);
    XCTAssert( identity[14] == 0.0f);
    XCTAssert( identity[15] == 1.0f);
}

-(void) testMatrixRotation {
    
    CORE_MATH_MATRIX identity( CORE_MATH_MATRIX::Identity);
    CORE_MATH_MATRIX matrix( CORE_MATH_MATRIX::Identity);
    CORE_MATH_MATRIX matrix2( CORE_MATH_MATRIX::Identity);
    
    matrix.XRotate(M_PI);
    matrix2.XRotate(M_PI_2);
    matrix2.XRotate(M_PI_2);
    
    XCTAssert( matrix == matrix2 );
    XCTAssert( matrix != identity );
    
    matrix.XRotate(M_PI);
    
    XCTAssert( matrix == identity );
}

-(void) testMatrixQuaternionRotation {
    
    CORE_MATH_MATRIX matrix;
    CORE_MATH_MATRIX matrix2;
    CORE_MATH_QUATERNION quaternion;
    CORE_MATH_QUATERNION quaternion2;
    
    matrix.XRotate(M_PI_4);
    matrix.YRotate(M_PI_2);
    matrix.ZRotate(M_PI);
    
    quaternion.RotateX(M_PI_4);
    quaternion.RotateY(M_PI_2);
    quaternion.RotateZ(M_PI);
    
    //quaternion.Normalize();
    //quaternion2.Normalize();
    quaternion.ToMatrix( &matrix2[0] );
    quaternion2.FromMatrix(&matrix[0] );
    
    XCTAssert(matrix == matrix2 );
}

-(void)testMatrixXRotation
{
    CORE_MATH_MATRIX matrix;
    
    matrix.XRotate(M_PI_4);
}

-(void)testMatrixYRotation
{
    CORE_MATH_MATRIX matrix;
    
    matrix.YRotate(M_PI_4);
}

-(void)testMatrixZRotation
{
    CORE_MATH_MATRIX matrix;
    
    matrix.ZRotate(M_PI_4);
}

-(void)testMatrixMultiply
{
    CORE_MATH_POSE pose;
    
    CORE_MATH_MATRIX matrix,matrix2,matrix_mul,matrix_result;
    
    pose.FromMatrix(matrix);
    
    matrix[0] = 0.0000000409782004;
    matrix[1] = 0.99999988;
    matrix[2] = -0.00000128102999;
    matrix[3] = -0.000000119208998;
    matrix[4] = 0.0122822998;
    matrix[5] = 0.00000127219005;
    matrix[6] = 0.9999246;
    matrix[7] = -0.000000119208998;
    matrix[8] = 0.99992448;
    matrix[9] = -0.0000000633298995;
    matrix[10] = -0.01228227;
    matrix[11] = 0;
    matrix[12] = 0;
    matrix[13] = 0;
    matrix[14] = 0;
    matrix[15] = 1;

    matrix2[0] = -0.329756796;
    matrix2[1] = 0.936163783;
    matrix2[2] = 0.121892698;
    matrix2[3] = -0.290822089;
    matrix2[4] = -0.943297982;
    matrix2[5] = -0.321524113;
    matrix2[6] = -0.0825289637;
    matrix2[7] = 0.251100004;
    matrix2[8] = -0.0380691588;
    matrix2[9] = -0.142195597;
    matrix2[10] = 0.989106297;
    matrix2[11] = 11.22896;
    matrix2[12] = 0;
    matrix2[13] = 0;
    matrix2[14] = 0;
    matrix2[15] = 1;
    
    matrix_mul = matrix2*matrix;
    
    matrix_result[0] = 0.133381724;
    matrix_result[1] = -0.329755574;
    matrix_result[2] = 0.934596538;
    matrix_result[3] = -0.290822148;
    matrix_result[4] = -0.0864718183;
    matrix_result[5] = -0.94329828;
    matrix_result[6] = -0.320485026;
    matrix_result[7] = 0.251100153;
    matrix_result[8] = 0.987285137;
    matrix_result[9] = -0.0380694009;
    matrix_result[10] = -0.154333293;
    matrix_result[11] = 11.22896;
    matrix_result[12] = 0;
    matrix_result[13] = 0;
    matrix_result[14] = 0;
    matrix_result[15] = 1;
    
    XCTAssert(matrix_mul == matrix_result);
}

-(void)testMultiplyPoseFromMatrix
{
    CORE_MATH_POSE pose1,pose2,pose_result,pose_mul;
    
    CORE_MATH_MATRIX matrix,matrix2,matrix_mul,matrix_result;
    
    matrix[0] = 0.0000000409782004;
    matrix[1] = 0.99999988;
    matrix[2] = -0.00000128102999;
    matrix[3] = -0.000000119208998;
    matrix[4] = 0.0122822998;
    matrix[5] = 0.00000127219005;
    matrix[6] = 0.9999246;
    matrix[7] = -0.000000119208998;
    matrix[8] = 0.99992448;
    matrix[9] = -0.0000000633298995;
    matrix[10] = -0.01228227;
    matrix[11] = 0;
    matrix[12] = 0;
    matrix[13] = 0;
    matrix[14] = 0;
    matrix[15] = 1;
    
    pose1.FromMatrix(matrix);
    
    matrix2[0] = -0.329756796;
    matrix2[1] = 0.936163783;
    matrix2[2] = 0.121892698;
    matrix2[3] = -0.290822089;
    matrix2[4] = -0.943297982;
    matrix2[5] = -0.321524113;
    matrix2[6] = -0.0825289637;
    matrix2[7] = 0.251100004;
    matrix2[8] = -0.0380691588;
    matrix2[9] = -0.142195597;
    matrix2[10] = 0.989106297;
    matrix2[11] = 11.22896;
    matrix2[12] = 0;
    matrix2[13] = 0;
    matrix2[14] = 0;
    matrix2[15] = 1;
    
    pose2.FromMatrix(matrix2);
    
    matrix_result[0] = 0.133381724;
    matrix_result[1] = -0.329755574;
    matrix_result[2] = 0.934596538;
    matrix_result[3] = -0.290822148;
    matrix_result[4] = -0.0864718183;
    matrix_result[5] = -0.94329828;
    matrix_result[6] = -0.320485026;
    matrix_result[7] = 0.251100153;
    matrix_result[8] = 0.987285137;
    matrix_result[9] = -0.0380694009;
    matrix_result[10] = -0.154333293;
    matrix_result[11] = 11.22896;
    matrix_result[12] = 0;
    matrix_result[13] = 0;
    matrix_result[14] = 0;
    matrix_result[15] = 1;
    
    pose_result.FromMatrix(matrix_result);
    
    pose_mul = pose2 * pose1;
    
    XCTAssert(pose_result == pose_mul);
}

-(void)testPoseFromMatrixToMatrix
{
    CORE_MATH_POSE pose1;
    
    CORE_MATH_MATRIX matrix,matrix2;
    
    matrix[0] = 0.0f;
    matrix[1] = 1.0f;
    matrix[2] = 0.0f;
    matrix[3] = 0.0f;
    matrix[4] = 0.012f;
    matrix[5] = 0.0f;
    matrix[6] = 1.0f;
    matrix[7] = 0.0f;
    matrix[8] = 1.0f;
    matrix[9] = 0.0f;
    matrix[10] = -0.012f;
    matrix[11] = 0.0f;
    matrix[12] = 0.0f;
    matrix[13] = 0.0f;
    matrix[14] = 0.0f;
    matrix[15] = 1.0f;
    
    pose1.FromMatrix(matrix);
    pose1.ToMatrix(matrix2);
    
    XCTAssert(matrix == matrix2);
}

-(void)testBaseQuaternionFromRotationMatrix
{
    CORE_MATH_POSE pose1;
    
    CORE_MATH_MATRIX matrix,matrix2;
    
    matrix[0] = 1.0f;
    matrix[1] = 0.0f;
    matrix[2] = 0.0f;
    matrix[3] = 0.0f;
    
    matrix[4] = 0.0f;
    matrix[5] = 0.0f;
    matrix[6] = -1.0f;
    matrix[7] = 0.0f;
    
    matrix[8] = 0.0f;
    matrix[9] = 1.0f;
    matrix[10] = 0.0f;
    matrix[11] = 40.0f;
    
    matrix[12] = 0.0f;
    matrix[13] = 0.0f;
    matrix[14] = 0.0f;
    matrix[15] = 1.0f;
    
    pose1.FromMatrix(matrix);
    
    XCTAssert(pose1.GetOrientation().X() - 0.7071 < 0.0001f &&  pose1.GetOrientation().W() - 0.7071 < 0.0001f);
}

-(void)testPoseFromMatrix1
{
    CORE_MATH_POSE pose;
}

-(void)testPoseToMatrix
{
    CORE_MATH_POSE pose;
}

-(void)testPoseToMatrix1
{
    CORE_MATH_POSE pose;
}

-(void) testMatrixMultiplication {
    
    CORE_MATH_MATRIX matrix;
    CORE_MATH_MATRIX matrix2;
    CORE_MATH_MATRIX matrix_result;
    CORE_MATH_MATRIX matrix_result1;
    
    matrix.XRotate(M_PI_4);
    matrix2.YRotate(M_PI_2);

    matrix_result = matrix * matrix2;
    
    matrix_result1.XRotate(M_PI_4);
    matrix_result1.YRotate(M_PI_2);
    
    XCTAssert(matrix_result1 == matrix_result );
}

-(void) testQuaternionMultiplication {
    
    CORE_MATH_MATRIX matrix;
    CORE_MATH_MATRIX matrix2;
    CORE_MATH_MATRIX matrix_result;
    CORE_MATH_MATRIX matrix_result1;
    CORE_MATH_QUATERNION quaternion;
    CORE_MATH_QUATERNION quaternion2;
    CORE_MATH_QUATERNION quaternion_result;
    
    matrix.XRotate(M_PI_4);
    matrix2.YRotate(M_PI_2);
    matrix2.ZRotate(M_PI);
    
    matrix_result = matrix = matrix2;
    
    quaternion.RotateX(M_PI_4);
    quaternion2.RotateY(M_PI_2);
    quaternion2.RotateZ(M_PI);
    
    quaternion_result = quaternion * quaternion2;
    
    quaternion_result.ToMatrix( &matrix_result1[0] );

    
    XCTAssert(matrix_result1 == matrix_result );
}

-(void) testMatrixInverse {
    
    CORE_MATH_MATRIX matrix( CORE_MATH_MATRIX::Identity);
    CORE_MATH_MATRIX identity( CORE_MATH_MATRIX::Identity);
    CORE_MATH_MATRIX inverse;
    
    matrix.Translate(  ( float[3] ){-1.0f, 1.0f, 2.0f} );
    matrix.GetInverse( inverse );
    
    matrix *= inverse;
    
    XCTAssert(identity == matrix );
}

-(void) testVectorRotation {
    
    CORE_MATH_MATRIX matrix( CORE_MATH_MATRIX::Identity);
    CORE_MATH_VECTOR rotation;
    CORE_MATH_VECTOR expected;
    
    matrix.YRotate( M_PI );
    
    expected.Set(-1.0f, 0.0f, 0.0f, 0.0f );
    rotation.Set( 1.0f, 0.0f, 0.0f, 0.0f );
    
    const CORE_MATH_VECTOR & result( rotation * matrix );
    float test[4];
    
    memcpy(test, &result[0], 4);
    
    XCTAssert( expected[0] == test[0] );
    XCTAssert( expected[1] == test[1] );
    XCTAssert( expected[2] == test[2] );
    XCTAssert( expected[3] == test[3] );
}

-(void) testRaySphereIntersection {
    
    CORE_MATH_RAY ray;
    CORE_MATH_SHAPE shape;
    
    ray.SetOrigin(CORE_MATH_VECTOR::WAxis );
    ray.SetDirection( CORE_MATH_VECTOR::ZAxis );
    
    shape.SetPosition( CORE_MATH_VECTOR( 1.0f, 0.0f, -5.0f, 1.0f ) );
    shape.SetHalfDiagonal( CORE_MATH_VECTOR::XAxis );

    bool intersection = shape.GetIntersection( ray );
    
    XCTAssert( intersection );
}

@end
