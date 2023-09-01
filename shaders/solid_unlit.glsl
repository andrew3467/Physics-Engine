#vertex
#version 460 core

layout (location = 0) in vec3 aPos;

//uniform mat4 proj;
//uniform mat4 view;
//transform info
//uniform mat4 model;

out vec3 pos;

void main()
{
    pos = aPos;
    gl_Position = vec4(aPos, 1.0);
}


#fragment
#version 460 core

out vec4 FragColor;

in vec3 pos;

void main() {
    FragColor = vec4(pos, 1.0);
}
