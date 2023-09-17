#version 330 core
//create a Material struct
struct Material
{
    //create a vec3 for the ambient color
    vec3 ambient;
    //create a vec3 for the diffuse color
    vec3 diffuse;
    //create a vec3 for the specular color
    vec3 specular;
    //create a float for the shininess
    float shininess;
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
};



out vec4 FragColor;

//create norm variable
in vec3 Normal;
//create FragPos variable
in vec3 FragPos;

//create material
uniform Material material;
//create light
uniform Light light;


uniform vec3 viewPos;


void main()
{            
    //FragColor = vec4(lightColor * objectColor, 1.0);     
    vec3 ambient =  material.ambient * light.ambient;   
    //cal the lightDir
    vec3 lightDir = normalize(light.position - FragPos);
    //normalize the norm
    vec3 norm = normalize(Normal);
    //cal the diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    //cal the diffuse color
    vec3 diffuse = (diff * material.diffuse)*light.diffuse;    

    //create specularStrength variable
    float specularStrength = 0.5;
    //create viewDir variable
    vec3 viewDir = normalize(viewPos - FragPos);
    //create reflectDir variable
    vec3 reflectDir = reflect(-lightDir, norm);
    //create spec variable
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    //create specular variable
    vec3 specular = spec*(material.specular) * light.specular;

    //update the result
    vec3 result = diffuse + ambient + specular ;    
    FragColor = vec4(result, 1.0);
}   