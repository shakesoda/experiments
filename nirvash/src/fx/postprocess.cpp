#include <GL/glcorearb.h>
#include "postprocess.h"

namespace Nepgear
{
void PostProcessEffect::init(int width, int height)
{
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(
		GL_TEXTURE_2D, 0, GL_RGBA8, width, height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, 0
	);

	// renderbuffer handle
	GLuint rbf;
	
	// generate renderbuffers
	glGenRenderbuffers(1, &rbf);
	glBindRenderbuffer(GL_RENDERBUFFER, rbf);
	glRenderbufferStorage(
		GL_RENDERBUFFER, GL_DEPTH_COMPONENT24,
		width, height
	);

	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

	glFramebufferTexture2D(
		GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0
	);
	glFramebufferRenderbuffer(
		GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbf
	);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	if (vao != 0) return;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	GLfloat post_effect_vertexData[] = {
			1.0f, 1.0f, 0.0f,       1.0f, 1.0f,
		-1.0f, 1.0f, 0.0f,       0.0f, 1.0f,
			1.0f,-1.0f, 0.0f,       1.0f, 0.0f,
		-1.0f,-1.0f, 0.0f,       0.0f, 0.0f,
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*4*5, post_effect_vertexData, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (char*)0 + 0*sizeof(GLfloat));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (char*)0 + 3*sizeof(GLfloat));

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	GLuint post_effect_indexData[] = { 0,1,2, 2,1,3, };

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*2*3, post_effect_indexData, GL_STATIC_DRAW);
	//if(glGetError()) log.warn("problem! L#%d",__LINE__);
}

void PostProcessEffect::load(std::string shader)
{
	m_material.load(shader);
	m_material.bind();
	m_material.set_uniform_int("Texture", 0);
}

void PostProcessEffect::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
}

void PostProcessEffect::draw()
{
	m_material.bind();

	glBindVertexArray(vao);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glDisable(GL_DEPTH_TEST);
	glDisableVertexAttribArray(1);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glEnableVertexAttribArray(1);
	glEnable(GL_DEPTH_TEST);
}

void PostProcessEffect::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

unsigned PostProcessEffect::vao = 0;
unsigned PostProcessEffect::vbo = 0;
unsigned PostProcessEffect::ibo = 0;

} 
