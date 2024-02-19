#version 330 core
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

//in vec2 texCoord;
in VS_OUT {
    vec2 TexCoord;
    vec3 Normal;
    vec3 FragPos;
} fs_in;

//create a val for lightColor
uniform vec3 lightColor;

void main()
{    
    FragColor = vec4(lightColor, 1.0);
    //caculate the brightColor
    //create a val to store the val of dot
    float brightness = dot(FragColor.rgb, vec3(0.2126, 0.7152, 0.0722));
    //check if the brightness is greater than 1
    if(brightness > 1.0)
    {
        //set the brightColor to the FragColor
        BrightColor = vec4(FragColor.rgb, 1.0);
    }
    else
    {
        //set the brightColor to black
        BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
    }    
}    