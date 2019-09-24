//
//  METAL.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 30/12/2018.
//  Copyright © 2018 Christophe Bernard. All rights reserved.
//

#include "GRAPHIC_SYSTEM_RUNTIME_ENVIRONMENT.h"
#include "GRAPHIC_TEXTURE.h"
#include "GRAPHIC_TEXTURE_LOADER.h"
#include "GRAPHIC_RENDER_TARGET.h"
#include "GRAPHIC_SHADER_LIGHT.h"
#include "GRAPHIC_SHADER_PROGRAM.h"
#include "GRAPHIC_MESH.h"

#if X_METAL

CORE_PARALLEL_LOCK_MUTEX GRAPHIC_SYSTEM::GraphicSystemLock;
const char * GRAPHIC_SYSTEM::ShaderDirectoryPath = "METAL";
CORE_HELPERS_COLOR GRAPHIC_SYSTEM::ClearColor = CORE_COLOR_Blue;

GRAPHIC_SYSTEM::~GRAPHIC_SYSTEM() {
    
}

void GRAPHIC_SYSTEM::Initialize( const char * app_name, int app_version ) {
    
    metalDelegate = [[__METAL_DELEGATE alloc] init];
    defaultLibrary = [_device newDefaultLibrary];
}

void GRAPHIC_SYSTEM::Finalize() {
    
}

