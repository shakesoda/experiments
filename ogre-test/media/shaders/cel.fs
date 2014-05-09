uniform sampler2D colorTexture;
uniform vec4 shadowColor;
varying vec2 vCoord;
varying vec3 vPos, vNor;

void main() {
	vec3 nor, pos, ref, light;
	nor = normalize(vNor);
	pos = normalize(vPos);
	ref = reflect(pos, nor);
	
	vec4 diffuse, specular, color, lightSource;
	float ambient = length(gl_FrontMaterial.ambient.rgb);
	lightSource = gl_LightSource[0].position;
	light = normalize(gl_ModelViewMatrix * lightSource).xyz;
	
	color = texture2D(colorTexture, vCoord.st);
	float intensity = max(dot(light,nor), 0.0);
	if (intensity < 0.5) {
		intensity *= 0.5;
		color *= shadowColor;
	}
	intensity = min(clamp(intensity, ambient, 1.0) + 0.25, 1.0);
	
	gl_FragColor = color * intensity;
}
