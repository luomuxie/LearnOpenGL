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
uniform sampler2D depthMap;
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


float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}


vec2 uniformDiskSample(float u, float v) {
    float r = sqrt(u);
    float theta = 2.0 * 3.14159265359 * v;

    return vec2(r * cos(theta), r * sin(theta));
}

float getPenumbraSize(float lightSize, float lightDistance, float receiverDistance) {
    return (lightSize / lightDistance) * (receiverDistance - lightDistance);
}

float findBlocker(sampler2D shadowMap, vec2 uv, float zReceiver, vec2 disk[]) {
    float dBlocker = zReceiver * 0.01; // 初始阻挡物深度
    const float wLight = 0.006;        // 光源宽度
    const float c = 100.0;             // 搜索半径比例常数
    float wBlockerSearch = wLight * zReceiver * c; // 搜索半径

    float sum = 0.01;  // 避免除以零的初始值
    for(int i = 0; i < 16; ++i) {
        float depthInShadowmap = texture(shadowMap, uv + disk[i] * wBlockerSearch).r;
        if(depthInShadowmap < zReceiver) {
            dBlocker += depthInShadowmap;
            sum += 1.0;
        }
    }
    return sum > 0.01 ? dBlocker / sum : zReceiver;
}




//create a func to calculate the shadow
float CalcShadow(vec4 fragPosLightSpace)
{    
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;

    float shadow = 0.0;

    //transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
                
    //get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    if(projCoords.z > 1.0){
        return shadow;
    }
    float closestDepth = texture(depthMap, projCoords.xy).r; 
    vec3 normal = normalize(fs_in.Normal);
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);

    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    //shadow = currentDepth-bias > closestDepth  ? 1.0 : 0.0;

    int poissonDiskSamples = 16;
    vec2 poissonDisk[16] = vec2[](
        vec2(-0.94201624, -0.39906216),
        vec2(0.94558609, -0.76890725),
        vec2(-0.094184101, -0.92938870),
        vec2(0.34495938, 0.29387760),
        vec2(-0.91588581, 0.45771432),
        vec2(-0.81544232, -0.87912464),
        vec2(-0.38277543, 0.27676845),
        vec2(0.97484398, 0.75648379),
        vec2(0.44323325, -0.97511554),
        vec2(0.53742981, -0.47373420),
        vec2(-0.26496911, -0.41893023),
        vec2(0.79197514, 0.19090188),
        vec2(-0.24188840, 0.99706507),
        vec2(-0.81409955, 0.91437590),
        vec2(0.19984126, 0.78641367),
        vec2(0.14383161, -0.14100790)
    );


    //3x3 kernel PCF---------------------------------------------------------

    //vec2 texelSize = 1.0 / textureSize(depthMap, 0);
    //for(int x = -1; x <= 1; ++x)
    //{
    //    for(int y = -1; y <= 1; ++y)
    //    {
    //        float pcfDepth = texture(depthMap, projCoords.xy + vec2(x, y) * texelSize).r; 
    //        shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
    //    }    
    //}
    //shadow /= 9.0;

    //uniformDiskSample PCF---------------------------------------------------------
    //int samples = 16; // 采样数，可调整
    //float radius = 1.0; // 采样半径，可调整    
    //vec2 texelSize = 1.0 / textureSize(depthMap, 0);
    //for(int i = 0; i < samples; ++i) {
    //    vec2 sampleUv = uniformDiskSample(rand(projCoords.xy), rand(projCoords.xy + 1.0));
    //    sampleUv = sampleUv * radius / textureSize(depthMap, 0).x + projCoords.xy;
    //    float sampleDepth = texture(depthMap, sampleUv).r;
    //    if(currentDepth - bias > sampleDepth)
    //        shadow += 1.0;
    //}
    //return shadow / float(samples);
    

    //poisson disk PCF---------------------------------------------------------
    //vec2 texelSize = 1.0 / textureSize(depthMap, 0);
    //for(int i = 0; i < poissonDiskSamples; ++i) {
    //    vec2 sampleUv = projCoords.xy + poissonDisk[i] * texelSize;
    //    float sampleDepth = texture(depthMap, sampleUv).r; 
    //    shadow += currentDepth - bias > sampleDepth ? 1.0 : 0.0;
    //}
    //return shadow / float(poissonDiskSamples);

    //PCSS 1---------------------------------------------------------
    //float lightDistance = length(lightPos - fs_in.FragPos);
    //float receiverDistance = projCoords.z; // 片元深度
    //float penumbraSize = getPenumbraSize(6, lightDistance, receiverDistance); // 假设光源大小为0.05
    //vec2 texelSize = 1.0 / textureSize(depthMap, 0);
    //for(int i = 0; i < poissonDiskSamples; ++i) {
    //    vec2 sampleUv = projCoords.xy + poissonDisk[i] * texelSize * penumbraSize;
    //    float sampleDepth = texture(depthMap, sampleUv).r;
    //    if(receiverDistance - bias > sampleDepth) {
    //        shadow += 1.0;
    //    }
    //}
    //shadow /= float(poissonDiskSamples);

    //PCSS 2 add findBlocker ---------------------------------------------------------

    // 计算阻挡物平均深度
    float blockerDepth = findBlocker(depthMap, projCoords.xy, projCoords.z, poissonDisk);
    // 计算半影区域
    // 这里可以根据 blockerDepth 和 receiverDepth 的差值来调整半影大小
    float penumbraRatio = blockerDepth == projCoords.z ? 0.0 : (projCoords.z - blockerDepth) / blockerDepth;
    penumbraRatio = clamp(penumbraRatio, 0.0, 1.0);
    // PCF 计算    
    vec2 texelSize = 1.0 / textureSize(depthMap, 0);
    for(int i = 0; i < poissonDiskSamples; ++i) {
        vec2 sampleUv = projCoords.xy + poissonDisk[i] * texelSize * penumbraRatio;
        float sampleDepth = texture(depthMap, sampleUv).r;
        if(projCoords.z - bias > sampleDepth) {
            shadow += 1.0;
        }
    }
    shadow /= float(poissonDiskSamples);



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
    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * lightColor;

    //diffuse 
    //calculate diffuse lighting    
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    //specular
    vec3 viewDir = normalize(viewPos-fs_in.FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular = spec * lightColor;    

    //calculate shadow
    float shadow = CalcShadow(fs_in.FragPosLightSpace);
   //float shadow = PCF(fs_in.TexCoords, GetCurDepth(fs_in.FragPosLightSpace), depthMap, 1024.0);

   vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;    

   FragColor = vec4(lighting, 1.0);
   //FragColor = vec4(shadow, 0.0, 0.0, 1.0);
   
        
}   