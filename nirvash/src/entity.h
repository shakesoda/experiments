#ifndef _NEPGEAR_ENTITY_H_
#define _NEPGEAR_ENTITY_H_

#include <vector>
#include <glm/glm.hpp>

class Entity
{
public:
	Entity();
	virtual ~Entity();

//	virtual void update(double dt) {}
	
	Entity *parent;
	std::vector<Entity> children;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};

#endif
