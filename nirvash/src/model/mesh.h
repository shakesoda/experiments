#ifndef _NEPGEAR_MESH_H_
#define _NEPGEAR_MESH_H_

#include <vector>
#include <glm/glm.hpp>

namespace Nepgear
{

struct Bone
{
	Bone() : previous(NULL), next(NULL) {}
	int id;
	glm::vec3 position;
	glm::vec4 orientation;
	Bone *previous, *next;
};

struct Vertex
{
	glm::vec3 position, normal;
	glm::vec2 tex_coords;
	glm::vec4 color;
	float weights[4];
//	unsigned bone;
};

struct Mesh
{
	Mesh() : vao(0), buffer(0) {}

	int material_id;

	std::vector<Vertex> points;
	std::vector<Vertex> lines;
	std::vector<Vertex> triangles;

	glm::mat4 xform;

	Mesh *parent;
	std::vector<Mesh> children;

	// GL stuff
	unsigned vao;
	unsigned buffer;
};

}

#endif
