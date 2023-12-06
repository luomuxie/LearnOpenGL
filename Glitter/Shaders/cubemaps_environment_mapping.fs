#version 330 core
out vec4 FragColor;

//create in normal
in vec3 Normal;
//create in Position
in vec3 Position;

//create a vec3 for the camera position
uniform vec3 cameraPos;
//create a samplerCube for the cubemap
uniform samplerCube skybox;



void main()
{        
    //calculate the view direction
    vec3 viewDir = normalize(cameraPos - Position);


    ////calculate the reflection direction
    //vec3 reflectDir = reflect(viewDir, normalize(Normal));
    ////flip the y coordinate
    //reflectDir.y *= -1.0; 
    ////calculate the color from the cubemap texture
    //FragColor = vec4(texture(skybox, reflectDir).rgb, 1.0);

    //create a ratio
    float ratio = 1.00 / 1.52;
    //calculate the refraction direction
    vec3 refractDir = refract(viewDir, normalize(Normal), ratio);
    //flip the y coordinate
    refractDir.y *= -1.0; 
    //calculate the color from the cubemap texture
    FragColor = vec4(texture(skybox, refractDir).rgb, 1.0);


}   