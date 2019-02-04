// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
#include <iostream>
#include <vector>
#include "View.hpp"
#include "Model.hpp"
#include "Controller.h"
#include <glm/gtc/matrix_transform.hpp>


int H = 2048; // Height of window
int W = 2048; // Width of window

int main(void)
{

	//initialise model
	Model* mymodel = new Model();
	//initialise myview
	View* myview = new View(mymodel, W, H);
	//initialise Controller
	Controller* mycontroller = new Controller(myview, mymodel);
	
	//initialise the scene and if succesful go into the control loop to wait for user input
	if (myview->initialise() != -1) {
        mycontroller->loop();
    }	else {
		std::cout << "ERROR: The game has not been initialised correctly" << std::endl;
		return 0;
	}
	
	return 0;
}

