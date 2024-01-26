#version 330 core
out vec4 FragColor;

//in vec2 texCoord;
//create a block  for the vertex data to allow for multiple vertex attributes
in VS_OUT
{
    vec3 FragPos;
    vec2 TexCoords;    
} fs_in;



uniform sampler2D ourTexture;
uniform sampler2D normalMap;

//lighting
uniform vec3 lightPos;
//view pos
uniform vec3 viewPos;


void main()
{    
    //create a color
    vec3 color = texture(ourTexture,fs_in.TexCoords).rgb;
    //create ambient light
    vec3 ambient = 0.1 * color;
    //create normal vector
    vec3 normal = normalize(texture(normalMap, fs_in.TexCoords).rgb * 2.0 - 1.0);

    //create light direction
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);

    //create diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * color;


    //create specular shading
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = vec3(0.2) * spec;

    //return the color of the fragment
    FragColor = vec4(ambient + diffuse + specular, 1.0);

}   