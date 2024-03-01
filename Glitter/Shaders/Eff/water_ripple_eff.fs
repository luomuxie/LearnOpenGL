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
//create a speed
float speed = 0.3;

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
<<<<<<< HEAD
    //float resolution = 10. * exp2(-3.*iMouse.x/iResolution.x);
    float resolution = 1.0*1;
=======
    float resolution = 10;//10. * exp2(-3.*iMouse.x/iResolution.x);
>>>>>>> 0a99e92733437e7b01c976ef01d02abc833db83a
    //normalize the fragCoord and multiply the resolution to extend the uv
    vec2 uv = fragCoord.xy / iResolution.y * resolution;
    //Grid Cell Division
    vec2 p0 = floor(uv);
<<<<<<< HEAD

    //create a vec2 to store the circles's effect
    vec2 circles = vec2(0.);
    //for (int j = -MAX_RADIUS; j <= MAX_RADIUS; ++j)
    //{
    //    for (int i = -MAX_RADIUS; i <= MAX_RADIUS; ++i)
    //    {
    //        //create a vec2 to store the curent p
    //        vec2 pi = p0 + vec2(i, j);            
    //        //create a random vec2 for the position
    //        vec2 p = pi + hash22(pi);

    //        //时间因子和距离计算
    //        //动态计算波纹的扩散。
    //        //为每个像素点相对于波纹源的位置和波纹的生命周期创建了一个动态映射，
    //        //从而产生了波纹随时间在水面上扩散的效果。
    //        float t = fract(0.3*iTime + hash12(pi));
    //        //float t = fract(iTime);
    //        vec2 v = p - uv;
    //        float d = length(v) - (float(MAX_RADIUS) + 1)*t;
    //        //create a float to store the 0.001
    //        //p1` 和 p2 计算了在 `d1` 和 `d2` 这两个距离处的波纹强度
    //        float h = 1e-3;
    //        float d1 = d - h;
    //        float d2 = d + h;
    //        float p1 = sin(10.*d1) * smoothstep(-0.6, -0.3, d1) * smoothstep(0., -0.3, d1);
    //        float p2 = sin(10.*d2) * smoothstep(-0.6, -0.3, d2) * smoothstep(0., -0.3, d2);
    //        //通过计算波纹强度梯度累积波纹影响
    //        // create a float to store intensity gradient
    //        float gradient = (p2 - p1) / (2 * h);

    //        // Add to 'circles' the normalized ripple contribution with time decay.
    //        circles += 0.5 * normalize(v) * gradient * (1 - t) * (1 - t);
    //    }
    //}

        //create a vec2 to store the curent p
    vec2 pi = p0; //+ vec2(i, j);            
    //create a random vec2 for the position
    vec2 p = pi ;//+ hash22(pi);

    //时间因子和距离计算
    //动态计算波纹的扩散。
    //为每个像素点相对于波纹源的位置和波纹的生命周期创建了一个动态映射，
    //从而产生了波纹随时间在水面上扩散的效果。
    float t = fract(0.3*iTime + hash12(pi));
    //float t = fract(iTime);
    vec2 v = p - uv;
    float d = length(v) - (float(MAX_RADIUS) + 1)*t;
    //create a float to store the 0.001
    //p1` 和 p2 计算了在 `d1` 和 `d2` 这两个距离处的波纹强度
    float h = 1e-3;
    float d1 = d - h;
    float d2 = d + h;
    float p1 = sin(10.*d1) * smoothstep(-0.6, -0.3, d1) * smoothstep(0., -0.3, d1);
    float p2 = sin(10.*d2) * smoothstep(-0.6, -0.3, d2) * smoothstep(0., -0.3, d2);
    //通过计算波纹强度梯度累积波纹影响
    // create a float to store intensity gradient
    float gradient = (p2 - p1) / (2 * h);

    // Add to 'circles' the normalized ripple contribution with time decay.
    circles += 0.5 * normalize(v) * gradient * (1 - t) * (1 - t);
