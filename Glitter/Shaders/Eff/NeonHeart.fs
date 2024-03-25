
#version 330 core
out vec4 FragColor;



//create a uniform for time
uniform float iTime;
//create a uniform for resolution
uniform vec2 iResolution;
//create a uniform for the color
uniform vec3 iHeartColor;
//create a uniform for the heartEdgeColor
uniform vec3 iHeartEdgeColor;

//create a int val to sel noise type
uniform int iNoiseType;

#define TIME            iTime
#define RESOLUTION      iResolution
#define PI              3.141592654
#define TAU             (2.0*PI)



// License: WTFPL, author: sam hocevar, found: https://stackoverflow.com/a/17897228/418488
const vec4 hsv2rgb_K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
vec3 hsv2rgb(vec3 c) {
    vec3 p = abs(fract(c.xxx + hsv2rgb_K.xyz) * 6.0 - hsv2rgb_K.www);
    return c.z * mix(hsv2rgb_K.xxx, clamp(p - hsv2rgb_K.xxx, 0.0, 1.0), c.y);
}

// License: WTFPL, author: sam hocevar, found: https://stackoverflow.com/a/17897228/418488
//  Macro version of above to enable compile-time constants
#define HSV2RGB(c)  (c.z * mix(hsv2rgb_K.xxx, clamp(abs(fract(c.xxx + hsv2rgb_K.xyz) * 6.0 - hsv2rgb_K.www) - hsv2rgb_K.xxx, 0.0, 1.0), c.y))

const float hoff = 0.58;
//const vec3 dbcol = HSV2RGB(vec3(hoff+0.96, 0.8, 0.75));
const vec3 sbcol = HSV2RGB(vec3(hoff+0.95, 0.4, 1.0));
const vec3 gbcol = HSV2RGB(vec3(hoff+0.98, 0.9, 0.001));
//const vec3 fbcol = HSV2RGB(vec3(hoff+0.95, 0.7, 2.0));


// License: Unknown, author: Claude Brezinski, found: https://mathr.co.uk/blog/2017-09-06_approximating_hyperbolic_tangent.html
float tanh_approx(float x) {
    //  Found this somewhere on the interwebs
    //  return tanh(x);
    float x2 = x*x;
    return clamp(x*(27.0 + x2)/(27.0+9.0*x2), -1.0, 1.0);
}

// License: Unknown, author: Matt Taylor (https://github.com/64), found: https://64.github.io/tonemapping/
vec3 aces_approx(vec3 v) {
    v = max(v, 0.0);
    v *= 0.6f;
    float a = 2.51f;
    float b = 0.03f;
    float c = 2.43f;
    float d = 0.59f;
    float e = 0.14f;
    return clamp((v*(a*v+b))/(v*(c*v+d)+e), 0.0f, 1.0f);

}

// License: MIT, author: Inigo Quilez, found: https://www.iquilezles.org/www/articles/smin/smin.htm
float pmin(float a, float b, float k) {
    float h = clamp(0.5+0.5*(b-a)/k, 0.0, 1.0);
    return mix(b, a, h) - k*h*(1.0-h);
}

// License: CC0, author: Mårten Rånge, found: https://github.com/mrange/glsl-snippets
float pabs(float a, float k) {
    return -pmin(a, -a, k);
}

float dot2(vec2 p) {
    return dot(p, p);
}

// License: MIT, author: Inigo Quilez, found: https://iquilezles.org/www/articles/distfunctions2d/distfunctions2d.htm
float heart(vec2 p) {
    p.x = pabs(p.x, 0.05);

    if( p.y+p.x>1.0 )
        return sqrt(dot2(p-vec2(0.25,0.75))) - sqrt(2.0)/4.0;
    return sqrt(min(dot2(p-vec2(0.00,1.00)),
                    dot2(p-0.5*max(p.x+p.y,0.0)))) * sign(p.x-p.y);
}


//df: 包装heart函数，对位置进行缩放和偏移处理
float df(vec2 p) {
    vec2 hp = p;
    const float hz = 1.0;
    hp /= hz;
    hp.y -= -0.6;
    float d = heart(hp)*hz;
    return d;
}

