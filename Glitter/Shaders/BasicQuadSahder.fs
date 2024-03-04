#version 330 core
out vec4 FragColor;

in vec2 texCoord;

//texture ourTexture;
uniform sampler2D ourTexture;


void main(){
    //get the color from the scene
    vec3 color = texture(ourTexture, texCoord).rgb;    
    //set the color of the fragment
    FragColor = vec4(color, 1.0);
}