=======
    //move the p0 to the center of the cell
    

    //create a vec2 to store the circles's effect
   
   vec2 circles = vec2(0.);
   vec3 finalCol = vec3(0.0);
    for (int j = -MAX_RADIUS; j <= MAX_RADIUS; ++j)
    {
        for (int i = -MAX_RADIUS; i <= MAX_RADIUS; ++i)
        {
            //move the p0 to the center of the cell
            //create a vec2 to store the curent p
            vec2 pi = p0+ vec2(i, j);            
            //create a random vec2 for the position
            vec2 p = pi+ hash22(pi);
            //时间因子和距离计算
            //动态计算波纹的扩散。
            //为每个像素点相对于波纹源的位置和波纹的生命周期创建了一个动态映射，
            //从而产生了波纹随时间在水面上扩散的效果。
            float t = fract(speed*iTime + hash12(pi));
            //float t = fract(speed*iTime);
            vec2 v = p - uv;
            float d = length(v)- (float(MAX_RADIUS) + 1)*t;
            //-------------------------------------
            //d = sin(d*31)*smoothstep(-0.6, -0.3, d) * smoothstep(0., -0.3, d);

            //个 (1. - t) 提供了一个线性的衰减效果，即波纹强度随时间线性减小。然而，线性衰减可能不足以模拟水波纹随时间的自然衰减方式。
            //通过使用 (1. - t) * (1. - t)，实际上是将衰减效果的曲线变得更加陡峭。这意味着波纹强度在初始时刻减少得较慢，但随着时间的推移，衰减速度加快。
            //d *= (1 - t) * (1 - t);
            //-----------------------------------------------------

            float h = 1e-3;
            float d1 = d - h;
            float d2 = d + h;
            float p1 = sin(31.*d1)*smoothstep(-0.6, -0.3, d1) * smoothstep(0., -0.3, d1);
            float p2 = sin(31.*d2)*smoothstep(-0.6, -0.3, d2) * smoothstep(0., -0.3, d2);
            float gradient = (p2 - p1) / (2 * h);
            d = gradient * (1 - t) * (1 - t);
            //-----------------------------------------------

            //create a col
            vec3 col = vec3(1.0);

            finalCol +=col*d ;
            circles += 0.5 * normalize(v) * d;
        }
    }
>>>>>>> 0a99e92733437e7b01c976ef01d02abc833db83a

    //finalCol /=   
    //vec3 color = finalCol;

    //normalize the circles
<<<<<<< HEAD
    //circles /= float((MAX_RADIUS*2+1)*(MAX_RADIUS*2+1));
    //calculate the intensity of the circle's light
    float intensity = mix(0.01, 0.15, smoothstep(0.1, 0.6, abs(fract(0.05*iTime + 0.5)*2.-1.)));
    //calculate the normal of the circle by  x^2 + y^2 + z^2 = 1
    vec3 n = vec3(circles, sqrt(1. - dot(circles, circles)));
    //create a light position
    vec3 lightPos = vec3(1., 0.7, 0.5);
    //calculate the specular light
    float specular = 5 * pow(clamp(dot(n, normalize(lightPos)), 0., 1.), 6.);
=======
    circles /= float((MAX_RADIUS*2+1)*(MAX_RADIUS*2+1));

    //calculate the normal of the circle by  x^2 + y^2 + z^2 = 1;计算法线-----------------------------
    vec3 n = vec3(circles, sqrt(1. - dot(circles, circles)));  

    //calculate the intensity of the bendUv;计算扭曲强度--------------------------------------
    float intensity = mix(0.01, 0.15, smoothstep(0.1, 0.6, abs(fract(0.05*iTime + 0.5)*2.-1.)));          
>>>>>>> 0a99e92733437e7b01c976ef01d02abc833db83a
    //calculate the bend uv: first is normalize uv then offset by the intensity and the normal
    vec2 bendUv = uv/resolution - intensity*n.xy;

    //create a half vector for the specular light//创建半向量,用于镜面反射
    vec3 h = vec3(1.0, 0.7, 0.5);
    //calculate the specular light
    float specular = 5 * pow(clamp(dot(n, normalize(h)), 0., 1.), 6.);


    //calculate the color by the texture and the specular
    vec3 color = texture(ourTexture, bendUv).rgb +specular;
    //vec3 color = texture(ourTexture, bendUv).rgb;
    
    
    fragColor = vec4(color, 1.0);
}

void main() {
    // 这里放入之前的水滴扩散效果代码
    mainImage(FragColor, gl_FragCoord.xy);
}


