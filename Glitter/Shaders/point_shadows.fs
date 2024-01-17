#version 330 core
out vec4 FragColor;

//a in struct from the vertex shader
in VS_OUT
{
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;


//create unifrom for the diffuse map,depth map and light pos ,far_plane,viewPos
uniform sampler2D diffuseTexture;
uniform samplerCube depthMap;
uniform vec3 lightPos;
uniform float far_plane;
uniform vec3 viewPos;

//create unifrom for check if need shadow
uniform bool shadows;

//create a function to calculate the shadow
float ShadowCalculation(vec3 fragPos)
{
    //get vector between fragment position and light position
    vec3 fragToLight = fragPos - lightPos;
    //use the fragment to light vector to sample from the depth map    
    float closestDepth = texture(depthMap, fragToLight).r;
    //it is currently in linear range between [0,1]. Re-transform back to original value
    closestDepth *= far_plane;
    //now get current linear depth as the length between the fragment and light position
    float currentDepth = length(fragToLight);
    //now test for shadows
    float bias = 0.05; //we use a much larger bias since depth is now in [near_plane, far_plane] range
    float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;        

    return shadow;
}


void main()
{   
    vec3 lightColor = vec3(0.3);

    //ambient lighting
    vec3 ambient = vec3(0.3f, 0.3f, 0.3f)*lightColor;

    //create a color variable
    vec3 color = texture(diffuseTexture, fs_in.TexCoords).rgb;

    //cacular diffuse lighting
    vec3 norm = normalize(fs_in.Normal);
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    //cacular specular lighting
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);    
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(norm, halfwayDir), 0.0), 64.0);
    vec3 specular = spec * lightColor; 

    // calculate shadow
    float shadow = shadows ? ShadowCalculation(fs_in.FragPos) : 0.0;                      
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;    
    
    FragColor = vec4(lighting, 1.0);
}   