#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

//txture for position
uniform sampler2D gPosition;
//texture for normal
uniform sampler2D gNormal;
//texture for albedo
uniform sampler2D gAlbedoSpec;

//create a light struct
struct Light {
    vec3 Position;
    vec3 Color;

    //attenuation factors
    float Quadratic;
    float Linear;
};

//create a const to store the light cnt
const int NR_LIGHTS = 32;
//create an array of lights
uniform Light lights[NR_LIGHTS];

//create a uniform for the view pos
uniform vec3 viewPos;


void main(){

    //retrieve data from gbuffer
    vec3 FragPos = texture(gPosition, TexCoords).rgb;
    vec3 Normal = texture(gNormal, TexCoords).rgb;
    vec3 diffuse = texture(gAlbedoSpec, TexCoords).rgb;
    float Specular = texture(gAlbedoSpec, TexCoords).a;

    //then calculate lighting as usual
    vec3 lighting = diffuse*0.1;

    //view direction
    vec3 viewDir = normalize(viewPos - FragPos);

    //iterate over all the lights and calculate the lighting
    for(int i = 0; i < NR_LIGHTS; i++)
    {
        //diffuse
        vec3 lightDir = normalize(lights[i].Position - FragPos);
        float diff = max(dot(Normal, lightDir), 0.0);
        vec3 diffuse = diff * diffuse * lights[i].Color;

        //specular
        vec3 halfwayDir = normalize(lightDir + viewDir);
        float spec = pow(max(dot(Normal, halfwayDir), 0.0), 16.0);
        vec3 specular =  spec * lights[i].Color*Specular;

        //attenuation
        float distance = length(lights[i].Position - FragPos);
        float attenuation = 1.0 / (1.0 + lights[i].Linear * distance + lights[i].Quadratic * distance * distance);
        
        
        ////add the diffuse and specular to the lighting
        diffuse *= attenuation;
        specular *= attenuation;

        lighting += diffuse +specular;        

    }

    //write final color to the default framebuffer
    FragColor = vec4(lighting, 1.0);

}