void GRAPHIC_SYSTEM::EnableScissor(bool enable) {
    #error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::SetScissorRectangle( float x, float y, float width, float height ) {
    
    #error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::EnableStencilTest( const GRAPHIC_SYSTEM_COMPARE_OPERATION operation, int ref, unsigned int mask ) {
    
    #error "TODO IMPLEMENT"
}
void GRAPHIC_SYSTEM::DisableStencil() {
    
    #error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::SetStencilOperation( const GRAPHIC_POLYGON_FACE face, const GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION stencil_fail, const GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION stencil_pass, const GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION stencil_and_depth_fail ) {
    
    #error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::EnableBlend( const GRAPHIC_SYSTEM_BLEND_OPERATION source, const GRAPHIC_SYSTEM_BLEND_OPERATION destination ) {
    
    #error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::DisableBlend() {
    
    #error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::SetBlendFunction( const GRAPHIC_SYSTEM_BLEND_EQUATION equation ) {
    
    #error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::EnableDepthTest( const GRAPHIC_SYSTEM_COMPARE_OPERATION operation, bool mask, float range_begin, float range_end ) {
    
    #error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::EnableBackfaceCulling( const GRAPHIC_POLYGON_FACE face ) {
    
    #error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::DisableFaceCulling() {
    
    #error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::UpdateVertexBuffer( GRAPHIC_MESH * mesh, CORE_DATA_BUFFER & data ) {
    
    #error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::SetPolygonMode( const GRAPHIC_SYSTEM_POLYGON_FILL_MODE fill_mode ) {
    
    #error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::DisableDepthTest() {
    
    #error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::ReleaseTexture( GRAPHIC_TEXTURE * texture ) {
    
    #error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::CreateTexture( GRAPHIC_TEXTURE * texture ) {
    
    #error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::SetTextureOptions( GRAPHIC_TEXTURE * texture, GRAPHIC_TEXTURE_FILTERING filtering, GRAPHIC_TEXTURE_WRAP wrap, const CORE_HELPERS_COLOR & color ) {
    
    #error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::CreateFrameBuffer( GRAPHIC_RENDER_TARGET * target, GRAPHIC_RENDER_TARGET_FRAMEBUFFER_MODE mode ) {
    
    #error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::CreateDepthBuffer( GRAPHIC_RENDER_TARGET * target, int width, int height ) {
    
    #error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::CreateDepthTexture( GRAPHIC_TEXTURE * texture, GRAPHIC_TEXTURE_IMAGE_TYPE type ) {
    
    #error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::CreateTexture( GRAPHIC_TEXTURE * texture, void * texture_data, bool generate_mipmap ) {
    
    #error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::CreateSubTexture( GRAPHIC_TEXTURE * sub_texture, const GRAPHIC_TEXTURE & texture, const CORE_MATH_VECTOR & offset, const CORE_MATH_VECTOR & size, const void * data ) {
    
    #error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::ApplyTexture( GRAPHIC_TEXTURE * texture, int texture_index, int shader_texture_attribute_index ) {
    
    #error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::ApplyDepthTexture( GRAPHIC_TEXTURE * texture, int texture_index, int shader_texture_attribute_index ) {
    
    #error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::DiscardTexture( GRAPHIC_TEXTURE * texture ) {
    
    #error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::ApplyLightDirectional( const GRAPHIC_SHADER_LIGHT & light, GRAPHIC_SHADER_PROGRAM & program ) {
    
    #error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::ApplyLightAmbient( const GRAPHIC_SHADER_LIGHT & light, GRAPHIC_SHADER_PROGRAM & program ) {
    
    #error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::ApplyLightPoint( const GRAPHIC_SHADER_LIGHT & light, GRAPHIC_SHADER_PROGRAM & program, int index ) {
    
    #error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::ApplyLightSpot( const GRAPHIC_SHADER_LIGHT & light, GRAPHIC_SHADER_PROGRAM & program, int index ) {
    
    #error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::ApplyShaderAttributeVector( const float * vector, GRAPHIC_SHADER_ATTRIBUTE & attribute ) {
    
    #error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::ApplyShaderAttributeFloat( const float value, GRAPHIC_SHADER_ATTRIBUTE & attribute ) {
    
    #error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::ApplyShaderAttributeVectorTable( const float * vector, int size, GRAPHIC_SHADER_ATTRIBUTE & attribute ) {
    
    #error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::ApplyShaderAttributeMatrix( const float * matrix, GRAPHIC_SHADER_ATTRIBUTE & attribute ) {
    
    #error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::CreateVertexBuffer(GRAPHIC_MESH &mesh) {
    
    mesh.
    
    _mtlVertexDescriptor = [[MTLVertexDescriptor alloc] init];
    
    _mtlVertexDescriptor.attributes[VertexAttributePosition].format = MTLVertexFormatFloat3;
    _mtlVertexDescriptor.attributes[VertexAttributePosition].offset = 0;
    _mtlVertexDescriptor.attributes[VertexAttributePosition].bufferIndex = BufferIndexMeshPositions;
    
    _mtlVertexDescriptor.attributes[VertexAttributeTexcoord].format = MTLVertexFormatFloat2;
    _mtlVertexDescriptor.attributes[VertexAttributeTexcoord].offset = 0;
    _mtlVertexDescriptor.attributes[VertexAttributeTexcoord].bufferIndex = BufferIndexMeshGenerics;
    
    _mtlVertexDescriptor.layouts[BufferIndexMeshPositions].stride = 12;
    _mtlVertexDescriptor.layouts[BufferIndexMeshPositions].stepRate = 1;
    _mtlVertexDescriptor.layouts[BufferIndexMeshPositions].stepFunction = MTLVertexStepFunctionPerVertex;
    
    _mtlVertexDescriptor.layouts[BufferIndexMeshGenerics].stride = 8;
    _mtlVertexDescriptor.layouts[BufferIndexMeshGenerics].stepRate = 1;
    _mtlVertexDescriptor.layouts[BufferIndexMeshGenerics].stepFunction = MTLVertexStepFunctionPerVertex;
    
    #error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::CreateIndexBuffer(GRAPHIC_MESH &mesh) {
    
    #error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::ApplyBuffers(GRAPHIC_MESH & mesh) {
    
    #error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::ReleaseBuffers(GRAPHIC_MESH &mesh) {
    
    #error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::Clear() {
    
    #error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::ClearFrambufferDepth( float default_depth ) {
    
    #error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::ClearFrambufferColor() {
    
    #error "TODO IMPLEMENT"
}

void GRAPHIC_SYSTEM::ClearFrambufferStencil() {
    
    #error "TODO IMPLEMENT"
}
#endif
