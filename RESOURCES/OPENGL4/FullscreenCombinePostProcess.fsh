#version 330

uniform sampler2D c_texture;
uniform sampler2D c_texture_1;

uniform float BloomIntensity;
uniform float BaseIntensity;

uniform float BloomSaturation;
uniform float BaseSaturation;

in vec2 textureCoordinates;

out vec4 colorOut;

vec4 AdjustSaturation(vec4 color, float saturation)
{
    // The constants 0.3, 0.59, and 0.11 are chosen because the
    // human eye is more sensitive to green light, and less to blue.
    float grey = dot( vec3( color ), vec3( 0.3, 0.59, 0.11 ) );
    
    return mix( vec4(grey,grey,grey, 1), color, saturation );
}

void main() {
    
    // Look up the bloom and original base image colors.
    vec4 base = texture(c_texture, textureCoordinates);
    vec4 bloom1 = texture(c_texture_1, textureCoordinates);
    
    // Adjust color saturation and intensity.
    base = AdjustSaturation(base, BaseSaturation) * BaseIntensity;
    bloom1 = AdjustSaturation(bloom1, BloomSaturation) * BloomIntensity;
    
    // Darken down the base image in areas where there is a lot of bloom,
    // to prevent things looking excessively burned-out.
    bloom1 *= (1 - clamp(bloom1, 0.0, 1.0));
    
    // Combine the two images.
    colorOut = bloom1 + base;
    colorOut.a = 1;
}

