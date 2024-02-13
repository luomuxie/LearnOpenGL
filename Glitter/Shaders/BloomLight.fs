#version 330 core
out vec4 FragColor;

//in vec2 texCoord;
in VS_OUT {
    vec2 TexCoord;
    vec3 Normal;
    vec3 FragPos;
} fs_in;

//create a val for lightColor
uniform vec3 lightColor;

void main()
{    
      FragColor = vec4(lightColor, 1.0);
}    