#version 410 core

// define the number of CPs in the output patch
layout (vertices = 3) out;

uniform vec3 gEyeWorldPos;

// attributes of the input CPs
in vec4 WorldPos0_CS_IN[];
in vec2 texCoord_CS_IN[];
in vec4 o_normal_CS_IN[];
in vec4 ShadowCoord_CS_IN[][3];
in mat3 TBNMatrix_p_CS_IN[];

// attributes of the output CPs
out vec4 WorldPos_ES_in[];
out vec2 TexCoord_ES_in[];
out vec4 Normal_ES_in[];
out vec4 ShadowCoord_ES_in[][3];
out mat3 TBNMatrix_p_ES_in[];

float GetTessLevel(float Distance0, float Distance1)
{
    float AvgDistance = (Distance0 + Distance1) / 2.0;

    if (AvgDistance <= 2.0) {
        return 10.0;
    }
    else if (AvgDistance <= 5.0) {
        return 7.0;
    }
    else {
        return 3.0;
    }
}

void main()
{
    // Set the control points of the output patch
    WorldPos_ES_in[gl_InvocationID] = WorldPos0_CS_IN[gl_InvocationID];
    TexCoord_ES_in[gl_InvocationID] = texCoord_CS_IN[gl_InvocationID];
    Normal_ES_in[gl_InvocationID] = o_normal_CS_IN[gl_InvocationID];

	ShadowCoord_ES_in[gl_InvocationID][0] = ShadowCoord_CS_IN[gl_InvocationID][0];
	ShadowCoord_ES_in[gl_InvocationID][1] = ShadowCoord_CS_IN[gl_InvocationID][1];
	ShadowCoord_ES_in[gl_InvocationID][2] = ShadowCoord_CS_IN[gl_InvocationID][2];
    TBNMatrix_p_ES_in[gl_InvocationID] = TBNMatrix_p_CS_IN[gl_InvocationID];

    // Calculate the distance from the camera to the three control points
    float EyeToVertexDistance0 = distance(gEyeWorldPos, WorldPos_ES_in[0].xyz);
    float EyeToVertexDistance1 = distance(gEyeWorldPos, WorldPos_ES_in[1].xyz);
    float EyeToVertexDistance2 = distance(gEyeWorldPos, WorldPos_ES_in[2].xyz);

    // Calculate the tessellation levels
    gl_TessLevelOuter[0] = 3;//GetTessLevel(EyeToVertexDistance1, EyeToVertexDistance2);
    gl_TessLevelOuter[1] = 3;//GetTessLevel(EyeToVertexDistance2, EyeToVertexDistance0);
    gl_TessLevelOuter[2] = 3;//GetTessLevel(EyeToVertexDistance0, EyeToVertexDistance1);
    gl_TessLevelInner[0] = gl_TessLevelOuter[2];
}