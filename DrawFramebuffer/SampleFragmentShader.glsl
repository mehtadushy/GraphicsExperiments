#version 150

in vec2 Texcoord;
in vec3 Color;

out vec4 outcolor;
uniform sampler2D tex;
uniform uint choice;

void main()
{
   if(choice==0u)
   {
    outcolor = texture(tex, Texcoord);
   }
   else
   {
      outcolor= vec4(Color,1.0f);
   }
}
