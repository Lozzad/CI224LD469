#include "View.hpp"

View::View(Model* mymodel, int widtht, int heightt) {
	width = widtht;
	height = heightt;
	model = mymodel;
}
View::~View() {
	//cleanup VBO and shader
	glDeleteBuffers(1, model->getPlayer()->getVertexBuffer());
	glDeleteBuffers(1, model->getPlayer()->getColorBuffer());
	glDeleteBuffers(1, model->getPlayer()->getNormalBuffer());
	for (int i = 0; i < model->getWalls().size(); i++) {
		glDeleteBuffers(1, model->getWalls()[i]->getVertexBuffer());
		glDeleteBuffers(1, model->getWalls()[i]->getColorBuffer());
		glDeleteBuffers(1, model->getWalls()[i]->getNormalBuffer());
	}
	for (int i = 0; i < model->getFloors().size(); i++) {
		glDeleteBuffers(1, model->getFloors()[i]->getVertexBuffer());
		glDeleteBuffers(1, model->getFloors()[i]->getColorBuffer());
		glDeleteBuffers(1, model->getFloors()[i]->getNormalBuffer());
	}
	for (int i = 0; i < model->getCollectables().size(); i++) {
		glDeleteBuffers(1, model->getCollectables()[i]->getVertexBuffer());
		glDeleteBuffers(1, model->getCollectables()[i]->getColorBuffer());
		glDeleteBuffers(1, model->getCollectables()[i]->getNormalBuffer());
	}
	for (int i = 0; i < model->getWalls().size(); i++) {
		glDeleteBuffers(1, model->getWalls()[i]->getVertexBuffer());
		glDeleteBuffers(1, model->getWalls()[i]->getColorBuffer());
		glDeleteBuffers(1, model->getWalls()[i]->getNormalBuffer());
	}
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);
	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}

glm::mat4 View::getMVPMatrix(glm::mat4 ModelMatrix) {
	glm::mat4 Projection = glm::perspective(
		glm::radians(50.0f),
		1.0f,
		0.1f,
		100.0f
		);
	glm::mat4 Model = ModelMatrix;
	glm::mat4 mvp = Projection * model->ComputeViewMatrix() * Model;

	return mvp;
}

