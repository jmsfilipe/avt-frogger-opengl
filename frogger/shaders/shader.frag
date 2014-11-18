#version 330 core

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

layout (std140) uniform Materials {
	vec4 diffuse;
	vec4 ambient;
	vec4 specular;
	float shininess;
};

// the set of lights to apply, per invocation of this shader
const int MaxLights = 8;
uniform LightProperties Lights[MaxLights];

float Shininess = 100;
float Strength = 1.0;

uniform sampler2D texUnit;

in vec2 TexCoord;
in vec3 Normal, eye, l_dir[8];
in vec4 Position;
in vec4 viewspace;

out vec4 colorOut;
vec3 n, l[8], e;

float dist = 0;
float fogFactor = 0;
const vec4 fogColor = vec4(0.5, 0.5,0.5,1);
const float FogDensity = 0.03;

void main()
{
	e = normalize(eye);
	n = normalize(Normal);

    vec4 scatteredLight = vec4(0.0);
    // or, to a global ambient light
	vec4 reflectedLight = vec4(0.0);
    // loop over all the lights
for ( int light = 0; light < MaxLights; ++light) {

	l[light] = normalize(l_dir[light]);

        if (Lights[light].isEnabled == 0) continue;
        vec3 halfVector;
        vec3 lightDirection = Lights[light].position;
        float attenuation = 1.0;
        // for local lights, compute per-fragment direction, halfVector, and attenuation

if (Lights[light].isLocal) {

            lightDirection = l[light];
            float lightDistance = length(lightDirection);
            lightDirection = lightDirection / lightDistance;
			
            attenuation = 1.0 /
				(Lights[light].constantAttenuation
				+ Lights[light].linearAttenuation * lightDistance
				+ Lights[light].quadraticAttenuation * lightDistance
				* lightDistance);
				
            if (Lights[light].isSpot) {
                float spotCos = dot(lightDirection,-Lights[light].coneDirection);
				
                if (spotCos < Lights[light].spotCosCutoff)
					attenuation = 0.0;
                else
				attenuation *= pow(spotCos, Lights[light].spotExponent);
            }

			halfVector = normalize(l[light] + e);
        }
 else {
            halfVector = Lights[light].position;
        }

float diff = max(0.0, dot(n, l[light]));
float intspec = max(0.0, dot(n, halfVector));
float spec;

        if (diff == 0.0)
			spec = 0.0;
        else
			spec = pow(intspec, Shininess) * Strength;

 	// Accumulate all the lights effects
	scatteredLight += ambient.rgba * attenuation + Lights[light].color * diffuse.rgba * diff * attenuation;
	reflectedLight += Lights[light].color * spec * specular.rgba * attenuation;
    }

vec4 Color = texture2D(texUnit, TexCoord);
vec4 rgba = max(ambient,  scatteredLight + reflectedLight + vec4(Color.rgb, 0.5));

//vec3 rgb = applyFog(rgba.rgb, length(e));
//gl_FragColor =  vec4(rgba.a) * vec4(rgb,1) + vec4(1.0 - rgba.a) * vec4(rgb,1);
if(Color.a < 0.1) discard;

dist = length(viewspace);

    fogFactor = 1.0 /exp(dist * FogDensity);
    fogFactor = clamp( fogFactor, 0.0, 1.0 );
 
    colorOut = mix(fogColor, Color.a * rgba + vec4(1.0 - rgba) * rgba, fogFactor);

}