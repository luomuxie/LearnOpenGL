#version 330 core
//create a Material struct
struct Material
{    
    //create a float for the shininess
    float shininess;
    //create a sampler2D for the diffuse map
    sampler2D diffuse;
    //create a specular map
    sampler2D specular;        
};

//create a Light struct
struct Light
{
    //create a vec3 for the position
    vec3 position;

    //create a vec3 for the ambient color
    vec3 ambient;
    //create a vec3 for the diffuse color
    vec3 diffuse;
    //create a vec3 for the specular color
    vec3 specular;

    
    //create a float for the cutOff
    float cutOff;
    //create a float for the outerCutOff
    float outerCutOff;

    //create a vec3 for the direction
    vec3 direction;
    
};


out vec4 FragColor;

//create norm variable
in vec3 Normal;
//create FragPos variable
in vec3 FragPos;
//create TexCoords variable
in vec2 TexCoords;

//create material
uniform Material material;
//create light
uniform Light light;
//create viewPos(camera's position)
uniform vec3 viewPos;


void main()
{
    // ambient
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
    vec3 lightDir = normalize(light.position - FragPos);

    // diffuse 
    vec3 norm = normalize(Normal);        
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb; 

    //cal spot light
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    diffuse *= intensity;
    specular *= intensity;    
    

    vec3 result = ambient + diffuse+specular;
    FragColor = vec4(result, 1);
        
}   