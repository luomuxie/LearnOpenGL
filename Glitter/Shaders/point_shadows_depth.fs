#version 330 core
in vec4 FragPos;

uniform vec3 lightPos;
uniform float far_plane;



void main()
{       
    //cal light distance
    float lightDistance = length(FragPos.xyz - lightPos);
    // trans to NDC
    lightDistance = lightDistance / far_plane;
    //write this to the depth map
    gl_FragDepth = lightDistance;

}   