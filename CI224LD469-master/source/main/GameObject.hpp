#pragma once
//include GLEW, GLFW
#include <GL/glew.h>
#include <glfw3.h>
#include <vector>
#include <glm/glm.hpp>
using namespace glm;
using namespace std;
#include "common/objloader.hpp"
#include "common/vboindexer.hpp"
#include "BoundingBox.h"


class GameObject {
	private:
		GLuint vertexBuffer;
		GLuint colorBuffer;
		GLuint normalBuffer;

		std::vector<unsigned short> indices;
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec3> colors;
		std::vector<glm::vec2> uvs;
		std::vector<glm::vec3> normals;

		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;

		bool alive = true;

		glm::vec3 boundingbox_min;
		glm::vec3 boundingbox_max;
		BoundingBox* boundingbox;



	public:
		GameObject();
		~GameObject();
		
		void loadObject(const char* key);
		void fillColour(glm::vec3 colour);
		void createBoundingBox();
		BoundingBox* getBoundingBox();
		
		//getters and setters
		//model info
		GLuint* getVertexBuffer();
		GLuint* getColorBuffer();
		GLuint* getNormalBuffer();

		std::vector<glm::vec3> getVertices();
		std::vector<glm::vec3> getColors();
		std::vector<glm::vec2> getUVs();
		std::vector<glm::vec3> getNormals();

		//pos
		void setPosition(glm::vec3 pos);
		void updatePosition(glm::vec3 move);
		glm::vec3 getPosition();
		
		//rotation
		void setRotation(glm::vec3 newRotation);
		void updateRotation(glm::vec3 rotationM);
		glm::vec3 getRotation();
		
		//scale
		void setScale(glm::vec3 newScale);
		glm::vec3 getScale();

		bool isAlive();
		void setAlive(bool living);
};