#include <GL/gl3w.h>

#include "model.h"
#include "utils/logger.h"

namespace Nepgear
{

void Model::SetMesh(Mesh *m)
{
	m_mesh = m;
}

void Model::SetMaterial(Material *m)
{
	m_material = m;
}

void Model::UploadMesh()
{
	Logger log(NULL);
	if (m_mesh)
		UploadMeshResursive(m_mesh);
	else
		log.warn("[Model] Attempt to upload NULL mesh");
}

void Model::Update(double delta)
{
	if (!delta) return;
}

void Model::Draw(int buffer)
{
	if (buffer > 2) return; // TODO: make useful!
	if (!m_mesh) return;
	DrawRecursive(m_mesh);
}

void Model::UploadMeshResursive(Mesh *child)
{
	if (!child->triangles.empty())
	{
		glGenVertexArrays(1, &child->vao);
		glBindVertexArray(child->vao);

		glGenBuffers(1, &child->buffer);
		glBindBuffer(GL_ARRAY_BUFFER, child->buffer);
		glBufferData(
			GL_ARRAY_BUFFER, child->triangles.size() * sizeof(Vertex),
			&child->triangles[0].position.x, GL_STATIC_DRAW
		);

		// position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), 0);

		// normal
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), (void*)sizeof(glm::vec3));

		// tex coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(Vertex), (void*)sizeof(glm::vec3));

		m_render_stack.push_back(child);
	}
	
	for (size_t i = 0; i < child->children.size(); i++)
	{
			UploadMeshResursive(&child->children[i]);
	}
}

void Model::DrawRecursive(Mesh *child)
{
	//glBindProgram(m_materials[child->material_id]);
	m_material->bind();
	m_material->set_uniform_mat4("Model", child->xform);

	glBindVertexArray(child->vao);
	glDrawArrays(GL_TRIANGLES, 0, child->triangles.size());

	for (size_t i = 0; i < child->children.size(); i++)
	{
			DrawRecursive(&child->children[i]);
	}
}

}