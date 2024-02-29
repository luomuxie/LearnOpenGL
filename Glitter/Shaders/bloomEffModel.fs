#version 330 core
//out float FragColor;
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

//in vec2 texCoord;
in vec2 Texcoords;

// texture sampler diffuse
uniform sampler2D texture_diffuse;
//texture sampler specular;
uniform sampler2D texture_specular;
//create a time
uniform float time;

//create main
void main(){
    FragColor = texture(texture_diffuse,Texcoords) + texture(texture_specular,Texcoords);

    //calculate the BrightColor
    float factor = sin(time) * 0.5 + 0.5;
    BrightColor = vec4(factor*15, 0.0f, 0.0f, 1.0);
   
}


