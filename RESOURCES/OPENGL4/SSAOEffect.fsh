#version 330

in vec2 TexCoord;

out vec3 SSAO;

uniform sampler2D c_texture; //Position
uniform sampler2D c_texture_1; //Diffuse
uniform sampler2D c_texture_2; //Normal
uniform sampler2D c_texture_3; //Shadow
uniform sampler2D c_texture_4; //SSAO
uniform mat4 ProjectionMatrix;
uniform float SSAOSampleRad = 0.2;

const int MAX_KERNEL_SIZE = 64;
const float SSAO_FACTOR = 1.0 / MAX_KERNEL_SIZE;
uniform vec4 SSAOKernel[MAX_KERNEL_SIZE];

void main()
{
    vec3 Pos = texture(c_texture, TexCoord).xyz;
    vec3 Color = texture( c_texture_1, TexCoord ).xyz;
    vec3 Normal = texture(c_texture_2, TexCoord).xyz;

    vec3 tangent   = Normal;//normalize(randomVec - Normal * dot(randomVec, Normal));
    vec3 bitangent = cross(Normal, tangent);
    mat3 TBN       = mat3(tangent, bitangent, Normal);  

    SSAO = vec3(0.0);

    for (int i = 0 ; i < MAX_KERNEL_SIZE ; i++) {

        vec3 samplePos = Pos + (SSAOKernel[i].xyz * SSAOSampleRad) ; // generate a random point
        //samplePos = Pos;// + (SSAOKernel[i].xyz * SSAOSampleRad) ; // generate a random point
        vec4 offset = vec4(samplePos, 1.0); // make it a 4-vector

        offset = ProjectionMatrix * offset; // project on the near clipping plane
        offset.xy /= offset.w; // perform perspective divide
        offset.xy = (offset.xy * 0.5) + 0.5; // transform to (0,1) range

        float sampleDepth = texture(c_texture, offset.xy).y;
        
        if (abs(Pos.y - sampleDepth) < SSAOSampleRad) {
            SSAO += step(sampleDepth,samplePos.y);
        }

        //SSAO = offset.yyy;//vec3(sampleDepth);
    }

    SSAO = (1.0 - (SSAO * SSAO_FACTOR));
}