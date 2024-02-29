#version 330 core
out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D image;

//a bool to check if the texture is horizontal
uniform bool horizontal;

//create a val for the weights
uniform float weight[5] = float[] (0.2270270270, 0.1945945946, 0.1216216216, 0.0540540541, 0.0162162162);

void main(){
    //get the offset of the texture
    vec2 tex_offset = 1.0 / textureSize(image, 0); // gets size of single texel
    //create a val to store the color
    vec3 result = texture(image, texCoord).rgb * weight[0]; // current fragment's value
    if(horizontal){
        for(int i = 1; i < 5; ++i){
            result += texture(image, texCoord + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
            result += texture(image, texCoord - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
        }
    }else{
        for(int i = 1; i < 5; ++i){
            result += texture(image, texCoord + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
            result += texture(image, texCoord - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
        }
    }
    FragColor = vec4(result, 1.0);

}

