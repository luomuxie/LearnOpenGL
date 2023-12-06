#version 330 core
out vec4 FragColor;

uniform vec2 iResolution;
uniform float iTime;

//create mainImage function
void mainImage( out vec4 fragColor, in vec2 fragCoord);
//create rot function
mat2 rot(float a);
//create star5 function
float star5(vec2 p, float r, float rf);
//create palette function
vec3 palette(float t);
//create sdHeart function
float sdHeart( in vec2 p, float size );
//create dot2 func
float dot2(vec2 v);



void main() {
    mainImage(FragColor, gl_FragCoord.xy);
}

// 定义旋转矩阵函数
mat2 rot(float a) {
    float s = sin(a);
    float c = cos(a);
    return mat2(c, -s, s, c);
}

// License: MIT, author: Inigo Quilez, found: https://iquilezles.org/www/articles/distfunctions2d/distfunctions2d.htm
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


// 定义调色板函数

vec3 palette(float a) {
  return 0.5+0.5*sin(vec3(0,1,2) + a);
}


void mainImage( out vec4 fragColor, in vec2 fragCoord ) {
    vec2 q = fragCoord/iResolution.xy;
    vec2 p = -1. + 2. * q;
    p.x *= iResolution.x/iResolution.y; 

    vec3 col = vec3(0.0, 0. ,0.0);  
    for (int i=0; i<5;++i) { 
        vec2 p0 = p;
        float itime = iTime+1.2*float(i);
        p0.x += sin(itime);


        float b = itime;
        b = fract(b);
        b -= 0.5;
        b *= b;
        b *= 2.0;
        p0.y += b;
  
        p0 *= rot(8.0*cos(itime));  

        float d = star5(p0, 0.5, 0.5);
    
        float od = abs(d)-0.015;
    
        if (d < 0.0) {
            col = palette(itime-8.0*d);
        }
    
        if (od < 0.0) {
            col = vec3(q.y);
        }       
    }
    
      //col.x += sin(40.0*d);
      col = sqrt(col);
      fragColor = vec4(col, 1.0);
 
}
