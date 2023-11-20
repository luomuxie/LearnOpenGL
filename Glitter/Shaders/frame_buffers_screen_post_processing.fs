#version 330 core
out vec4 FragColor;

in vec2 texCoord;
uniform sampler2D screenTexture;

void main()
{    
    //FragColor = texture(screenTexture, texCoord);

    //create a offset val 
    float offset = 1.0 / 300.0;
    //create a offset array to get the pixel around the current pixel
    vec2 offsets[9] = vec2[](
        vec2(-offset, offset), // top-left
        vec2(0.0f, offset), // top-center
        vec2(offset, offset), // top-right
        vec2(-offset, 0.0f), // center-left
        vec2(0.0f, 0.0f), // center-center
        vec2(offset, 0.0f), // center-right
        vec2(-offset, -offset), // bottom-left
        vec2(0.0f, -offset), // bottom-center
        vec2(offset, -offset) // bottom-right    
    );

    //create a kernel array to get the pixel around the current pixel
    //float kernel[9] = float[](
    //    -1, -1, -1,
    //    -1,  8, -1,
    //    -1, -1, -1
    //);

    //create a blur kernel
    //float kernel[9] = float[](
    //    1.0 / 16, 2.0 / 16, 1.0 / 16,
    //    2.0 / 16, 4.0 / 16, 2.0 / 16,
    //    1.0 / 16, 2.0 / 16, 1.0 / 16
    //);

    //create a sharpen kernel
    //float kernel[9] = float[](
    //    0, -1, 0,
    //    -1, 5, -1,
    //    0, -1, 0
    //);


    //create a array to store the color of the pixel around the current pixel
    vec3 sampleTex[9];
    //get the color of the pixel around the current pixel
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(screenTexture, texCoord.st + offsets[i]));        
    }

    //create a color
    vec3 color = vec3(0.0);
    //cal the sum of the pixel around the current pixel by the kernel
    for(int i = 0; i < 9; i++)
    {
        color += kernel[i] * sampleTex[i];
    }

    //set the color of the current pixel
    FragColor = vec4(color, 1.0);

}   