#version 330 core
//out vec4 FragColor;
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

in vec2 TexCoords;

// texture sampler diffuse
uniform sampler2D texture_diffuse;
//texture sampler specular;
uniform sampler2D texture_specular;
//create a time
uniform float time;


void main (){   
    FragColor = texture(texture_diffuse, TexCoords), texture(texture_specular, TexCoords);
    //if have the red color 
    //if(FragColor.r > 0.5)
    //{
    //    //set the brightColor to the FragColor and improve the red color
    //    BrightColor = vec4(10.0f, 0.0f, 0.0f, 1.0);        
    //}
    //else
    //{
    //    //set the brightColor to black
    //    BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
    //}

    //use sin to get the value of the time
    float factor = sin(time) * 0.5 + 0.5;

    BrightColor = vec4(factor*15, 0.0f, 0.0f, 1.0);   
    //float brightness = dot(FragColor.rgb, vec3(0.2126, 0.7152, 0.0722));
    //if(brightness > 1.0)
    //{
    //    //set the brightColor to the FragColor
    //    BrightColor = vec4(FragColor.rgb, 1.0);
    //}
    //else
    //{
    //    //set the brightColor to black
    //    BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
    //} 
}
