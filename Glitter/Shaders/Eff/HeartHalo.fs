#version 330 core
out vec4 FragColor;

//create a uniform for time
uniform float iTime;
//create a uniform for resolution
uniform vec2 iResolution;

//create a uniform for the color
uniform vec3 iHeartColor;
//create a uniform for the heartEdgeColor
uniform vec3 iHeartBgColor;

//create a float for the glow thickness
uniform float iGlowThickness;

//create a float for the glow offset
uniform float iGlowOffset;




//create a define for PI
#define PI 3.141592654


//create a func for df heart
float heart(vec2 p) {
    // shape
    float a = atan(p.x,p.y)/PI;
    float h = abs(a);
    float d = (13.0*h - 22.0*h*h + 10.0*h*h*h)/(6.0-5.0*h);
    return d;
}

//create sd circle
float sdCircle(vec2 p, float r){
    return length(p) - r;
}

//create a hash func
vec2 hash(vec2 p){
    p = vec2(dot(p, vec2(127.1,311.7)),dot(p,vec2(269.5,183.3)));
    return -1.0+2.0*fract(sin(p)*43758.5453123);
}


//create a func for the noise
//simplex
float noise(vec2 p){
    const float K1 = 0.366025404;
    const float K2 = 0.211324865;
    vec2 i = floor(p + (p.x + p.y) * K1);
    vec2 a = p - i + (i.x + i.y) * K2;
    vec2 o = step(a.yx, a.xy);
    vec2 b = a - o + K2;
    vec2 c = a - 1.0 + 2.0 * K2;
    vec3 h = max(0.5 - vec3(dot(a, a), dot(b, b), dot(c, c)), 0.0);
    vec3 n = h*h*h*h*vec3 (dot (a, hash (i + .0)),dot (b, hash (i + o)), dot (c, hash (i + 1.)));
    return dot(n, vec3(70.0));
}


//create a func for fbm
float fbm(vec2 p, float tm){
    //create a offset for the noise
   vec2 offset = vec2(cos(tm),sin(tm*sqrt(0.5)));

    //octaves
    float aggr = 0.0;
    //octave 1
    aggr += noise(p);
    //octave 2
    aggr += 0.5 * noise(p+offset);
    //octave 3
    aggr += 0.25 * noise(p+offset.yx);
    //octave 4
    aggr += 0.125 * noise(p-offset);
    //octave 5
    aggr += 0.0625 * noise(p-offset.yx);

    aggr /= 1.0 + 0.5 + 0.25 + 0.125 + 0.0625;

    float f = (aggr * 0.5) + 0.5;

    return f;
    
}


//create a func for the lightning
vec3 lightning(vec2 p, float d){
    //create orgCol
    vec3 orgCol = vec3(0.0, 2.0, 4.0);

    //cal the time
    float time = iTime+123.5;

    //create a col for the lightning
    vec3 col = vec3(0.0);

    //add loop for the lightning
    for(int i = 0; i < 3; i++){
        //cal the col by time
        vec3 gCol0 = 1.0+cos(0.5*orgCol+time+3.0*p.x);
        //add noise
        //create a float time for the noise
        float timeN = time/200;

        timeN= 75*timeN +i;
        //create a float for the noise
        float fbm = fbm(p+i, timeN);
        float div1 = abs(d-fbm);
        

        float d1 = iGlowThickness/div1;
        col+= gCol0*d1;
    }

    //cal the col by time
    //vec3 gCol0 = 1.0+cos(0.5*orgCol+time+3.0*p.x);
    ////add noise
    ////create a float time for the noise
    //float timeN = time/200;

    //timeN*= 75;
    ////create a float for the noise
    //float fbm = fbm(p, timeN);
    //float div1 = abs(d-fbm);

    ////creat f float val for the div1
    ////float div1 = abs(d);

    //float d1 = iGlowThickness/div1;
    //col+= gCol0*d1;

    return col;
}

//create aces_approx func
vec3 aces_approx(vec3 v) {
    v = max(v, 0.0);
    v *= 0.6;
    float a = 2.51;
    float b = 0.03;
    float c = 2.43;
    float d = 0.59;
    float e = 0.14;

    v = clamp((v*(a*v+b))/(v*(c*v+d)+e), 0.0, 1.0);    
    return v;
}


//create a func to set the eff
vec3 effect(vec2 p){
    //cal the bg color by gradually changing the color
    vec3 bgColor = vec3(iHeartBgColor.r, iHeartBgColor.g, iHeartBgColor.b-0.07*p.y) * (1.0 - 0.25*length(p));

    // add animation
    //create a float for the time
    float tt = mod(iTime, 2.0)/1.5;
    float ss = pow(tt, 0.5)*0.5 +0.5;
    ss = sin(tt*PI*6+p.y*0.5)*exp(-tt*4.0)*ss*0.5+1;
    p*= vec2(0.5, -0.5)*ss+vec2(0.5, 1.5);


    //create a color for the result
    vec3 col = vec3(0.0);
    col = bgColor;
    
    //create a float for the heart
    //offset for the heart's y
    p.y -= 0.25;

    float r = length(p);
    float s = 0.75+0.75*p.x;
    //create a col for the heartColor
    vec3 hCol = vec3(iHeartColor.r, iHeartColor.g*r, iHeartColor.b)*s;

    
    float d = heart(p);

    //add glow
    p.y += iGlowOffset;
    float dd = sdCircle(p, 0.8);
    vec3 gCol = lightning(p, dd);
    col += gCol;


    //mix the color
    col = mix(col, hCol, smoothstep(-0.01, 0.01, d-r));

    //apply the color mapping
    col = aces_approx(col);
    col = sqrt(col);

    return col;

}



//create mainImage function
void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    //normalize the coordinates
    vec2 uv = fragCoord.xy / iResolution.xy;
    //center the coordinates
    uv = -1+2*uv;
    uv.x *= iResolution.x / iResolution.y;
    //create a color for the fragment
    vec3 color = effect(uv);
    //set the color of the fragment
    fragColor = vec4(color, 1.0);
    
}



void main(){
     
    mainImage(FragColor, gl_FragCoord.xy);
}

