-- Vertex
#version 150
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

in vec3 vPosition;
in vec3 vNormal;

out vec3 Normal;

void main()
{
	Normal = mat3(View) * vNormal;
	
	gl_Position = Projection * View * Model * vec4(vPosition, 1.0);
}

-- Fragment
#version 150

uniform vec3 LightDirection;

uniform mat4 View;

in vec3 Normal;

out vec4 FragColor;

void main()
{
	vec3 EyeDirection = vec3(0.0, 0.0, 1.0);

	//float fresnel = dot(Normal, EyeDirection) * 1.4;
	float intensity = dot(Normal, LightDirection);

	//FragColor = vec4(vec3(mix(fresnel, intensity, 1.0)), 1.0);
	FragColor = vec4(intensity);
	FragColor.a = dot(FragColor.rgb, vec3(0.299, 0.587, 0.114));
}
