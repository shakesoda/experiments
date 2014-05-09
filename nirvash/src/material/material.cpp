#include <stdlib.h>
#include <stdio.h>
#include "material.h"
#include "file.h"
#include "utils/logger.h"

using namespace Nepgear;

/* eat a dick, opengl. I should be able to use one function for both. */
namespace
{
	#define iif(cond, fn1, fn2) (cond ? fn1 : fn2)

	int print_info_log(GLuint shader)
	{
		Logger log;

		GLint status;
		GLchar *error;
		bool select = (bool)glIsShader(shader);
		GLenum which = iif(select, GL_COMPILE_STATUS, GL_LINK_STATUS);

		void (*GetProg)(GLuint, GLenum, GLint*);
		void (*GetProgInfo)(GLuint, GLsizei, GLsizei*, GLchar*);

		GetProg = iif(select, glGetShaderiv, glGetProgramiv);
		GetProgInfo = iif(select, glGetShaderInfoLog, glGetProgramInfoLog);

		GetProg(shader, which, &status);
		if (!status)
		{
			/* reuse status for count */
			GetProg(shader, GL_INFO_LOG_LENGTH, &status);
			if (status > 0)
			{
				GetProgInfo(shader, status, NULL, (error = new char[status+1]));
				log.error("%s", error);
				delete[] error;

				return 1;
			}
		}

		return 0;
	}
	#undef iif
}

void Material::load(std::string path)
{
	Logger log;

	assert(path.size() > 0);

	File shader(path);

	std::string vs = shader.get_section("Vertex");
	std::string fs = shader.get_section("Fragment");

	// fugly ugly
	const char *vsp = vs.c_str(), *fsp = fs.c_str();

	/*
	printf( "----------------\n"
		"%s\n"
		"----------------\n"
		"%s\n"
		"----------------\n",
		vs.c_str(), fs.c_str()
	);
	*/

	int err = 0;

	program.vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	program.fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

	/* load shader */
	glShaderSource(program.vertex_shader, 1, &vsp, NULL);
	glShaderSource(program.fragment_shader, 1, &fsp, NULL);

	glCompileShader(program.vertex_shader);
	glCompileShader(program.fragment_shader);

	program.shader_program = glCreateProgram();

	glAttachShader(program.shader_program, program.vertex_shader);
	glAttachShader(program.shader_program, program.fragment_shader);

	glBindAttribLocation(program.shader_program, 0, "vPosition");
	glBindAttribLocation(program.shader_program, 1, "vNormal");
	glBindAttribLocation(program.shader_program, 2, "vTexCoord");

	glBindFragDataLocation(program.shader_program, 0, "FragColor");

	glLinkProgram(program.shader_program);
	glValidateProgram(program.shader_program);

	/* accumulate so we don't need to bother checking between calls. */
	err += print_info_log(program.vertex_shader);
	if (!err) err += print_info_log(program.fragment_shader);
	if (!err) err += print_info_log(program.shader_program);
	if (err) log.error("Something went terribly wrong with the shaders!");
}

void Material::unload()
{
	/* detach and delete shaders. */
	glDetachShader(program.shader_program, program.vertex_shader);
	glDetachShader(program.shader_program, program.fragment_shader);

	glDeleteShader(program.vertex_shader);
	glDeleteShader(program.fragment_shader);

	glDeleteProgram(program.shader_program);
}

void Material::bind()
{
	glUseProgram(this->program.shader_program);
}
