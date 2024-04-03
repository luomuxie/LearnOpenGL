

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

//create a floate val to offset the noise
uniform float iOffsetNoise;

//create a float for the glow thickness
uniform float iGlowThickness;

//create a int for the sample the noise offset
uniform int iNoiseScale;

//create the fbm's octave
uniform int iFbmOctaves;


#define TIME            iTime
#define RESOLUTION      iResolution
#define PI              3.141592654

//这个是作者变形得出，不是原始的心形函数
//在使用距离场（Signed Distance Field, SDF）函数时，返回值确实用来区分空间中点的位置相对于图形的边界。SDF为每个空间点提供一个值，该值表示点到最近图形表面的最短距离。对于SDF，约定如下：

//当返回值小于0时，这意味着点在图形内部。
//当返回值大于0时，这意味着点在图形外部。
//当返回值等于0时，这意味着点恰好在图形的边界上。
//这种方法允许在渲染时轻松实现复杂形状的高效率光照和阴影计算，以及其他图形效果，如边缘平滑。
//通过SDF，可以基于点到图形表面的距离，以数学方式定义和操作图形。

float heart(vec2 p) {
    // shape
    //float a = atan(p.x,p.y)/PI; 计算点p的角度（在x和y平面上），然后除以π（PI），将角度标准化到[-1, 1]的范围内。
    //atan函数的输出范围是[-π/2, π/2]（对于atan(y,x)，即atan2，范围是[-π, π]），
    //因此除以π后，a的范围是[-1, 1]。
    float a = atan(p.x,p.y)/PI;//a的范围是[-1, 1]
    //float r = length(p);
    float h = abs(a);//a的范围是[0, 1]
    float d = (13.0*h - 22.0*h*h + 10.0*h*h*h)/(6.0-5.0*h);
    return d;
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

//https://thebookofshaders.com/10/
//https://stackoverflow.com/questions/12964279/whats-the-origin-of-this-glsl-rand-one-liner
vec2 hash(vec2 p) {
    p = vec2(dot (p, vec2 (127.1, 311.7)), dot (p, vec2 (269.5, 183.3)));
    return -1. + 2.*fract (sin (p)*43758.5453123);
}

//https://gist.github.com/patriciogonzalezvivo/670c22f3966e662d2f83
//Simplex
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


//fbm: 生成分形布朗运动，用于创建类似闪电的效果。
//https://en.wikipedia.org/wiki/Fractional_Brownian_motion
//https://thebookofshaders.com/13/
float fbm(vec2 pos, float tm) {
    vec2 offset = vec2(cos(tm), sin(tm*sqrt(0.5)));
    //octave 一共5层
    float aggr = 0.0;
    aggr += noise(pos);//第一层
    aggr += noise(pos + offset) * 0.5;//第二层
    aggr += noise(pos + offset.yx) * 0.25;//第三层
    aggr += noise(pos - offset) * 0.125;//第四层
    aggr += noise(pos - offset.yx) * 0.0625;//第五层
     
    aggr /= 1.0 + 0.5 + 0.25 + 0.125 + 0.0625;
        
    float f = (aggr * 0.5) + 0.5;
          
    return f;
}

float fbm2 (in vec2 st) {
    float rtime = iTime*75.0;
    float tm = rtime/200.0;;

    vec2 offset = vec2(cos(tm), sin(tm*sqrt(0.5)));
    // Initial values
    float value = 0.0;
    float amplitude = .5;
    float frequency = 0.;
    //
    // Loop of octaves: 6
    for (int i = 0; i < iFbmOctaves; i++) {
        value += amplitude * noise(st+offset);
        st *= 2.;
        amplitude *= .5;
    }
    return value;
}


//lightning: 创建一个闪电效果，它可能会随着时间的变化而变化。
vec3 lightning(vec2 pos, float offset) {
   
    //creaet a color to store the color and name orgcol
    //第一步，初始化内部发光颜色
    vec3 orgCol = vec3(0.0, 2.0, 4.0);
    vec3 sub = 0.01*orgCol*length(pos);

    float time = iTime+123.4;
    float stime = time/200.0;

    vec3 col = vec3(0.0);
            
    //第二步：根据时间和位置重新计算发光颜色
    vec3 gcol0 = (1.0+cos(0.50*orgCol + time+3.0*pos.x));
    
    //offset is less than 0,is inside the glow
    //offset is greater than 0,is outside the glow
    //offset is equal to 0, is on the glow edge

    //第三步：画一个圆
    //float div1 = abs(offset);

    //第四步：给圆添加上noise,使其看起来像闪电,并且根据时间变化
    float rtime = stime*75.0;
    //float fbm= fbm(pos *iNoiseScale, rtime);
    float fbm= fbm2(pos *iNoiseScale);
    float div1 = abs(offset - fbm);    

    float d1 = iGlowThickness /div1;
    col += d1 * gcol0;

    return col;
}


float sdCircle( vec2 p, float r )
{
    return length(p) - r;
}


vec3 effect(vec2 p) {
    
    // background color
    //vec3 bgCol = vec3(1.0,0.8,0.7-0.07*p.y)*(1.0-0.25*length(p));
    //第一步
    vec3 bgCol = vec3(iHeartBgColor.r,iHeartBgColor.g,iHeartBgColor.b-0.07*p.y)*(1.0-0.25*length(p));

    // 最后一步:加上动画 animate---------------------------
    float tt = mod(iTime,1.5)/1.5;
    float ss = pow(tt,.2)*0.5 + 0.5;
    ss = 1.0 + ss*0.5*sin(tt*6.2831*3.0 + p.y*0.5)*exp(-tt*4.0);
    p *= vec2(0.5,1.5) + ss*vec2(0.5,-0.5);
    
    // 第二步:定义心的颜色
    //create a val to store the p    
    p.y -= 0.25;    
    float r = length(p);    
    
    float s = 0.75 + 0.75*p.x;    
    vec3 hcol = vec3(iHeartColor.r,iHeartColor.g*r,iHeartColor.b)*s;
    
   
   //add glow        
    vec3 col = bgCol;

    
    //第三步：画心心
    float d = heart(p);

    //第四步：add grow-------------------------------------------
    p.y += iOffsetNoise;
    float dd = sdCircle(p, 0.7);    
    vec3 lightColor = lightning(p, dd);
    col += lightColor;

    //第五步：add heart-------------------------------
    col = mix(col, hcol, smoothstep( -0.01, 0.01, d-r) );

    //最后一步：应用色调映射

    col = aces_approx(col); 
    col = sqrt(col); 

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
