#version 330 core
out vec4 FragColor;

in vec2 texCoord;
uniform sampler2D ourTexture;

void main()
{    
    FragColor = texture(ourTexture, texCoord);
    //set the color of the fragment
    //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}   