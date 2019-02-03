#include "Controller.h"

Controller::Controller(View* myview, Model* mymodel)
{
	view = myview;
	model = mymodel;
	count = 0;
}

Controller::~Controller()
{
}

void Controller::loop() {
	do {
		if (model->isPlaying()) {
			if (glfwGetKey(view->getWindow(), GLFW_KEY_UP) == GLFW_PRESS) {
				model->updatePlayer(glm::vec3(0, 0, -speed));
				if (model->playerTouchingWall()) {
					model->updatePlayer(glm::vec3(0, 0, speed));
				}
			}

			if (glfwGetKey(view->getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
				model->updatePlayer(glm::vec3(speed, 0, 0));
				if (model->playerTouchingWall()) {
					model->updatePlayer(glm::vec3(-speed, 0, 0));
				}
			}
			if (glfwGetKey(view->getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS) {
				model->updatePlayer(glm::vec3(-speed, 0, 0));
				if (model->playerTouchingWall()) {
					model->updatePlayer(glm::vec3(speed, 0, 0));
				}
			}
			if (glfwGetKey(view->getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS) {
				model->updatePlayer(glm::vec3(0, 0, speed));
				if (model->playerTouchingWall()) {
					model->updatePlayer(glm::vec3(0, 0, -speed));
				}
			}
			model->updateCollectables();
			model->updateEnemies(enemySpeed);
			
		}
		view->update();
	} while (glfwGetKey(view->getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(view->getWindow()) == 0);
}