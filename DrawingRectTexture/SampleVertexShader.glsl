#version 150

in vec2 texcoord;
in vec2 position;
//in vec3 color;

//out vec3 Color;
out vec2 Texcoord;

void main()
{
    Texcoord= texcoord;
    //Color=color;
    gl_Position = vec4(position, 0.0, 1.0);
}
