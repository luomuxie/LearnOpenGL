#version 330 core
out vec4 FragColor;

uniform vec2 iResolution;
uniform float iTime;

//create mainImage function
void mainImage( out vec4 fragColor, in vec2 fragCoord );

//create palette function
vec3 palette(float t );


void main (){
    //set the color of the fragment
    //FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    mainImage(FragColor, gl_FragCoord.xy);
}

vec3 palette(float t ){
    vec3 a = vec3(0.5,0.5,0.5);
    vec3 b = vec3(0.5,0.5,0.5);
    vec3 c = vec3(1.0,1.0,1.0);
    vec3 d = vec3(0.263,0.416,0.557);
    return a +b*cos(6.28318*(c*t+d));
}


void mainImage( out vec4 fragColor, in vec2 fragCoord ){
    //create uv and move the centre to the middle of the screen
    vec2 uv = (fragCoord*2.0-iResolution.xy )/ iResolution.y;

    //create a variable to store the uv
    vec2 uv0 = uv;
    //create a val  for result color
    vec3 finalCol = vec3(0.0);
    for(int i = 0;i <4;i++){

        uv = fract(uv*1.5)-0.5;  
        //create a v3 to store the tempColor 
        vec3 col = palette(length(uv0)+i*.4+iTime*.4);
    
        //create a float d to store the distance
        float d = length(uv)*exp(-length(uv0));
        d = sin(d*8+iTime)/8;

        d = abs(d);
        d = pow(0.01/d,1.2);

        finalCol += col*d;

    }


    

    fragColor = vec4(finalCol, 1.0);


    
}