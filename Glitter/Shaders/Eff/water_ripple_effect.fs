#version 330 core
out vec4 FragColor;

//create a uniform variable to store the time
uniform float iTime;
//create a uniform for resolution 
uniform vec2 iResolution;

//create a uniform for mouse position
uniform vec2 iMouse;

//create a uniform for the texture
uniform sampler2D ourTexture;

#define MAX_RADIUS 2;

#define HASHSCALE3 vec3(0.1031, 0.1030, 0.0973)
#define HASHSCALE1 .1031


//create a func to create a random vec2 and the name is hash22
vec2 hash22(vec2 p)
{
    vec3 p3 = fract(vec3(p.xyx) * HASHSCALE3);
    p3 += dot(p3, p3.yzx + 19.19);
    return fract((p3.xx + p3.yz) * p3.zy);

}

//create a func to create a random float and the name is hash12
float hash12(vec2 p){

    vec3 p3 = fract(vec3(p.xyx) * HASHSCALE1);
    p3 += dot(p3, p3.yzx + 19.19);
    return fract((p3.x + p3.y) * p3.z);
}


void mainImage(out vec4 fragColor, in vec2 fragCoord)
{
    //calculate the resoultion by the mouse pos
    float resolution =  exp(-3*iResolution.x / iMouse.x)*10;

    //normalize the fragCoord and multiply by the resolution to extend the uv
    vec2 uv = fragCoord.xy / iResolution.xy * resolution;

    //grid the cell division
    vec2 p0 = floor(uv);

    //create a vec2 to store the circles's effect
    vec2 circle = vec2(0.0);
    
    //create two for loops to calculate the circle's effect
    for(int i = -MAX_RADIUS; i <= MAX_RADIUS; i++)
    {
        for(int j = -MAX_RADIUS; j <= MAX_RADIUS; j++)
        {
            
            //create a vec2 to store the current cell
            vec2 pi = p0 + vec2(i, j);

            //create a random vec2 for the position
            vec2 p = pi+hash22(pi);

            //create a time to control the chane of ripple over time
            float t = fract(iTime*0.3+ hash12(pi));
            
            vec2 v = p - uv;
            float d = length(v) - (float(MAX_RADIUS)+1.0)*t;


            //cal the intensity gradient
            //create a float to store the 0.001 by name h
            float h = 1e-3;
            float d1 = d-h;
            float d2 = d+h;

            //caculate the p1 and p2
            float p1 = smoothstep(-0.6, -0.3, d1)*smoothstep(0.0,-0.3, d1)*sin(31*d1);
            float p2 = smoothstep(-0.6, -0.3, d2)*smoothstep(0.0,-0.3, d2)*sin(31*d1);

            //caculate the gradient
            float g = (p2-p1)/(2.0*h);

            //add to the circle the normalized ripple contribution with the decay
            circle += normalize(v) *g *(1-t)*(1-t) *0.5;

            

        }
    }

    //normalize the circle by the max radius
    circle /= float((MAX_RADIUS+1)*(MAX_RADIUS+1));

    


    


}


void main()
{
    FragColor = vec4(0.0, 0.0, 1.0, 1.0);
}
