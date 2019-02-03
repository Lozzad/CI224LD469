#include "BoundingBox.h"

BoundingBox::BoundingBox(glm::vec3 minValues, glm::vec3 maxValues) {
	min = minValues;
	max = maxValues;
	size = glm::vec3(max.x-min.x, max.y-min.y, max.z-min.z);
}

BoundingBox::~BoundingBox() {
}

glm::vec3 BoundingBox::getSize()
{
	return size;
}
