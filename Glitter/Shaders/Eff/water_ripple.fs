#version 330 core
out vec4 FragColor;

//create a samper2D
uniform sampler2D ourTexture;
//create a uniform for time
uniform float iTime;
//create a uniform for resolution
uniform vec2 iResolution;

//create a speed
float speed = 0.3;
#define MAX_RADIUS 2


//create a hash12 func
float hash12(vec2 p)
{
    vec3 p3  = fract(vec3(p.xyx) * .1031);
    p3 += dot(p3, p3.yzx + 19.19);
    return fract((p3.x + p3.y) * p3.z);
}

//create a hash22 func
vec2 hash22(vec2 p)
{
    vec3 p3 = fract(vec3(p.xyx) * vec3(.1031, .1030, .0973));
    p3 += dot(p3, p3.yzx+19.19);
    return fract((p3.xx+p3.yz)*p3.zy);
}


//create a mainImage func 
void mainImage( out vec4 fragColor, in vec2 fragCoord )
{    
    //calculate the resolution for the grid cell division
    float resolution = 10;
    //normalize the fragCoord and multiply the resolution to extend the uv
    vec2 uv = fragCoord.xy / iResolution.y * resolution;
    //Grid Cell Division
    vec2 p0 = floor(uv);
    //create a finalCol to store the color
    vec3 finalCol = vec3(0.0);

    //create a v2 to store the circles's effect
    vec2 circles = vec2(0.);

    for(int j = -MAX_RADIUS;j<= MAX_RADIUS;++j)
    {
        for(int i = -MAX_RADIUS;i<= MAX_RADIUS;++i)
        {
            //move the p0 to the center of the cell
            vec2 pi = p0 + vec2(i, j);

            vec2 p = pi+hash22(pi);

            //create a time factor and distance calculation
            float t = fract(iTime * speed+hash12(pi));
            vec2 v = p - uv;

            float d = length(v) - (float(MAX_RADIUS)+1)*t;
            
            //d = sin(d*31)*smoothstep(-0.6, -0.3, d) * smoothstep(0., -0.3, d);
            //d *= (1 - t) * (1 - t);

            float h = 1e-3;
            float d1 = d - h;
            float d2 = d + h;
            float p1 = sin(31.*d1)*smoothstep(-0.6, -0.3, d1) * smoothstep(0., -0.3, d1);
            float p2 = sin(31.*d2)*smoothstep(-0.6, -0.3, d2) * smoothstep(0., -0.3, d2);
            float gradient = (p2 - p1) / (2 * h);
            d = gradient * (1 - t) * (1 - t);


            vec3 col = vec3(1.0);
            finalCol += col*d;

            circles += 0.5 * normalize(v) * d;

        }

    }

    //finalCol /= float((MAX_RADIUS*2+1)*(MAX_RADIUS*2+1));

    circles /= float((MAX_RADIUS*2+1)*(MAX_RADIUS*2+1));
    //cal the normal by the circles : x^2 + y^2 + z^2 = 1;
    vec3 normal = vec3(circles, sqrt(1.0 - dot(circles, circles)));
    //cal the instensity of the benduv
    float tempVal = smoothstep(0.1, 0.6, abs(fract(0.05*iTime+0.5)*2-1));
    float intensity = mix(0.01,0.15,tempVal);
    //cal the bend uv
    vec2 bendUV = uv/resolution - intensity*normal.xy;
    finalCol = texture(ourTexture, bendUV).rgb;

    //cal the specular
    //create half vector
    vec3 halfVector = vec3(1.0, 0.7, 0.5);
    float specular = 5 * pow(clamp(dot(normal, normalize(halfVector)), 0., 1.), 6.);


    fragColor = vec4(finalCol, 1.0)+specular;
   
}


//main func
void main()
{
    //set the color
    //FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    mainImage(FragColor, gl_FragCoord.xy);


}


