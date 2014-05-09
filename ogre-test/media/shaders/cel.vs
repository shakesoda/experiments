attribute vec4 vertex;
attribute vec4 normal;
attribute vec2 uv0;

varying vec2 vCoord;
varying vec3 vPos, vNor;

void main() {
	vCoord = uv0;
	vPos = (gl_ModelViewMatrix * vertex).xyz;
	vNor = normal.xyz;

	gl_Position = gl_ModelViewProjectionMatrix * vertex;
}
