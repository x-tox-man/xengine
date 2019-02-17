#version 330

in vec2 TexCoord;

out vec3 SSAO;

uniform sampler2D c_texture; //Position
uniform sampler2D c_texture_1; //Diffuse
uniform sampler2D c_texture_2; //Normal
uniform sampler2D c_texture_3; //Shadow
uniform sampler2D c_texture_4; //SSAO
uniform sampler2D c_texture_5; //random noise
uniform mat4 SSAOViewProjectionMatrix;
uniform mat4 ViewMatrix;
uniform float SSAOSampleRad = 1.5;

const int MAX_KERNEL_SIZE = 64;
const float SSAO_FACTOR = 1.0 / MAX_KERNEL_SIZE;
uniform vec4 SSAOKernel[MAX_KERNEL_SIZE];

void main()
{
    const vec2 noiseScale = vec2(1024.0/4.0, 768.0/4.0); // screen = 1024*768

    vec3 Pos    = texture(c_texture, TexCoord).xyz;
    vec3 Color = texture( c_texture_1, TexCoord ).xyz;
    vec3 Normal = (ViewMatrix * vec4( texture( c_texture_2, TexCoord).xyz, 0.0 )).xyz;
    vec3 randomVec = texture( c_texture_5, TexCoord * noiseScale).xyz;  

    vec3 tangent   = normalize(randomVec - Normal * dot(randomVec, Normal));
    vec3 bitangent = cross(Normal, tangent);
    mat3 TBN       = mat3(tangent, bitangent, Normal);  

    SSAO = vec3(0.0);

    for (int i = 0 ; i < MAX_KERNEL_SIZE ; i++) {

        vec3 samplePos = Pos + SSAOKernel[i].xyz;//;( TBN * SSAOKernel[i].xyz ) * SSAOSampleRad;
        vec4 offset = vec4(samplePos, 1.0); // make it a 4-vector

        offset = SSAOViewProjectionMatrix * offset; // project on the near clipping plane
        offset.xy /= offset.w; // perform perspective divide
        offset.xy = (offset.xy * 0.5) + vec2(0.5); // transform to (0,1) range

        float sampleDepth = texture(c_texture, offset.xy).z;
        
        if (abs(Pos.z - sampleDepth) < SSAOSampleRad) {
            SSAO += step(sampleDepth,samplePos.z);
        }
    }

    SSAO = (1.0 - (SSAO * SSAO_FACTOR));

    SSAO = vec3(pow(SSAO.r, 2.0));
}