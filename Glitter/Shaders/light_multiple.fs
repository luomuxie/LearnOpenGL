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


//create dirLight struct
struct DirLight
{
    //create a vec3 for the direction
    vec3 direction;
    //create a vec3 for the ambient color
    vec3 ambient;
    //create a vec3 for the diffuse color
    vec3 diffuse;
    //create a vec3 for the specular color
    vec3 specular;
};



//create pointLight struct
struct PointLight
{
    //create a vec3 for the position
    vec3 position;

    //create a vec3 for the ambient color
    vec3 ambient;
    //create a vec3 for the diffuse color
    vec3 diffuse;
    //create a vec3 for the specular color
    vec3 specular;

    //create a float for the constant
    float constant;
    //create a float for the linear
    float linear;
    //create a float for the quadratic
    float quadratic;
};

#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);

out vec4 FragColor;

//create norm variable
in vec3 Normal;
//create FragPos variable
in vec3 FragPos;
//create TexCoords variable
in vec2 TexCoords;

//create material
uniform Material material;
//create viewPos(camera's position)
uniform vec3 viewPos;
//create dirLight
uniform DirLight light;

void main()
{
    //normalize the normal    
    vec3 normal = normalize(Normal);
    //create viewDir
    vec3 viewDir = normalize(viewPos - FragPos);

    //use the CalcDirLight function to calculate the dirLight
    vec3 result = CalcDirLight(light, normal, viewDir);

    //cal the pointLight
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
    {
        //use the CalcPointLight function to calculate the pointLight
        result += CalcPointLight(pointLights[i], normal, FragPos, viewDir);
    }

    //set the FragColor to the result
    FragColor = vec4(result, 1.0);            
}

//create a function to calculate the direction light
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    //cal ambient
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

    //cal diffuse
    float diff = max(dot(normal, light.direction), 0.0);    
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;

    //cal specular
    vec3 reflectDir = reflect(-light.direction, normal);    
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);    
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

    //return the ambient + diffuse + specular
    return (ambient + diffuse + specular);
}

//create a function to calculate the point light
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    //create a vec3 for the lightDir
    vec3 lightDir = normalize(light.position - fragPos);

    //cal diffuse
    float diff = max(dot(normal, lightDir), 0.0);    
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;

    //cal specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);    
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

    //cal ambient
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

    //cal attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    //return the ambient + diffuse + specular
    return (ambient + diffuse + specular) * attenuation;
}
