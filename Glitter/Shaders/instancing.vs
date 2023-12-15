#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aOffset;

out vec3 fColor;

void main()
{
    fColor = aColor;
    vec2 pos = aPos + aOffset; // Apply the offset to the quad's position
    gl_Position = vec4(pos, 0.0, 1.0);
}
