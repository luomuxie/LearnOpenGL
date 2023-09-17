#version 330 core
out vec4 FragColor;

//create objColor variable
uniform vec3 objectColor;
//create lightColor variable
uniform vec3 lightColor;
//create lightPos variable
uniform vec3 lightPos;
//create viewPos variable
uniform vec3 viewPos;


//create norm variable
in vec3 Normal;
//create FragPos variable
in vec3 FragPos;

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


void main()
{        
    
    //FragColor = vec4(lightColor * objectColor, 1.0); 
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    //vec3 result = ambient * objectColor;
    //cal the lightDir
    vec3 lightDir = normalize(lightPos - FragPos);
    //normalize the norm
    vec3 norm = normalize(Normal);
    //cal the diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    //cal the diffuse color
    vec3 diffuse = diff * lightColor;    

    //create specularStrength variable
    float specularStrength = 0.5;
    //create viewDir variable
    vec3 viewDir = normalize(viewPos - FragPos);
    //create reflectDir variable
    vec3 reflectDir = reflect(-lightDir, norm);
    //create spec variable
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    //create specular variable
    vec3 specular = specularStrength * spec * lightColor;

    //update the result
    vec3 result = (diffuse + ambient + specular ) * objectColor;    
    FragColor = vec4(result, 1.0);
}   