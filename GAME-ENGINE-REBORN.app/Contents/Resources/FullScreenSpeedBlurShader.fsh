#version 330

uniform sampler2D c_texture;
uniform sampler2D d_texture;

uniform mat4 PreviousModelViewProjection;
uniform mat4 InverseCurrentModelView;
uniform vec4 ViewRay; // for extracting current world space position

in vec2 textureCoordinates;

out vec4 colorOut;

void main() {
    
    // Get the depth buffer value at this pixel.
    float zOverW = texture( d_texture, textureCoordinates ).r;
    
    // H is the viewport position at this pixel in the range -1 to 1.
    vec4 H = vec4(textureCoordinates.x * 2 - 1, (textureCoordinates.y) * 2 - 1, zOverW, 1);
    
    // Transform by the view-projection inverse.
    vec4 D = H * InverseCurrentModelView;
    // Divide by w to get the world position.
    vec4 worldPos = D / D.w;
    
    // Current viewport position
    vec4 currentPos = H;
    // Use the world position, and transform by the previous view-
    // projection matrix.
    vec4 previousPos = worldPos * PreviousModelViewProjection;
    // Convert to nonhomogeneous points [-1,1] by dividing by w.
    previousPos /= previousPos.w;
    // Use this frame's position and last frame's to compute the pixel
    // velocity.
    vec3 velocity = (currentPos-previousPos ).xyz* 0.01;
    
    // Get the initial color at this pixel.
    
    int nSamples = 5;
    
    vec4 color = texture(c_texture, textureCoordinates);
    vec2 texCoord = textureCoordinates + velocity.xy;
    
    for(int i = 1; i < nSamples; ++i, texCoord += velocity.xy)
    {
        // Sample the color buffer along the velocity vector.
        vec4 currentColor = texture(c_texture, texCoord);
        // Add the current color to our color sum.
        color += currentColor;
    }
    // Average all of the samples to get the final blur color.
    
    // Average all of the samples to get the final blur color.
    colorOut = color / nSamples;
    
    // get current world space position:
    /*vec4 current = ViewRay * texture(d_texture, textureCoordinates).r;
    current = InverseCurrentModelView * current;
    
    // get previous screen space position:
    vec4 previous = PreviousModelViewProjection * current;
    previous.xyz /= previous.w;
    previous.xy = previous.xy * 0.5 + 0.5;
    
    vec2 blurVec = previous.xy - textureCoordinates;
    
    int nSamples = 8;
    
    // perform blur:
    vec4 result = texture(c_texture, textureCoordinates);
    for (int i = 1; i < nSamples; ++i) {
        // get offset in range [-0.5, 0.5]:
        vec2 offset = blurVec * (float(i) / float(nSamples - 1) - 0.5);
        
        // sample & add to result:
        result += texture(c_texture, textureCoordinates + offset);
    }
    
    result /= float(nSamples);
    colorOut = result;*/
    
    colorOut.a = 1;
}

