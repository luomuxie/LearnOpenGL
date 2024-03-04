#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse;

uniform sampler2D texture_specular;

void main()
{    
    FragColor = texture(texture_diffuse, TexCoords)+texture(texture_specular, TexCoords);
    //FragColor = texture(texture_specular, TexCoords);
}