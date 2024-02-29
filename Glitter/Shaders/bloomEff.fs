#version 330 core
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;


//get the struct from the vertex shader
in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;

//create a light struct
struct Light {
    vec3 Position;
    vec3 Color;
};

//create a light's array and the number of lights
uniform Light lights[4];

uniform sampler2D ourTexture;

//create a main
void main()
{
    //create a color to store the color of the texture
    vec4 color = texture(ourTexture, fs_in.TexCoords);

    //normalize the normal
    vec3 norm = normalize(fs_in.Normal);

    //caculate the ligth
    vec3 result = vec3(0.0f);
    //ambient
    vec3 ambient = vec3(0.0f);

    //diffuse
    //create a val to store the diffuse
    vec3 diffuse = vec3(0.0f);

    for(int i = 0; i < 4; i++)
    {
        //diffuse
        vec3 lightDir = normalize(lights[i].Position - fs_in.FragPos);
        float diff = max(dot(norm, lightDir), 0.0f);
        vec3 result = lights[i].Color * diff;

        //attenuation
        float distance = length(lights[i].Position - fs_in.FragPos);
        float attenuation = 1.0 / (distance * distance);
        result *= attenuation;
        diffuse += result;
    }

    result = color.rgb * (ambient + diffuse);
    FragColor = vec4(result, 1.0f);

    //create a val to store the val of dot
    float brightness = dot(FragColor.rgb, vec3(0.2126, 0.7152, 0.0722));
    //check if the brightness is greater than 1
    if(brightness > 1.0)
    {
        //set the brightColor to the FragColor
        BrightColor = vec4(FragColor.rgb, 1.0);
    }
    else
    {
        //set the brightColor to black
        BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
    }

    
}


