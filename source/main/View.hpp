#pragma once
// Include GLEW
#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/GLU.h>

// Include GLFW
#include <glfw3.h>
#include <vector>

// Include GLM
#include <glm/glm.hpp>
using namespace glm;
#include "common/objloader.hpp"
#include "common/vboindexer.hpp"
#include <glm/gtx/transform.hpp>
#include "common/shader.hpp"
#include "common/controls.hpp"
#include "common/text2D.hpp"
#include "common/texture.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "Model.hpp"

class View {
private:
    
    GLFWwindow* window;
    
    GLuint programID;
	Model* model;
    
    GLuint VertexArrayID;
	//GLuint colorbuffer;

    //screen size
    int width;
    int height;
    
	GLuint MatrixID;
	GLuint ViewMatrixID;
	GLuint ModelMatrixID;
	GLuint LightID;
	GLuint LightPowerID;
	GLuint SpecLobeModID;
	glm::vec3 lightPosition;

	void EnableBindPointer(int key, GLuint buffer);
	void GenBindBufferData(GLuint* buffer, std::vector<glm::vec3> bufferdata);
    
public:
    View(Model* mymodel, int widtht, int heightt);
    ~View();
	glm::mat4 getMVPMatrix(glm::mat4 ModelMatrix);
    int initialise();
    void update();
	
	GLFWwindow* getWindow() { return window; }
};

