#version 150

in vec2 Texcoord;
out vec4 outcolor;
uniform sampler2D tex;

void main()
{
    outcolor = texture(tex, Texcoord);
}