//hf: 根据距离场生成高度信息。
float hf(vec2 p) {
    float d = df(p);
    float h = (-20.0*d);
    h = tanh_approx(h);
    h -= 3.0*length(p);
    h = pmin(h, 0.0, 1.);
    h *= 0.25;
    return h;
}

//calculate the normal
vec3 nf(vec2 p) {
    vec2 v;
    vec2 w;
    vec2 e = vec2(4.0/RESOLUTION.y, 0);
  
    vec3 n;
    n.x = hf(p + e.xy) - hf(p - e.xy);
    n.y = hf(p + e.yx) - hf(p - e.yx);
    n.z = 2.0*e.x;
  
    return normalize(n);
}

//hash和noise: 实现噪声函数。
vec2 hash(vec2 p) {
    p = vec2(dot (p, vec2 (127.1, 311.7)), dot (p, vec2 (269.5, 183.3)));
    return -1. + 2.*fract (sin (p)*43758.5453123);
}


float noise(vec2 p) {
    const float K1 = .366025404;
    const float K2 = .211324865;

    vec2 i = floor (p + (p.x + p.y)*K1);
    
    vec2 a = p - i + (i.x + i.y)*K2;
    vec2 o = step (a.yx, a.xy);    
    vec2 b = a - o + K2;
    vec2 c = a - 1. + 2.*K2;

    vec3 h = max (.5 - vec3 (dot (a, a), dot (b, b), dot (c, c) ), .0);

    vec3 n = h*h*h*h*vec3 (dot (a, hash (i + .0)),dot (b, hash (i + o)), dot (c, hash (i + 1.)));

    return dot (n, vec3 (70.));
}

//-------------------------------------------------------------
float ghash(vec2 p) { return fract(1e4 * sin(17.0 * p.x + p.y * 0.1) * (0.1 + abs(sin(p.y * 13.0 + p.x)))); }
float rand(vec2 n) { 
    return fract(sin(dot(n, vec2(12.9898, 4.1414))) * 43758.5453);
}

//Generic 1,2,3 Noise
float gnoise(vec2 x) {
    vec2 i = floor(x);
    vec2 f = fract(x);

    // Four corners in 2D of a tile
    float a = ghash(i);
    float b = ghash(i + vec2(1.0, 0.0));
    float c = ghash(i + vec2(0.0, 1.0));
    float d = ghash(i + vec2(1.0, 1.0));

    // Simple 2D lerp using smoothstep envelope between the values.
    // return vec3(mix(mix(a, b, smoothstep(0.0, 1.0, f.x)),
    //			mix(c, d, smoothstep(0.0, 1.0, f.x)),
    //			smoothstep(0.0, 1.0, f.y)));

    // Same code, with the clamps in smoothstep and common subexpressions
    // optimized away.
    vec2 u = f * f * (3.0 - 2.0 * f);
    return mix(a, b, u.x) + (c - a) * u.y * (1.0 - u.x) + (d - b) * u.x * u.y;
}

//https://en.wikipedia.org/wiki/Simplex_noise
vec3 permute(vec3 x) { return mod(((x*34.0)+1.0)*x, 289.0); }
float snoise(vec2 v){
    const vec4 C = vec4(0.211324865405187, 0.366025403784439,
            -0.577350269189626, 0.024390243902439);
    vec2 i  = floor(v + dot(v, C.yy) );
    vec2 x0 = v -   i + dot(i, C.xx);
    vec2 i1;
    i1 = (x0.x > x0.y) ? vec2(1.0, 0.0) : vec2(0.0, 1.0);
    vec4 x12 = x0.xyxy + C.xxzz;
    x12.xy -= i1;
    i = mod(i, 289.0);
    vec3 p = permute( permute( i.y + vec3(0.0, i1.y, 1.0 ))
    + i.x + vec3(0.0, i1.x, 1.0 ));
    vec3 m = max(0.5 - vec3(dot(x0,x0), dot(x12.xy,x12.xy),
    dot(x12.zw,x12.zw)), 0.0);
    m = m*m ;
    m = m*m ;
    vec3 x = 2.0 * fract(p * C.www) - 1.0;
    vec3 h = abs(x) - 0.5;
    vec3 ox = floor(x + 0.5);
    vec3 a0 = x - ox;
    m *= 1.79284291400159 - 0.85373472095314 * ( a0*a0 + h*h );
    vec3 g;
    g.x  = a0.x  * x0.x  + h.x  * x0.y;
    g.yz = a0.yz * x12.xz + h.yz * x12.yw;
  return 130.0 * dot(m, g);
}


