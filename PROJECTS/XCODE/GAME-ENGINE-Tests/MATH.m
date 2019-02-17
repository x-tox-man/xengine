//
//  MATH.m
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 25/06/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#import <XCTest/XCTest.h>

#include "CORE_MATH_MATRIX.h"
#include "CORE_MATH_VECTOR.h"
#include "CORE_MATH_RAY.h"
#include "CORE_MATH_SHAPE.h"
#include "CORE_MATH_QUATERNION.h"
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
#include "CORE_MATH.h"
#include <vector>

@interface MATH : XCTestCase

@end

@implementation MATH {
    CORE_FILESYSTEM file_system;
}

- (void)setUp {
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
    
    file_system.Initialize( "/Users/christophebernard/Develop/Project/game-engine/RESOURCES/" );
    
    CORE_FILESYSTEM::SetDefaultFilesystem( file_system );
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

-(void)testProjection {
    
    CORE_MATH_VECTOR
        position(10.0f, 15.0f, 64.0f, 1.0f);
    CORE_MATH_QUATERNION
        lookat,
        orientation;
    
    lookat.RotateX(M_PI_2 );
    orientation.RotateX( M_PI_2 );
    GRAPHIC_CAMERA
    camera( 1.0f, 1500.0f, 1024.0f, 768.0f, position, CORE_MATH_VECTOR::ZAxis, CORE_MATH_VECTOR::YAxis );
    GRAPHIC_OBJECT_RENDER_OPTIONS
    options;
    CORE_MATH_MATRIX
    transform,
    mvp,
    object_matrix;
    GRAPHIC_OBJECT
    object;
    
    options.SetPosition( CORE_MATH_VECTOR( 1.0f, 0.0f, 0.0f ) );
    options.SetOrientation( CORE_MATH_QUATERNION() );
    options.SetScaleFactor(CORE_MATH_VECTOR( 1.0f, 1.0f, 1.0f, 1.0f ) );
    GRAPHIC_RENDERER::GetInstance().SetCamera( &camera );
    
    object.ComputeModelViewProjection( options, transform, GRAPHIC_RENDERER::GetInstance(), mvp, object_matrix );
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
    
    //[self measureBlock:^{
        // Put the code you want to measure the time of here.
        CORE_MATH_QUATERNION quat;
        
        for (int i = 0; i < 1; i++) {
            
            quat.X( i * 0.0f );
            quat.Y( i * 1.0f );
            quat.Z( i * 2.0f );
            quat.W( i * 3.0f );
            
            XCTAssert(quat.X() == 0.0f* i && quat.Y() == 1.0f* i && quat.Z() == 2.0f* i && quat.W() == 3.0f* i );
        }
    //}];
}

-(void) testQuaternionInit3 {
    
    /*[self measureBlock:^{
        // Put the code you want to measure the time of here.
        
        CORE_MATH_QUATERNION quat;
        
        for (int i = 0; i < 1; i++) {
            quat[0] = i * 0.0f;
            quat[1] = i * 1.0f;
            quat[2] = i * 2.0f;
            quat[3] = i * 3.0f;
            
            XCTAssert(quat.X() == 0.0f* i && quat.Y() == 1.0f* i && quat.Z() == 2.0f* i && quat.W() == 3.0f* i );
        }
    }];*/
    
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
    
    CORE_MATH_MATRIX check2, check = matrix2 * matrix;
    
    pose_result.FromMatrix(matrix_result);
    
    pose_mul = pose2 * pose1;
    
    pose_mul.ToMatrix( check2 );
    
    XCTAssert( MATH_IsRougthlyEqual( pose_result, pose_mul ) );
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
    
    XCTAssert( MATH_IsRougthlyEqual( matrix, matrix2 ) );
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
    
    CORE_MATH_MATRIX matrix, matrix2;
    
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
    
    pose.FromMatrix(matrix);
    pose.ToMatrix( matrix2 );
    
    XCTAssert( matrix == matrix2 );
}

-(void)testPoseToMatrix
{
    CORE_MATH_POSE pose, pose2;
    CORE_MATH_MATRIX matrix;
    
    pose.SetPosition(CORE_MATH_VECTOR( 1.0f, 2.0f, 3.0f, 1.0f ) );
    
    CORE_MATH_QUATERNION q(0.0f, 1.0f, 0.0f, 1.0f );
    q.Normalize();
    
    pose.SetOrientation( q );
    
    pose.ToMatrix( matrix );
    pose2.FromMatrix( matrix );
    
    XCTAssert( pose == pose2 );
}

-(void)testMatrixToQuaternion {
    
    CORE_MATH_QUATERNION q1;
    
    CORE_MATH_MATRIX result, matrix;
    
    matrix[0] = 0.0000000409782004;
    matrix[1] = 0.99999988;
    matrix[2] = -0.00000128102999;
    matrix[3] = 0.0f;
    matrix[4] = 0.0122822998;
    matrix[5] = 0.00000127219005;
    matrix[6] = 0.9999246;
    matrix[7] = 0.0f;
    matrix[8] = 0.99992448;
    matrix[9] = -0.0000000633298995;
    matrix[10] = -0.01228227;
    matrix[11] = 0;
    matrix[12] = 0;
    matrix[13] = 0;
    matrix[14] = 0;
    matrix[15] = 1;
    
    q1.FromMatrix( &matrix[0] );
    
    q1.ToMatrix( &result[0] );
    
    XCTAssert( MATH_IsRougthlyEqual(matrix, result ) );
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

-(void) testQuaternionMultiplication2 {
    
    CORE_MATH_QUATERNION q1, q2, q3, q4;
    
    CORE_MATH_MATRIX result, matrix,matrix2;
    
    matrix[0] = 0.0000000409782004;
    matrix[1] = 0.99999988;
    matrix[2] = -0.00000128102999;
    matrix[3] = 0.0f;
    matrix[4] = 0.0122822998;
    matrix[5] = 0.00000127219005;
    matrix[6] = 0.9999246;
    matrix[7] = 0.0f;
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
    matrix2[3] = 0.0f;
    matrix2[4] = -0.943297982;
    matrix2[5] = -0.321524113;
    matrix2[6] = -0.0825289637;
    matrix2[7] = 0.0f;
    matrix2[8] = -0.0380691588;
    matrix2[9] = -0.142195597;
    matrix2[10] = 0.989106297;
    matrix2[11] = 0.0f;
    matrix2[12] = 0;
    matrix2[13] = 0;
    matrix2[14] = 0;
    matrix2[15] = 1;
    
    q1.FromMatrix( &matrix[0] );
    q2.FromMatrix( &matrix2[2] );
    
    q3 = q1 * q2;
    
    result = matrix * matrix2;
    
    q4.FromMatrix( &result[0] );
    
    XCTAssert( MATH_IsRougthlyEqual( q3, q4) );
}

-(void) testQuaternionXRotation1 {
    
    CORE_MATH_QUATERNION q1, q2, q3, q4;
    
    CORE_MATH_MATRIX result, matrix,matrix2;
    
    matrix.XRotate( -M_PI_2 );
    q1.RotateX( -M_PI_2 );
    
    q2.FromMatrix( &matrix[0] );
    q2.ToMatrix( &matrix2[0]);
    
    XCTAssert( MATH_IsRougthlyEqual( q1, q2) );
    XCTAssert( MATH_IsRougthlyEqual( matrix, matrix2) );
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

-(void) testPicking {
    
    CORE_MATH_RAY ray;
    CORE_MATH_SHAPE shape;
    
    ray.SetOrigin(CORE_MATH_VECTOR::WAxis );
    ray.SetDirection( CORE_MATH_VECTOR::ZAxis );
    
    shape.SetPosition( CORE_MATH_VECTOR( 1.0f, 0.0f, -5.0f, 1.0f ) );
    shape.SetHalfDiagonal( CORE_MATH_VECTOR::XAxis );
    
    bool intersection = shape.GetIntersection( ray );
    
    XCTAssert( intersection );
}

-(void) testMatrixQuaternionRotation2 {

    CORE_MATH_QUATERNION
    q1, q2, qresult;
    CORE_MATH_MATRIX
    m1,m2, mresult, mcombined;
    
    q1.RotateX( 0.1f);
    q1.RotateY( 0.2f);
    q1.RotateZ( -0.3f);
    
    q2.RotateX( 0.3f);
    q2.RotateY( -0.5f);
    q2.RotateZ( 0.2f);
    
    qresult = q1 * q2;
    qresult.ToMatrix( mresult.GetRow(0) );
    
    
    m1.XRotate( 0.1f );
    m1.YRotate( 0.2f );
    m1.ZRotate( -0.3f );
    
    m2.XRotate( 0.3f );
    m2.YRotate( -0.5f );
    m2.ZRotate( 0.2f );
    
    mcombined = m1 * m2;
    
    XCTAssert( mcombined == mresult );
}

-(void) testShapeBoxContainsIn1 {
    CORE_MATH_SHAPE box1, box2;
    
    box1.SetPosition( CORE_MATH_VECTOR( 0.0f, 0.0f) );
    box1.SetHalfDiagonal( CORE_MATH_VECTOR(10.0f, 5.0f, 5.0f, 0.0f ) );
    box2.SetPosition( CORE_MATH_VECTOR( 0.0f, 0.0f) );
    box2.SetHalfDiagonal( CORE_MATH_VECTOR(9.0f, 4.0f, 4.0f, 0.0f ) );
    
    XCTAssert( box1.ContainsBox( box2 ) );
}

-(void) testShapeBoxContainsIn2 {
    CORE_MATH_SHAPE box1, box2;
    
    box1.SetPosition( CORE_MATH_VECTOR( 2.0f, 2.0f, 2.0f, 1.0f ) );
    box1.SetHalfDiagonal( CORE_MATH_VECTOR(10.0f, 5.0f, 5.0f, 0.0f ) );
    box2.SetPosition( CORE_MATH_VECTOR( 2.0f, 2.0f, 2.0f, 1.0f  ) );
    box2.SetHalfDiagonal( CORE_MATH_VECTOR(9.0f, 4.0f, 4.0f, 0.0f ) );
    
    XCTAssert( box1.ContainsBox( box2 ) );
}

-(void) testShapeBoxContainsOut1 {
    CORE_MATH_SHAPE box1, box2;
    
    box1.SetPosition( CORE_MATH_VECTOR( 2.0f, 2.0f, 2.0f, 1.0f ) );
    box1.SetHalfDiagonal( CORE_MATH_VECTOR(10.0f, 5.0f, 5.0f, 0.0f ) );
    box2.SetPosition( CORE_MATH_VECTOR( 20.0f, 20.0f, 20.0f, 1.0f  ) );
    box2.SetHalfDiagonal( CORE_MATH_VECTOR(9.0f, 4.0f, 4.0f, 0.0f ) );
    
    XCTAssert( !box1.ContainsBox( box2 ) );
}

-(void) testShapeBoxContainsEven {
    CORE_MATH_SHAPE box1, box2;
    
    box1.SetPosition( CORE_MATH_VECTOR( 2.0f, 2.0f, 2.0f, 1.0f ) );
    box1.SetHalfDiagonal( CORE_MATH_VECTOR(10.0f, 5.0f, 5.0f, 0.0f ) );
    box2.SetPosition( CORE_MATH_VECTOR( 2.0f, 2.0f, 2.0f, 1.0f  ) );
    box2.SetHalfDiagonal( CORE_MATH_VECTOR(10.0f, 5.0f, 5.0f, 0.0f ) );
    
    XCTAssert( box1.ContainsBox( box2 ) );
}

-(void) testShapeBoxContainsOut2 {
    CORE_MATH_SHAPE box1, box2;
    
    box1.SetPosition( CORE_MATH_VECTOR( 2.0f, 2.0f, 2.0f, 1.0f ) );
    box1.SetHalfDiagonal( CORE_MATH_VECTOR(10.0f, 5.0f, 5.0f, 0.0f ) );
    box2.SetPosition( CORE_MATH_VECTOR( 2.0f, 2.0f, 2.0f, 1.0f  ) );
    box2.SetHalfDiagonal( CORE_MATH_VECTOR(11.0f, 4.0f, 4.0f, 0.0f ) );
    
    XCTAssert( !box1.ContainsBox( box2 ) );
}

-(void) testShapeBoxContainsOut3 {
    CORE_MATH_SHAPE box1, box2;
    
    box1.SetPosition( CORE_MATH_VECTOR( 2.0f, 2.0f, 2.0f, 1.0f ) );
    box1.SetHalfDiagonal( CORE_MATH_VECTOR(10.0f, 5.0f, 5.0f, 0.0f ) );
    box2.SetPosition( CORE_MATH_VECTOR( 2.0f, 2.0f, 2.0f, 1.0f  ) );
    box2.SetHalfDiagonal( CORE_MATH_VECTOR(11.0f, 40.0f, 40.0f, 0.0f ) );
    
    XCTAssert( !box1.ContainsBox( box2 ) );
}

-(void) testShapeBoxContainsOut4 {
    CORE_MATH_SHAPE box1, box2;
    
    box1.SetPosition( CORE_MATH_VECTOR( 2.0f, 2.0f, 2.0f, 1.0f ) );
    box1.SetHalfDiagonal( CORE_MATH_VECTOR(10.0f, 5.0f, 5.0f, 0.0f ) );
    box2.SetPosition( CORE_MATH_VECTOR( 2.0f, 2.0f, 2.0f, 1.0f  ) );
    box2.SetHalfDiagonal( CORE_MATH_VECTOR(11.0f, 4.0f, 40.0f, 0.0f ) );
    
    XCTAssert( !box1.ContainsBox( box2 ) );
}

-(void) testShapeBoxContainsIn3 {
    CORE_MATH_SHAPE box1, box2;
    
    box1.SetPosition( CORE_MATH_VECTOR( 2.0f, 2.0f, 2.0f, 1.0f ) );
    box1.SetHalfDiagonal( CORE_MATH_VECTOR(10.0f, 5.0f, 5.0f, 0.0f ) );
    box2.SetPosition( CORE_MATH_VECTOR( 2.0f, 2.0f, 2.0f, 1.0f  ) );
    box2.SetHalfDiagonal( CORE_MATH_VECTOR(11.0f, 40.0f, 40.0f, 0.0f ) );
    
    XCTAssert( box2.ContainsBox( box1 ) );
}

@end
