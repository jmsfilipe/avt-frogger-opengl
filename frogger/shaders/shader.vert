#version 330 core

layout (std140) uniform Matrices {
    mat4 m_pvm;
    mat4 m_viewModel;
    mat3 m_normal;
};

struct LightProperties {
    int isEnabled;
    int isLocal; //point
    int isSpot; //spotlight
    vec4 color;
    vec3 position;
    vec3 coneDirection;
    float spotCosCutoff;
    float spotExponent;
    float constantAttenuation;
    float linearAttenuation;
    float quadraticAttenuation;
};

in vec2 texCoord;
in vec3 normal;
in vec4 position;

out vec2 TexCoord;
out vec3 Normal;
out vec3 l_dir[8], eye;
out vec4 viewspace;

const int MaxLights = 8;

uniform LightProperties Lights[MaxLights];

void main()
{
    TexCoord = texCoord;
    Normal = normalize(m_normal * normal);
    vec4 Position = m_viewModel * position;

	for(int i = 0; i < MaxLights; i++){
	vec4 light_pos=  m_viewModel * vec4(Lights[i].position,1);
	l_dir[i] = vec3 (light_pos.xyz - Position.xyz);
	}
	eye = vec3(-Position);
	viewspace = m_viewModel*vec4(position.xyz,1);

    gl_Position = m_pvm * position;
}
