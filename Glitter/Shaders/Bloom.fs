#version 330 core
out vec4 FragColor;

//in vec2 texCoord;
in VS_OUT {
    vec2 TexCoord;
    vec3 Normal;
    vec3 FragPos;
} fs_in;


uniform sampler2D ourTexture;
//create a light struct
struct Light {
    vec3 Position;
    vec3 Color;
};

//create a light's array and the number of lights 
uniform Light lights[4];
//create a view pos
uniform vec3 viewPos;



void main()
{    
    //FragColor = texture(ourTexture, fs_in.TexCoord);
    //set the color of the fragment
    //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    //create a color to store the color of the texture
    
    vec4 color = texture(ourTexture, fs_in.TexCoord);
    //normalize the normal
    vec3 norm = normalize(fs_in.Normal);

    //caculate the ligth
    vec3 result = vec3(0.0f);
    //ambient
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength*vec3(1.0f);
    //diffuse
    //create a val to store the diffuse
    vec3 diffuse = vec3(0.0f);

    //create a val to store the specular
    vec3 specular = vec3(0.0f);
    for(int i = 0; i < 4; i++)
    {
        //diffuse
        vec3 lightDir = normalize(lights[i].Position - fs_in.FragPos);
        float diff = max(dot(norm, lightDir), 0.0f);
        diffuse += diff * lights[i].Color;

        //attenuation
        float distance = length(lights[i].Position - fs_in.FragPos);
        float attenuation = 1.0 / (1.0 + 0.09 * distance + 0.032 * (distance * distance));
        diffuse *= attenuation;      

        //specular
        //float specularStrength = 0.5f;
        //vec3 viewDir = normalize(viewPos - fs_in.FragPos);
        //vec3 reflectDir = reflect(-lightDir, norm);
        //float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        //specular += specularStrength * spec * lights[i].Color;
     }

    result = (ambient + diffuse) * color.rgb;
    FragColor = vec4(result, 1.0f);
}    