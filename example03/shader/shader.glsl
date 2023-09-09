#type vertex
#version 330

layout (location = 0) in vec3 pos;

void main()
{
        gl_Position = vec4(pos, 1.0);
}

#type fragment
#version 330

out vec4 color;

void main()
{
    color = vec4(0.6, 0.2, 0.4, 1.0);
}