#pragma once
// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
#include <vector>

#include "Model.hpp"
#include <cmath>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "GameObject.hpp"
#include "Enemy.hpp"

class Model {
private:
	GameObject* player;
	glm::vec3 player_start_pos;

	int currentscore;
	int maxscore;

	float enemySpeed = 0.1f;

	//0 = floor, 1 = wall, 2 = collectable
	//3 = player start loc, 4 = end loc
	//5 = enemy (move up and down)
	//6 = enemy (move left and right)
	//7 = fake wall
	int wall_positions[16][16] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 1},
		{1, 2, 0, 0, 6, 1, 0, 0, 6, 0, 0, 2, 1, 0, 1, 1},
		{1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1},
		{1, 1, 0, 1, 0, 1, 0, 1, 1, 2, 1, 0, 1, 1, 0, 1},
		{1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 4},
		{1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1},
		{1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 2, 1},
		{1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1},
		{1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1},
		{1, 2, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 2, 1, 0, 1},
		{1, 0, 1, 0, 1, 1, 1, 1, 1, 2, 1, 0, 1, 1, 0, 1},
		{1, 0, 1, 0, 1, 2, 0, 2, 1, 7, 1, 0, 1, 1, 0, 1},
		{1, 0, 1, 0, 1, 0, 2, 0, 1, 0, 1, 0, 1, 1, 0, 1},
		{1, 3, 1, 2, 1, 2, 0, 2, 0, 0, 1, 5, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};

	std::vector<GameObject*> walls;
	std::vector<GameObject*> floors;
	std::vector<GameObject*> collectables;
	std::vector<Enemy*> enemies;
	GameObject* end_zone;

	float LightPower;
	float SpecLobeMod;

	glm::mat4 viewM;

	void Model::createGameObjects();
	void Model::createWall(float x, float y, float z);
	void Model::createFloor(float x, float y, float z);
	void Model::createCollectable(float x, float y, float z);
	void Model::createEndZone(float x, float y, float z);
	void Model::createEnemy(float x, float y, float z, glm::vec3 direction);

	bool playingbool;

public:
	Model();
	~Model();
	//getters n setters
	GameObject* getPlayer();
	std::vector<GameObject*> getWalls();
	std::vector<GameObject*> getFloors();
	std::vector<GameObject*> getCollectables();
	std::vector<Enemy*> getEnemies();
	void updatePlayer(glm::vec3 move);
	void updateCollectables();
	void updateEnemies();
	bool checkCollisions(GameObject * a, GameObject * b);
	bool playerTouchingWall();

	glm::mat4 ComputeViewMatrix();
	float getLightPower();
	float getSpecLobeMod();
	void resetGame();
	bool isPlaying();
};

