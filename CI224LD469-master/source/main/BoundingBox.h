#pragma once
#include <GL/glew.h>
#include <glfw3.h>
#include <vector>
#include <glm/glm.hpp>

class BoundingBox {
private:
	glm::vec3 size;
	glm::vec3 min;
	glm::vec3 max;

public:
	BoundingBox(glm::vec3 minValues, glm::vec3 maxValues);
	~BoundingBox();
	glm::vec3 getSize();
	glm::vec3 getMin() { return min; }
	glm::vec3 getMax() { return max; }
};