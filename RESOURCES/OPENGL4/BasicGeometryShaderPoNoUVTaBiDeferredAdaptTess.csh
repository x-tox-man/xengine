#version 410 core

// define the number of CPs in the output patch
layout (vertices = 1) out;

//uniform float gTessellationLevel = 0;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 ModelMatrix;
//uniform sampler2D c_texture;
//uniform sampler2D n_texture;
//uniform sampler2D d_texture;
//uniform sampler2D d_texture1;
//uniform sampler2D d_texture2;
//uniform float cascadeEndClipSpace[3];

in vec4 WorldPos0_CS_IN[];
in vec2 texCoord_CS_IN[];
in vec4 o_normal_CS_IN[];
//in vec4 ShadowCoord_CS_IN[][3];
//in mat3 TBNMatrix_p_CS_IN[];


struct OutputPatch
{
    vec3 WorldPos_B030;
    vec3 WorldPos_B021;
    vec3 WorldPos_B012;
    vec3 WorldPos_B003;
    vec3 WorldPos_B102;
    vec3 WorldPos_B201;
    vec3 WorldPos_B300;
    vec3 WorldPos_B210;
    vec3 WorldPos_B120;
    vec3 WorldPos_B111;
    vec4 Normal[3];
    vec2 TexCoord[3];
    //vec4 ShadowCoord_ES_in[3];
    //mat3 TBNMatrix_p_ES_in;
};

// attributes of the output CPs
patch out OutputPatch oPatch;

vec3 ProjectToPlane(vec3 Point, vec3 PlanePoint, vec3 PlaneNormal)
{
    vec3 v = Point - PlanePoint;
    float Len = dot(v, PlaneNormal);
    vec3 d = Len * PlaneNormal;
    return (Point - d);
}

void CalcPositions()
{
    // The original vertices stay the same
    oPatch.WorldPos_B030 = WorldPos0_CS_IN[0].xyz;
    oPatch.WorldPos_B003 = WorldPos0_CS_IN[1].xyz;
    oPatch.WorldPos_B300 = WorldPos0_CS_IN[2].xyz;

    // Edges are names according to the opposing vertex
    vec3 EdgeB300 = oPatch.WorldPos_B003 - oPatch.WorldPos_B030;
    vec3 EdgeB030 = oPatch.WorldPos_B300 - oPatch.WorldPos_B003;
    vec3 EdgeB003 = oPatch.WorldPos_B030 - oPatch.WorldPos_B300;

    // Generate two midpoints on each edge
    oPatch.WorldPos_B021 = oPatch.WorldPos_B030 + EdgeB300 / 3.0;
    oPatch.WorldPos_B012 = oPatch.WorldPos_B030 + EdgeB300 * 2.0 / 3.0;
    oPatch.WorldPos_B102 = oPatch.WorldPos_B003 + EdgeB030 / 3.0;
    oPatch.WorldPos_B201 = oPatch.WorldPos_B003 + EdgeB030 * 2.0 / 3.0;
    oPatch.WorldPos_B210 = oPatch.WorldPos_B300 + EdgeB003 / 3.0;
    oPatch.WorldPos_B120 = oPatch.WorldPos_B300 + EdgeB003 * 2.0 / 3.0;

    // Project each midpoint on the plane defined by the nearest vertex and its normal
    oPatch.WorldPos_B021 = ProjectToPlane(oPatch.WorldPos_B021, oPatch.WorldPos_B030,
                                          oPatch.Normal[0].xyz);
    oPatch.WorldPos_B012 = ProjectToPlane(oPatch.WorldPos_B012, oPatch.WorldPos_B003,
                                         oPatch.Normal[1].xyz);
    oPatch.WorldPos_B102 = ProjectToPlane(oPatch.WorldPos_B102, oPatch.WorldPos_B003,
                                         oPatch.Normal[1].xyz);
    oPatch.WorldPos_B201 = ProjectToPlane(oPatch.WorldPos_B201, oPatch.WorldPos_B300,
                                         oPatch.Normal[2].xyz);
    oPatch.WorldPos_B210 = ProjectToPlane(oPatch.WorldPos_B210, oPatch.WorldPos_B300,
                                         oPatch.Normal[2].xyz);
    oPatch.WorldPos_B120 = ProjectToPlane(oPatch.WorldPos_B120, oPatch.WorldPos_B030,
                                         oPatch.Normal[0].xyz);

    // Handle the center
    vec3 Center = (oPatch.WorldPos_B003 + oPatch.WorldPos_B030 + oPatch.WorldPos_B300) / 3.0;
    oPatch.WorldPos_B111 = (oPatch.WorldPos_B021 + oPatch.WorldPos_B012 + oPatch.WorldPos_B102 +
                          oPatch.WorldPos_B201 + oPatch.WorldPos_B210 + oPatch.WorldPos_B120) / 6.0;
    oPatch.WorldPos_B111 += (oPatch.WorldPos_B111 - Center) / 2.0;

    //oPatch.ShadowCoord_ES_in[0] = ShadowCoord_CS_IN[0][0];
    //oPatch.ShadowCoord_ES_in[1] = ShadowCoord_CS_IN[0][1];
    //oPatch.ShadowCoord_ES_in[2] = ShadowCoord_CS_IN[0][2];
    //oPatch.TBNMatrix_p_ES_in = TBNMatrix_p_CS_IN[0];
}

void main()
{
    // Set the control points of the output patch
    for (int i = 0 ; i < 3 ; i++) {
       oPatch.Normal[i] = o_normal_CS_IN[i];
       oPatch.TexCoord[i] = texCoord_CS_IN[i];
    }

    CalcPositions();

    // Calculate the tessellation levels
    gl_TessLevelOuter[0] = 1;
    gl_TessLevelOuter[1] = 1;
    gl_TessLevelOuter[2] = 1;
    gl_TessLevelInner[0] = 1;
}