#version 330 core
out vec4 FragColor;

//create objColor variable
uniform vec3 objectColor;
//create lightColor variable
uniform vec3 lightColor;

void main()
{        
    
    FragColor = vec4(lightColor * objectColor, 1.0); 
}   