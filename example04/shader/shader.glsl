#type vertex
#version 330

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 mvp;

out vec3 p;

void main()
{
        gl_Position = mvp * vec4(aPos, 1.0);
        p = aPos + 0.3;
}

#type fragment
#version 330

out vec4 color;

in vec3 p;

void main()
{
    // color = vec4(0.21, 0.33, 0.73, 1.0);
    color = vec4(p, 1.0);
}