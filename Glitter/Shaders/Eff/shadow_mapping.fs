#version 330 core
out vec4 FragColor;

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



float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}


vec2 uniformDiskSample(float u, float v) {
    float r = sqrt(u);
    float theta = 2.0 * 3.14159265359 * v;

    return vec2(r * cos(theta), r * sin(theta));
}

const int poissonDiskSamples = 71;
const  vec2 poissonDisk[poissonDiskSamples] = vec2[](
        vec2(-0.026062, 0.033525),
        vec2(0.146411, -0.072178),
        vec2(-0.206828, 0.123158),
        vec2(-0.030381, -0.171644),
        vec2(0.314729, -0.192280),
        vec2(0.254208, 0.111740),
        vec2(0.435894, -0.019511),
        vec2(0.511214, -0.282421),
        vec2(-0.099841, 0.310326),
        vec2(-0.403816, 0.284965),
        vec2(-0.401442, 0.064316),
        vec2(-0.289044, -0.109352),
        vec2(-0.598621, 0.147027),
        vec2(-0.205764, -0.337033),
        vec2(0.031348, 0.486174),
        vec2(-0.069751, -0.506044),
        vec2(-0.282734, -0.531261),
        vec2(-0.466186, -0.266385),
        vec2(-0.633478, -0.384917),
        vec2(-0.631896, -0.124253),
        vec2(-0.109729, -0.723862),
        vec2(-0.417079, -0.726224),
        vec2(-0.503180, -0.545285),
        vec2(0.153009, 0.663038),
        vec2(0.218501, 0.399661),
        vec2(-0.140664, 0.631555),
        vec2(-0.798268, -0.259232),
        vec2(-0.777302, -0.552237),
        vec2(-0.979524, -0.061612),
        vec2(-0.971645, -0.404976),
        vec2(0.442545, 0.194019),
        vec2(-0.877375, 0.134962),
        vec2(-0.620794, -0.715166),
        vec2(-0.968601, -0.620978),
        vec2(0.393572, 0.543278),
        vec2(-0.743302, 0.324368),
        vec2(0.322801, 0.828496),
        vec2(-0.031200, 0.834503),
        vec2(0.074787, -0.839529),
        vec2(-0.259665, -0.896391),
        vec2(0.634114, 0.046211),
        vec2(0.589242, 0.351141),
        vec2(0.765226, -0.122908),
        vec2(-0.663601, 0.514847),
        vec2(0.268293, -0.779580),
        vec2(-0.206685, 0.939976),
        vec2(-0.400520, 0.777466),
        vec2(-0.333699, 0.514647),
        vec2(-0.808582, 0.705673),
        vec2(0.965107, 0.027175),
        vec2(0.961839, -0.265666),
        vec2(0.758706, 0.524811),
        vec2(0.783202, 0.284558),
        vec2(0.577568, 0.632352),
        vec2(0.952373, 0.699874),
        vec2(0.949094, 0.410767),
        vec2(0.128173, -0.326884),
        vec2(-0.616279, 0.870106),
        vec2(-0.981725, 0.568443),
        vec2(-0.873435, -0.814975),
        vec2(0.438009, -0.950059),
        vec2(0.757794, 0.806406),
        vec2(0.782614, -0.414103),
        vec2(0.637071, -0.867825),
        vec2(0.320465, -0.458533),
        vec2(0.157505, -0.581345),
        vec2(0.558779, 0.994296),
        vec2(0.912859, 0.945485),
        vec2(0.774313, -0.676565),
        vec2(0.957122, -0.828102),
        vec2(0.810311, -0.986664)
    );


//create a func to calculate the shadow
float CalcShadow(vec4 fragPosLightSpace)
{
    //perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    //transform to [0, 1] range
    projCoords = projCoords * 0.5 + 0.5;
    //get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(depthMap, projCoords.xy).r; 
    //get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;

    float shadow = 0.0;
    if(projCoords.z > 1.0){
        return shadow;
    }


    vec3 normal = normalize(fs_in.Normal);
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);

    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    

    //3X3 kernel PCF
    //vec2 texelSize = 1.0 / textureSize(depthMap, 0);
    
    //for(int x = -1; x <= 1; ++x)
    //{
    //    for(int y = -1; y <= 1; ++y)
    //    {
    //        float pcfDepth = texture(depthMap, projCoords.xy + vec2(x, y) * texelSize*4).r; 
    //        shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;        
    //    }
    //}

    //shadow /= 9.0;

    //uniformDiskSample PCF
    //int samples = 16; // sample count, can be adjusted
    //float radius = 5.0; // sample radius, can be adjusted 
    //for(int i = 0; i < samples; ++i) {
    //    vec2 sampleUv = uniformDiskSample(rand(projCoords.xy), rand(projCoords.xy + 1.0));
    //    // map the sample point from the unit circle to the sample radius
    //    sampleUv = sampleUv * radius / textureSize(depthMap, 0).x + projCoords.xy;
    //    float sampleDepth = texture(depthMap, sampleUv).r;
    //    if(currentDepth - bias > sampleDepth)
    //        shadow += 1.0;
    //}
    //shadow = shadow / float(samples);

    //poisson disk PCF

    vec2 texelSize = 1.0 / textureSize(depthMap, 0);
    for(int i = 0; i < poissonDiskSamples; ++i) {
        vec2 sampleUv = projCoords.xy + poissonDisk[i] * texelSize*5; 
        float sampleDepth = texture(depthMap, sampleUv).r; 
        shadow += currentDepth - bias > sampleDepth ? 1.0 : 0.0;
    }
    shadow = shadow / float(poissonDiskSamples);

    //pcss PCF


      

    return shadow;
}   



void main()
{             
    //get the diffuse color
    vec3 color = texture(diffuseTexture, fs_in.TexCoords).rgb;
    //create a light color
    vec3 lightColor = vec3(1.0);

    vec3 normal = normalize(fs_in.Normal);

    //ambient
    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * lightColor;

    //diffuse    
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

    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;

    FragColor = vec4(lighting, 1.0);
    //FragColor = vec4(shadow, 0.0, 0.0, 1.0);
    
}