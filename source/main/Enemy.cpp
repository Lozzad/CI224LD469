#include "Enemy.hpp"

Enemy::Enemy(glm::vec3 dir) : GameObject()
{
	direction = dir;
}

Enemy::~Enemy()
{
}

void Enemy::reverseDirection()
{
	direction *= -1;
}

glm::vec3 Enemy::getDirection()
{
	return direction;
}


