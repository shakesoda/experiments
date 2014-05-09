attribute vec4 vertex;
attribute vec4 normal;
uniform float Factor;

void main() {
	vec4 position = vertex + normal * Factor;
	// prevent skewing
	position.w = 1.0;
	
	gl_Position = gl_ModelViewProjectionMatrix * position;
}
