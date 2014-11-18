#version 330
 
layout (std140) uniform Matrices {
 
    mat4 m_proj;
    mat4 m_viewModel;
};
 
in vec3 position;
in vec2 texCoord;
 
out vec4 vertexPos;
out vec2 TexCoord;
 
void main()
{
    TexCoord = vec2(texCoord);
    gl_Position = m_proj * m_viewModel* vec4(position,1.0);
}