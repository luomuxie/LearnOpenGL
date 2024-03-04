#version 330 core
//out vec4 FragColor;
layout(location = 0) out vec4 gPosition;
layout(location = 1) out vec3 gNormal;
layout(location = 2) out vec4 gAlbedoSpec;


in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D texture_diffuse;

uniform sampler2D texture_specular;

void main()
{    
    //store the fragment position vector in the gPosition texture
    gPosition = vec4(FragPos, 1.0);
    //store the normal vector in the gNormal texture
    gNormal = Normal;
    //store the color of the fragment in the gAlbedoSpec texture
    gAlbedoSpec.rgb = texture(texture_diffuse, TexCoords).rgb;
    gAlbedoSpec.a = texture(texture_specular, TexCoords).r;

}