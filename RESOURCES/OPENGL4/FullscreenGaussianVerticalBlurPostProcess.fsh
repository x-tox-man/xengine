#version 330

uniform sampler2D c_texture;

uniform float weight[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);
uniform vec4 FrameResolution;

in vec2 textureCoordinates;

out vec4 colorOut;

void main() {
    
    vec2 tex_offset = 1.0 / (textureSize(c_texture, 0) * FrameResolution.xy); // gets size of single texel
    vec2 txc = textureCoordinates * FrameResolution.xy;

    colorOut.rgb = texture(c_texture, txc).rgb * weight[0];
    
    for(int i = 1; i < 5; ++i)
    {
        colorOut.rgb += texture(c_texture, txc + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
        colorOut.rgb += texture(c_texture, txc - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
    }
    
    colorOut.a = 1;
}

