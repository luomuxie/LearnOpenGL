#version 330 core
out vec4 FragColor;
//create a uniform samper2D
uniform sampler2D ourTexture;
//create a uniform for time
uniform float iTime;
//create a uniform for resolution
uniform vec2 iResolution;
//create a uniform for mouse
uniform vec2 iMouse;


#define MAX_RADIUS 2
#define HASHSCALE1 .1031
#define HASHSCALE3 vec3(.1031, .1030, .0973)

float hash12(vec2 p)
{
    vec3 p3  = fract(vec3(p.xyx) * HASHSCALE1);
    p3 += dot(p3, p3.yzx + 19.19);
    return fract((p3.x + p3.y) * p3.z);
}

vec2 hash22(vec2 p)
{
    vec3 p3 = fract(vec3(p.xyx) * HASHSCALE3);
    p3 += dot(p3, p3.yzx+19.19);
    return fract((p3.xx+p3.yz)*p3.zy);
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{    
    //calculate the resolution by the mouse position
    float resolution = 10. * exp2(-3.*iMouse.x/iResolution.x);
    //normalize the fragCoord and multiply the resolution to extend the uv
    vec2 uv = fragCoord.xy / iResolution.y * resolution;
    //Grid Cell Division
    vec2 p0 = floor(uv);


    //create a vec2 to store the circles's effect
    vec2 circles = vec2(0.);
    for (int j = -MAX_RADIUS; j <= MAX_RADIUS; ++j)
    {
        for (int i = -MAX_RADIUS; i <= MAX_RADIUS; ++i)
        {
            //create a vec2 to store the curent p
            vec2 pi = p0 + vec2(i, j);            
            //create a random vec2 for the position
            vec2 p = pi + hash22(pi);

            //时间因子和距离计算
            //动态计算波纹的扩散。
            //为每个像素点相对于波纹源的位置和波纹的生命周期创建了一个动态映射，
            //从而产生了波纹随时间在水面上扩散的效果。
            float t = fract(0.3*iTime + hash12(pi));
            vec2 v = p - uv;
            float d = length(v) - (float(MAX_RADIUS) + 1)*t;
            //create a float to store the 0.001
            //p1` 和 p2 计算了在 `d1` 和 `d2` 这两个距离处的波纹强度
            float h = 1e-3;
            float d1 = d - h;
            float d2 = d + h;
            float p1 = sin(31.*d1) * smoothstep(-0.6, -0.3, d1) * smoothstep(0., -0.3, d1);
            float p2 = sin(31.*d2) * smoothstep(-0.6, -0.3, d2) * smoothstep(0., -0.3, d2);
            //通过计算波纹强度梯度累积波纹影响
            // create a float to store intensity gradient
            float gradient = (p2 - p1) / (2 * h);

            // Add to 'circles' the normalized ripple contribution with time decay.
            circles += 0.5 * normalize(v) * gradient * (1 - t) * (1 - t);

        }
    }


    //normalize the circles
    circles /= float((MAX_RADIUS*2+1)*(MAX_RADIUS*2+1));
    //calculate the intensity of the circle's light
    float intensity = mix(0.01, 0.15, smoothstep(0.1, 0.6, abs(fract(0.05*iTime + 0.5)*2.-1.)));
    //calculate the normal of the circle by  x^2 + y^2 + z^2 = 1
    vec3 n = vec3(circles, sqrt(1. - dot(circles, circles)));
    //create a light position
    vec3 lightPos = vec3(1., 0.7, 0.5);
    //calculate the specular light
    float specular = 5 * pow(clamp(dot(n, normalize(lightPos)), 0., 1.), 6.);
    //calculate the bend uv: first is normalize uv then offset by the intensity and the normal
    vec2 bendUv = uv/resolution - intensity*n.xy;
    //calculate the color by the texture and the specular
    vec3 color = texture(ourTexture, bendUv).rgb +specular;
    
    fragColor = vec4(color, 1.0);
}

void main() {
    // 这里放入之前的水滴扩散效果代码
    mainImage(FragColor, gl_FragCoord.xy);
}


