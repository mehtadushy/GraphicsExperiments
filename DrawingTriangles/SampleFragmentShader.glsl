#version 150

in vec3 Color;
out vec4 outcolor;

void main()
{
    outcolor = vec4(Color, 1.0);
}
