#ifndef _NEPGEAR_MATERIAL_H_
#define _NEPGEAR_MATERIAL_H_

#include <GL/gl3w.h>

#include <map>
#include <string>
#include <glm/glm.hpp>

// yeah this kind of fucks up everything.
#define UNIFORM_TYPE(type) \
void set_uniform_##type(std::string key, type data) \
{ \
	unsigned location = 0; \
	std::map<std::string, unsigned>::iterator it = uniforms.find(key); \
	if (it == uniforms.end()) \
	{ \
		location = glGetUniformLocation(program.shader_program, \
			key.c_str()); \
		uniforms[key] = location;\
	} \
	else\
		location = it->second;

#define POD_UNIFORM_TYPE(type, fn) \
	UNIFORM_TYPE(type); \
	fn(location, 1, &data); \
}

// These use GLM, matrix is separate because the GL functions take 4 args.
#define VECTOR_UNIFORM_TYPE(type, fn) \
	UNIFORM_TYPE(type); \
	fn(location, 1, &data[0]); \
}

#define MATRIX_UNIFORM_TYPE(type, fn) \
	UNIFORM_TYPE(type); \
	fn(location, 1, 0, &data[0].x); \
}

using namespace glm;

namespace Nepgear
{

class Material
{
public:
	void load(std::string path);
	void unload();
	void bind();

	// usage: set_uniform_<type>(name, data)
	POD_UNIFORM_TYPE(float, glUniform1fv);
	POD_UNIFORM_TYPE(int, glUniform1iv);
	VECTOR_UNIFORM_TYPE(vec2, glUniform2fv);
	VECTOR_UNIFORM_TYPE(vec3, glUniform3fv);
	MATRIX_UNIFORM_TYPE(mat2, glUniformMatrix2fv);
	MATRIX_UNIFORM_TYPE(mat4, glUniformMatrix4fv);
	
protected:
	struct {
		GLuint vertex_shader;
		GLuint fragment_shader;
		GLuint shader_program;
	} program;
	
	std::map<std::string, unsigned> uniforms;
};

}

#undef UNIFORM_TYPE
#undef POD_UNIFORM_TYPE
#undef VECTOR_UNIFORM_TYPE
#undef MATRIX_UNIFORM_TYPE

#endif