int View::initialise() {

	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



	// Open a window and create its OpenGL context
	window = glfwCreateWindow(width, height, "My Game", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//for getting the esc key
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	//hide mouse and enable unlimited movement
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//set mouse at center screen
	glfwPollEvents();
	glfwSetCursorPos(window, width / 2, height / 2);

	// Initialize GLEW
	glewExperimental = GL_TRUE; //needed for core profile

	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	
	//we set the cursor at the centre so that it always start on our origin (0,0,0)
	glfwSetCursorPos(window, width / 2, height / 2);


	// background
	glClearColor(0, 0, 0, 0.01);

	//define vertex array
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	//send vert info for player to GL using vertex buffer
	GenBindBufferData(model->getPlayer()->getVertexBuffer(), model->getPlayer()->getVertices());
	//normal info 
	GenBindBufferData(model->getPlayer()->getColorBuffer(), model->getPlayer()->getColors());
	//colors 
	GenBindBufferData(model->getPlayer()->getNormalBuffer(), model->getPlayer()->getNormals());

	//same for the walls
	for (int i = 0; i < model->getWalls().size(); i++) {
		GenBindBufferData(model->getWalls()[i]->getVertexBuffer(), model->getWalls()[i]->getVertices());
		GenBindBufferData(model->getWalls()[i]->getColorBuffer(), model->getWalls()[i]->getColors());
		GenBindBufferData(model->getWalls()[i]->getNormalBuffer(), model->getWalls()[i]->getNormals());
	}
	//and floors
	for (int i = 0; i < model->getFloors().size(); i++) {
		GenBindBufferData(model->getFloors()[i]->getVertexBuffer(), model->getFloors()[i]->getVertices());
		GenBindBufferData(model->getFloors()[i]->getColorBuffer(), model->getFloors()[i]->getColors());
		GenBindBufferData(model->getFloors()[i]->getNormalBuffer(), model->getFloors()[i]->getNormals());
	}
	//and coins
	for (int i = 0; i < model->getCollectables().size(); i++) {
		GenBindBufferData(model->getCollectables()[i]->getVertexBuffer(), model->getCollectables()[i]->getVertices());
		GenBindBufferData(model->getCollectables()[i]->getColorBuffer(), model->getCollectables()[i]->getColors());
		GenBindBufferData(model->getCollectables()[i]->getNormalBuffer(), model->getCollectables()[i]->getNormals());
	}
	//enemies
	for (int i = 0; i < model->getEnemies().size(); i++) {
		GenBindBufferData(model->getEnemies()[i]->getVertexBuffer(), model->getEnemies()[i]->getVertices());
		GenBindBufferData(model->getEnemies()[i]->getColorBuffer(), model->getEnemies()[i]->getColors());
		GenBindBufferData(model->getEnemies()[i]->getNormalBuffer(), model->getEnemies()[i]->getNormals());
	}


	programID = LoadShaders("SimpleVertexShader.hlsl", "SimpleFragmentShader.hlsl");

	MatrixID = glGetUniformLocation(programID, "MVP");
	ViewMatrixID = glGetUniformLocation(programID, "V");
	ModelMatrixID = glGetUniformLocation(programID, "M");
	LightID = glGetUniformLocation(programID, "LightPosition_worldspace");
	LightPowerID = glGetUniformLocation(programID, "LightPower");
	SpecLobeModID = glGetUniformLocation(programID, "SpecLobeMod");
	lightPosition = glm::vec3(model->getPlayer()->getPosition());

	return 1;
}

void View::update() {
		// Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		
		glEnable(GL_DEPTH_TEST);
		
		//use our shaders
		glUseProgram(programID);
		lightPosition = model->getPlayer()->getPosition();
		
		glm::mat4 ModelMatrixPlayer = glm::translate(model->getPlayer()->getPosition()) * glm::scale(model->getPlayer()->getScale());

		glm::mat4 mvp1 = getMVPMatrix(ModelMatrixPlayer);

		glUniform1f(LightPowerID, model->getLightPower());
		glUniform1f(SpecLobeModID, model->getSpecLobeMod());
		glUniform3f(LightID, lightPosition.x, lightPosition.y, lightPosition.z);
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp1[0][0]);
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &model->ComputeViewMatrix()[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrixPlayer[0][0]);


		//verts
		EnableBindPointer(0, *model->getPlayer()->getVertexBuffer());
		//colors
		EnableBindPointer(1, *model->getPlayer()->getColorBuffer());
		//normals
		EnableBindPointer(2, *model->getPlayer()->getNormalBuffer());
		//the mesh is then drawn
		glDrawArrays(GL_TRIANGLES, 0, model->getPlayer()->getVertices().size());

		//end of drawing the player
		//draw walls
		for (int i = 0; i < model->getWalls().size(); i++) {
			glm::mat4 ModelMatrixWall = glm::translate(model->getWalls()[i]->getPosition()) * glm::scale(model->getWalls()[i]->getScale());
			glm::mat4 mvpWall = getMVPMatrix(ModelMatrixWall);
			//set new uniforms for each wall
			glUniform1f(LightPowerID, model->getLightPower());
			glUniform3f(LightID, lightPosition.x, lightPosition.y, lightPosition.z);
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvpWall[0][0]);
			glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &model->ComputeViewMatrix()[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrixWall[0][0]);
			//Bind the bufffers
			//verts
			EnableBindPointer(0, *model->getWalls()[i]->getVertexBuffer());
			//colors
			EnableBindPointer(1, *model->getWalls()[i]->getColorBuffer());
			//normals
			EnableBindPointer(2, *model->getWalls()[i]->getNormalBuffer());
			//draw
			glDrawArrays(GL_TRIANGLES, 0, model->getWalls()[i]->getVertices().size());
		}
		//and floors
		for (int i = 0; i < model->getFloors().size(); i++) {
			glm::mat4 ModelMatrixFloor = glm::translate(model->getFloors()[i]->getPosition()) * glm::scale(model->getFloors()[i]->getScale());
			glm::mat4 mvpFloor = getMVPMatrix(ModelMatrixFloor);
			//set new uniforms for each floor
			glUniform1f(LightPowerID, model->getLightPower());
			glUniform3f(LightID, lightPosition.x, lightPosition.y, lightPosition.z);
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvpFloor[0][0]);
			glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &model->ComputeViewMatrix()[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrixFloor[0][0]);
			//Bind the bufffers
			//verts
			EnableBindPointer(0, *model->getFloors()[i]->getVertexBuffer());
			//colors
			EnableBindPointer(1, *model->getFloors()[i]->getColorBuffer());
			//normals
			EnableBindPointer(2, *model->getFloors()[i]->getNormalBuffer());
			//draw
			glDrawArrays(GL_TRIANGLES, 0, model->getFloors()[i]->getVertices().size());
		}
		//and collectables
		for (int i = 0; i < model->getCollectables().size(); i++) {
			if (model->getCollectables()[i]->isAlive()) {
				glm::mat4 ModelMatrixCollectable = glm::translate(model->getCollectables()[i]->getPosition()) * glm::scale(model->getCollectables()[i]->getScale());
				glm::mat4 mvpCollectable = getMVPMatrix(ModelMatrixCollectable);
				//set new uniforms for each collectable
				glUniform1f(LightPowerID, model->getLightPower());
				glUniform3f(LightID, lightPosition.x, lightPosition.y, lightPosition.z);
				glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvpCollectable[0][0]);
				glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &model->ComputeViewMatrix()[0][0]);
				glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrixCollectable[0][0]);
				//Bind the bufffers
				//verts
				EnableBindPointer(0, *model->getCollectables()[i]->getVertexBuffer());
				//colors
				EnableBindPointer(1, *model->getCollectables()[i]->getColorBuffer());
				//normals
				EnableBindPointer(2, *model->getCollectables()[i]->getNormalBuffer());
				//draw
				glDrawArrays(GL_TRIANGLES, 0, model->getCollectables()[i]->getVertices().size());
			}
		}
		//enemies
		for (int i = 0; i < model->getEnemies().size(); i++) {
			glm::mat4 ModelMatrixEnemy = glm::translate(model->getEnemies()[i]->getPosition());
			glm::mat4 mvpEnemy = getMVPMatrix(ModelMatrixEnemy);
			//set new uniforms for each enemy
			glUniform1f(LightPowerID, model->getLightPower());
			glUniform3f(LightID, lightPosition.x, lightPosition.y, lightPosition.z);
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvpEnemy[0][0]);
			glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &model->ComputeViewMatrix()[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrixEnemy[0][0]);
			//Bind the bufffers
			//verts
			EnableBindPointer(0, *model->getEnemies()[i]->getVertexBuffer());
			//colors
			EnableBindPointer(1, *model->getEnemies()[i]->getColorBuffer());
			//normals
			EnableBindPointer(2, *model->getEnemies()[i]->getNormalBuffer());
			//draw
			glDrawArrays(GL_TRIANGLES, 0, model->getEnemies()[i]->getVertices().size());
		}
		//end of drawing stage
		
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
}

//cutting down on code reuse
void View::EnableBindPointer(int key, GLuint buffer) {
	glEnableVertexAttribArray(key);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glVertexAttribPointer(key, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

void View::GenBindBufferData(GLuint* buffer, std::vector<glm::vec3> bufferdata) {
	glGenBuffers(1, buffer);
	glBindBuffer(GL_ARRAY_BUFFER, *buffer);
	glBufferData(GL_ARRAY_BUFFER, bufferdata.size() * sizeof(glm::vec3), &bufferdata[0], GL_STATIC_DRAW);
}


