#version 330
 
uniform sampler2D texUnit;
 
in vec2 TexCoord;
out vec4 outputF;
 
void main()
{
    outputF = texture2D(texUnit, TexCoord);
}