#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glfw3.h>
#include "GameObject.hpp"

class Enemy: public GameObject {
private:
	glm::vec3 direction;
public:
	Enemy(glm::vec3 dir);
	~Enemy();
	void reverseDirection();
	glm::vec3 getDirection();
};