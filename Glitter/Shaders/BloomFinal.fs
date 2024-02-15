#version 330 core
out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D scene;
//create a simpler2d for the bloomblur
uniform sampler2D bloomBlur;
//create a val for the bloom
uniform bool bloom;
//create a val for the exposure
uniform float exposure;


void main()
{    
    //create a val to store the color of the scene
    vec3 hdrColor = texture(scene, texCoord).rgb;
    //create a val to store the color of the bloomblur
    vec3 bloomColor = texture(bloomBlur, texCoord).rgb;
    //check if the bloom is true
    if(bloom)
    {
        //add the color of the bloom to the hdrColor
        hdrColor += bloomColor;
    }
    //create a val to store the final color
    vec3 result = vec3(1.0) - exp(-hdrColor * exposure);
    //set the color of the fragment

    //gamma correct
    result = pow(result, vec3(1.0/2.2));
    FragColor = vec4(result, 1.0);
}    