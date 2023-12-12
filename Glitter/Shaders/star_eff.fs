#version 330 core
out vec4 FragColor;

//create mian to set the fragment color

//create a uniform for time
uniform float iTime;
//create a uniform for resolution
uniform vec2 iResolution;

//create a func name mainImage 
void mainImage(out vec4 fragColor, in vec2 fragCoord);

//create a fun name rot
mat2 rot(float a);

//create a fun to draw the star
float star5(vec2 p, float r, float rf);

//create a palette func
vec3 palette(float a);



void main()
{
    //FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    mainImage(FragColor, gl_FragCoord.xy);
}

//create a func name rot
mat2 rot(float a)
{
    float c = cos(a);
    float s = sin(a);
    return mat2(c, -s, s, c);
}

float star5(in vec2 p, in float r, in float rf) {

    const vec2 k1 = vec2(0.809016994375, -0.587785252292);
    const vec2 k2 = vec2(-k1.x,k1.y);
    p.x = abs(p.x);
    p -= 2.0*max(dot(k1,p),0.0)*k1;
    p -= 2.0*max(dot(k2,p),0.0)*k2;
    p.x = abs(p.x);
    p.y -= r;
    vec2 ba = rf*vec2(-k1.y,k1.x) - vec2(0,1);
    float h = clamp( dot(p,ba)/dot(ba,ba), 0.0, r );
    return length(p-ba*h) * sign(p.y*ba.x-p.x*ba.y);
}

vec3 palette(float a){
    
    return 0.5+0.5*sin(vec3(0,1,2)+a);
}


//achieve the mainImage func
void mainImage(out vec4 fragColor, in vec2 fragCoord)
{
    //normalize the fragCoord
    vec2 q = fragCoord / iResolution.xy;
    vec2 p = -1.0 + 2.0 * q;
    p.x *= iResolution.x / iResolution.y;
    
    //creat a col
    vec3 col = vec3(0.0);
    
    //create a loop to draw the star
    for(int i = 0; i < 5; i++)
    {
       //create a v2 to store the  p
       vec2 p0 = p;
       float itime= iTime+1.2*float(i);
       p0.x+= sin(itime);

       float b = itime;
       b = fract(b);
       b-=0.5;       
       b *= 2.0;
       b *= b;
       p0.y+=b;
       
       p0 *= rot(8.0*cos(itime));

       float d = star5(p0, 0.5, 0.5);

       float od = abs(d)-0.015;

       if(d<0.0){
            //set color
            col = palette(itime-8.0*d);
       }

       if(od<0.0){
           col = vec3(q.y);
       }

    }

    col = sqrt(col);
    
    //set the fragColor
    fragColor = vec4(col, 1.0);

}
