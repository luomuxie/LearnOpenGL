#version 330 core
out vec4 FragColor;

in vec2 texCoord;

//uniform sampler2D ourTexture;
//create color for light
uniform vec3 lightColor;

void main()
{        
    //set the color of the fragment
    FragColor = vec4(lightColor, 1.0f);
}   