#version 330 core
out vec4 FragColor;


//get the input from the vertex shader with the in_vs variable
in VS_OUT
{
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;

} fs_in;


//get the depth value from the texture
uniform sampler2D shadowMap;
//get the diffuse texture
uniform sampler2D diffuseTexture;
//get the light pos
uniform vec3 lightPos;
//get the viewPos
uniform vec3 viewPos;


//关于在阴影计算中进行的透视除法，这里的意图是将片段的坐标从齐次坐标转换为三维坐标，这是为了进一步处理这些坐标。让我们一步步分析这个过程🔍🌟。

//1. **齐次坐标转换**:
//   - 在3D图形渲染过程中，顶点坐标首先以齐次坐标（四维）的形式存在，这种形式方便进行各种矩阵变换（如模型变换、视图变换、投影变换）。
//   - 当一个顶点通过投影变换后，它被映射到一个新的空间，称为裁剪空间（Clip Space），在这个空间中，坐标仍然是齐次坐标形式。

//2. **透视除法的目的**:
//   - 透视除法的目的是将齐次坐标转换为归一化设备坐标（NDC）。这是通过将`x, y, z`坐标除以`w`分量来完成的。
//   - 在阴影计算中，执行这一步是为了将坐标从裁剪空间转换到NDC空间。在NDC空间中，所有可见的顶点坐标都位于`[-1, 1]`的范围内。

//3. **阴影计算中的透视除法**:
//   - 在阴影映射的上下文中，我们通常关心的是片段在光源视角下的位置。这个位置需要被转换到NDC空间，以便与深度贴图（shadow map）进行比较。
//   - 所以，透视除法在这里用于将片段的位置从光源的视角（齐次坐标）转换到一个可以与深度贴图进行比较的形式（NDC空间）。

//4. **进一步处理**:
//   - 一旦坐标被转换到NDC空间，接下来的步骤是将这些坐标映射到深度贴图的坐标系统中。这通常涉及将`[-1, 1]`范围的NDC坐标映射到`[0, 1]`范围，因为深度贴图是在这个范围内定义的。

//在阴影映射的上下文中，透视除法是将片段的坐标从光源视角下的裁剪空间转换到NDC空间，这是与深度贴图进行比较的必要步骤。🦌🌅🖥️


//create a func to calculate the shadow
float CalcShadow(vec4 fragPosLightSpace)
{
    //turn to NDC
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    //transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    //get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    //get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    //check whether current frag pos is in shadow
    float shadow = currentDepth > closestDepth ? 1.0 : 0.0;
    return shadow;
}


void main()
{    
    //get the diffuseTexture color from the texture
    vec3 color = texture(diffuseTexture, fs_in.TexCoords).rgb;
    //create a light color
    vec3 lightColor = vec3(1.0);
    //normalize the normal
    vec3 normal = normalize(fs_in.Normal);

    //ambient
    //calculate ambient lighting
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    //diffuse 
    //calculate diffuse lighting    
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    //specular
    //calculate specular lighting
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos-fs_in.FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  

    //calculate shadow
    float shadow = CalcShadow(fs_in.FragPosLightSpace);       
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;    

    FragColor = vec4(lighting, 1.0);    
        
}   