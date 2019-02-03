#include "GameObject.hpp"

GameObject::GameObject() {
	scale = glm::vec3(1, 1, 1);
}
GameObject::~GameObject() {
}

void GameObject::loadObject(const char* key) {
	loadAssImp(key, indices, vertices, uvs, normals);
}
void GameObject::fillColour(glm::vec3 colour) {
	for (int i = 0; i < vertices.size(); i++) {
		colors.push_back(colour);
	}
}

void GameObject::createBoundingBox() {
	//gives aabb box
	boundingbox_min.x = boundingbox_max.x = vertices[0].x;
	boundingbox_min.y = boundingbox_max.y = vertices[0].y;
	boundingbox_min.z = boundingbox_max.z = vertices[0].z;
	for (int i = 0; i < vertices.size(); i++) {
		if (vertices[i].x < boundingbox_min.x) { boundingbox_min.x = vertices[i].x; }
		if (vertices[i].x > boundingbox_max.x) { boundingbox_max.x = vertices[i].x; }
		if (vertices[i].y < boundingbox_min.y) { boundingbox_min.y = vertices[i].y; }
		if (vertices[i].y > boundingbox_max.y) { boundingbox_max.y = vertices[i].y; }
		if (vertices[i].z < boundingbox_min.z) { boundingbox_min.z = vertices[i].z; }
		if (vertices[i].z > boundingbox_max.z) { boundingbox_max.z = vertices[i].z; }
	}
	
	boundingbox = new BoundingBox(boundingbox_min, boundingbox_max);
}

BoundingBox* GameObject::getBoundingBox() {
	return boundingbox;
}

GLuint* GameObject::getVertexBuffer()
{
	return &vertexBuffer;
}
GLuint * GameObject::getColorBuffer()
{
	return &colorBuffer;
}
GLuint * GameObject::getNormalBuffer()
{
	return &normalBuffer;
}
std::vector<glm::vec3> GameObject::getVertices()
{
	return vertices;
}
std::vector<glm::vec3> GameObject::getColors()
{
	return colors;
}
std::vector<glm::vec2> GameObject::getUVs()
{
	return uvs;
}
std::vector<glm::vec3> GameObject::getNormals()
{
	return normals;
}
void GameObject::setPosition(glm::vec3 pos) {
	position = pos;
}

void GameObject::updatePosition(glm::vec3 move)
{
	position += move;
}

glm::vec3 GameObject::getPosition()
{
	return position;
}

void GameObject::setRotation(glm::vec3 newRotation)
{
	rotation = newRotation;
}

void GameObject::updateRotation(glm::vec3 rotationM)
{
	rotation = rotationM;
}

glm::vec3 GameObject::getRotation()
{
	return rotation;
}

void GameObject::setScale(glm::vec3 newScale)
{
	scale = newScale;
}

glm::vec3 GameObject::getScale()
{
	return scale;
}

bool GameObject::isAlive()
{
	return alive;
}

void GameObject::setAlive(bool living)
{
	alive = living;
}

