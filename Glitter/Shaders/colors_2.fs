#version 330 core
out vec4 FragColor;

//create objColor variable
uniform vec3 objectColor;
//create lightColor variable
uniform vec3 lightColor;
//create lightPos variable
uniform vec3 lightPos;
//create norm variable
in vec3 Normal;
//create FragPos variable
in vec3 FragPos;


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
    //update the result
    vec3 result = (diffuse + ambient) * objectColor;    
    FragColor = vec4(result, 1.0);
}   