//fbm: 生成分形布朗运动，用于创建类似闪电的效果。
//https://en.wikipedia.org/wiki/Fractional_Brownian_motion
float fbm(vec2 pos, float tm) {
    vec2 offset = vec2(cos(tm), sin(tm*sqrt(0.5)));
    float aggr = 0.0;

    //according to the noise type to select the noise
    if(iNoiseType == 0){

        aggr += noise(pos);
        aggr += noise(pos + offset) * 0.5;
        aggr += noise(pos + offset.yx) * 0.25;
        aggr += noise(pos - offset) * 0.125;
        aggr += noise(pos - offset.yx) * 0.0625;
    }else if(iNoiseType == 1) {
        
        aggr += snoise(pos);
        aggr += snoise(pos + offset) * 0.5;
        aggr += snoise(pos + offset.yx) * 0.25;
        aggr += snoise(pos - offset) * 0.125;
        aggr += snoise(pos - offset.yx) * 0.0625;    
    }else if(iNoiseType == 2) {
        
        aggr += gnoise(pos);
        aggr += gnoise(pos + offset) * 0.5;
        aggr += gnoise(pos + offset.yx) * 0.25;
        aggr += gnoise(pos - offset) * 0.125;
        aggr += gnoise(pos - offset.yx) * 0.0625;    
    }
     
     
    aggr /= 1.0 + 0.5 + 0.25 + 0.125 + 0.0625;
    
    float f = (aggr * 0.5) + 0.5;
  
    return f;
}

//divf: 功能不详，似乎是与闪电效果相关的某种衰减函数。
float divf(float offset, float f) {
    const float goff = 0.2;
    const float gfloor = 0.001;
    float r = abs(goff + offset - f);
    r = max(r, gfloor);
    return r;
}

//lightning: 创建一个闪电效果，它可能会随着时间的变化而变化。
// This way of computing "lightning" I found at shadertoy. Unfortunately I don't remember where.
vec3 lightning(vec2 pos, float offset) {

    //creaet a color to store the color and name orgcol
    vec3 orgCol = vec3(0.0, 1.0, 2.0);

    vec3 sub = 0.03*orgCol*length(pos);

    float time = TIME+123.4;
    float stime = time/200.0;

    vec3 col = vec3(0.0);
    vec2 f = 10.0*cos(vec2(sqrt(0.5), 1.0)*stime)+vec2(0.0, -11.0)*stime;
    const float glow = 0.0125;    

    //calculate the the  outside glow
    for (float i = 0.0; i < 3; ++i) {

        vec3 gcol0 = (1.0+cos(0.50*orgCol +time+3.0*pos.x-0.33*i));

        float rtime = stime*75.0 + (i);
        float div1 = divf(offset, fbm((pos + f) * 3.0, rtime));
        float d1 = offset * glow / div1;
        //col += (d1 * gcol0)-sub;
        col += (d1 * gcol0);


        //vec3 gcol1 = (1.0+cos(1.25*vec3(0.0, 1.0, 2.0) +2.*time+pos.y+0.25*i));
        //float btime = stime*85.0 + (i);               
        //float div2 = divf(offset, fbm((pos + f) * 2.0, btime));        
        //float d2 = offset * glow / div2;        
        //col += (d2 * gcol1)-sub;
    }
    
    return col;
}

vec3 palette(float a){
    
    return 0.5+0.5*sin(vec3(0,1,2)+a);
}

vec3 palette2( float t ) {
    vec3 a = vec3(0.1, 0, 0);
    vec3 b = vec3(0.5, 0, 0);
    vec3 c = vec3(1.0, 0, 0);
    //vec3 d = vec3(0.263,0.416,0.557);
    //vec3 d = vec3(0.0, 0.5, 1.0);
    vec3 d = vec3(0.67, 0, 0); // 创建类似彩虹的颜色过渡

    return a + b*cos( 6.28318*(c*t+d) );
}

