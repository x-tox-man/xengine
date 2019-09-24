#version 330

uniform sampler2D c_texture;

uniform float BloomThreshold;

in vec2 textureCoordinates;

out vec4 colorOut;

void main() {
    
    // Look up the original image color.
    vec4 c = texture(c_texture, textureCoordinates);
    vec4 tresh = vec4(BloomThreshold);
    
    // Adjust it to keep only values brighter than the specified threshold.
    colorOut = clamp( (c - tresh) / (1 - tresh), vec4(0.0), vec4(1.0) );
}

