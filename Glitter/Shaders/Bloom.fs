#version 330 core
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

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
    vec3 ambient = vec3(0.0f);
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
        vec3 result = lights[i].Color * diff;
        

        //attenuation
        float distance = length(lights[i].Position - fs_in.FragPos);
        float attenuation = 1.0 / (distance * distance);
        result *= attenuation;
        diffuse += result;
                
     }

    result = (ambient + diffuse) * color.rgb;
    FragColor = vec4(result, 1.0f);

    //caculate the brightColor
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