float sdCircle( vec2 p, float r )
{
    return length(p) - r;
}


vec3 effect(vec2 p) {
    
    //根据距离场生成高度信息
    float h = hf(p);

    //calculate the normal
    vec3 n = nf(p);

    //ligth point
    const vec3 lp = vec3(-4.0, -5.0, 3.0);

    //ro代表的就是相机（或观察者）的位置，通常用于确定视图的原点，即你从哪里看向场景。在这个情境下
    //相机位于Z轴上，离XY平面10个单位远，朝向原点。这对于计算从相机到场景中任意点的视线（光线）非常重要
    const vec3 ro = vec3(0.0, 0.0, 10.0);

    //h是根据二维坐标p计算得出的，可以被看作是在心形的距离场上的高度或深度值，它为心形图形添加了立体效果。
    //因此，vec3(p, h)是在将二维屏幕空间的点转换成三维空间中的点，这允许着色器处理像光照这样的三维效果，
    //因为这需要知道每个点在三维空间中的位置。在这里，p3代表了屏幕上每个像素对应的三维世界中的点，这对于接下来计算光照和渲染效果至关重要。
    vec3 p3 = vec3(p, h); 

    //view direction
    vec3 rd = normalize(p3-ro);
    //light direction
    vec3 ld = normalize(lp-p3);

    //calculate reflection
    vec3 r = reflect(rd, n);

    //calculate the diffuse color
    float diff = max(dot(ld, n), 0.0);
    
    //包装heart函数，对位置进行缩放和偏移处理
    float d = df(p);


    //calculate the heartColor
    //float len = length(p);
    //float s = 0.75 + 0.75*p.x;
    //s *= 1.0-0.4*len;
    //s = 0.3 + 0.7*s;
    //s *= 0.5+0.5*pow( 1.0-clamp(len/d, 0.0, 1.0 ), 0.1 );
    //vec3 dbcol = vec3(1.0,0.4*len,0.3)*s;

    vec3 dbcol = iHeartColor;    
    vec3 dcol = dbcol*mix(vec3(0.15), vec3(1.0), diff);

    //calculate the specular color
    float spe = pow(max(dot(ld, r), 0.0), 3.0);
    vec3 scol = spe*sbcol;




    vec3 hcol = dcol;
    hcol += scol;

    // draw a circle light
    vec3 col = vec3(0.0);
    col += gbcol/max(0.01*(dot2(p)-0.15), 0.0001);


    //add glow    
    vec3 gcol = lightning(p, d);
    col += gcol;

    //the heart outside color------------------------------------

    //the 
    float aa = 4.0/RESOLUTION.y;

    col = mix(col, hcol, smoothstep(0.0, -aa, d));

    vec3 fbcol = iHeartEdgeColor;
    //the heart edge color
    col = mix(col, fbcol, smoothstep(0.0, -aa, abs(d+0.01)-0.01));    


    //deal with the gamma:色彩映射
    //col = aces_approx(col); 
    //col = sqrt(col); 

    return col;
}


void mainImage(out vec4 fragColor, in vec2 fragCoord) {

//映射到NDC空间：把屏幕坐标（fragCoord）映射到[-1, 1]范围内，这是OpenGL中使用的标准化设备坐标（NDC）空间。
//在NDC空间中，(0,0)通常是屏幕中心，(-1, -1)是左下角，(1, 1)是右上角。
//保持宽高比：通过调整x坐标（p.x *= RESOLUTION.x/RESOLUTION.y），它考虑到屏幕宽高比，
//确保在不同分辨率的屏幕上渲染时保持图形的比例，防止图形拉伸或压缩。
    vec2 q = fragCoord/RESOLUTION.xy;
    vec2 p = -1. + 2. * q;    
    p.x *= RESOLUTION.x/RESOLUTION.y;
    vec3 col = effect(p); 
    fragColor = vec4(col.xyz, 1.0);
}



void main()
{             
    //FragColor = vec4(1,0,0, 1.0); //
    mainImage(FragColor, gl_FragCoord.xy);
}
