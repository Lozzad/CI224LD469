#include "Model.hpp"


void Model::createGameObjects() {
	LightPower = 0.0f;
	SpecLobeMod = 8.0f;
	
	
	//create the stage
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			//create all floors
			createFloor(j * 2, -1 * 2, i * 2);

			switch (wall_positions[i][j]) {
				case 0:
					break;
				case 1: {
					createWall(j * 2, 0, i * 2);
					break;
				case 2:
					createCollectable(j * 2, 0, i * 2);
					break;
				case 3:
					//set player start position
					player_start_pos = glm::vec3(j * 2, 0, i * 2);
					break;
				case 4:
					createEndZone(j * 2, 0, i * 2);
					break;
				case 5:
					//enemy that goes up/down
					createEnemy(j * 2 , -1, i * 2, glm::vec3(0, 0, 0.1) * enemySpeed);
					break;
				case 6:
					//enemy that goes left right
					createEnemy(j * 2, -1, i * 2.5, glm::vec3(0.1, 0, 0) * enemySpeed);
					cout << "enemy placed at" << j * 2 << "," << i * 2 << endl;
					break;
				case 7:
					//secret wall thats actually a floor (i.e. no hitbox)
					createFloor(j * 2, 0, i * 2);
					break;
				default:
					cout << "unknown tile number" << endl;
					break;

				}

			}
			
		}
	}
	//create player
	player = new GameObject();
	player->loadObject("player.obj");
	player->createBoundingBox();
	player->setPosition(player_start_pos);
	player->fillColour(glm::vec3(1, 0, 1));

	currentscore = 0;
	maxscore = collectables.size();
}

void Model::createWall(float x, float y, float z)
{
	GameObject* wall = new GameObject();
	wall->loadObject("box.obj");
	wall->createBoundingBox();
	wall->setPosition(glm::vec3(x, y, z));
	wall->fillColour(glm::vec3(0.4, 0.4, 0.4));
	walls.push_back(wall);
}

void Model::createFloor(float x, float y, float z)
{
	GameObject* floor = new GameObject();
	floor->loadObject("box.obj");
	floor->setPosition(glm::vec3(x, y, z)); 
	floor->fillColour(glm::vec3(0.4, 0.4, 0.4));
	floors.push_back(floor);
}

void Model::createCollectable(float x, float y, float z)
{
	GameObject* coin = new GameObject();
	coin->loadObject("coin.obj");
	coin->createBoundingBox();
	coin->setPosition(glm::vec3(x, y, z));
	coin->fillColour(glm::vec3(1, 0.86, 0));
	collectables.push_back(coin);
}

void Model::createEndZone(float x, float y, float z)
{
	end_zone = new GameObject();
	end_zone->loadObject("box.obj");
	end_zone->setPosition(glm::vec3(x,y,z));
	end_zone->createBoundingBox();
}

void Model::createEnemy(float x, float y, float z, glm::vec3 direction)
{
	Enemy* enemy = new Enemy(direction);
	enemy->loadObject("enemy.obj");
	enemy->createBoundingBox();
	enemy->setPosition(glm::vec3(x, y, z));
	enemy->fillColour(glm::vec3(1, 0, 0));
	enemies.push_back(enemy);
}

Model::Model() {
	playingbool = true;
	createGameObjects();
}
Model::~Model() {

}

GameObject* Model::getPlayer()
{
	return player;
}

std::vector<GameObject*> Model::getWalls()
{
	return walls;
}

std::vector<GameObject*> Model::getFloors()
{
	return floors;
}

std::vector<GameObject*> Model::getCollectables()
{
	return collectables;
}

std::vector<Enemy*> Model::getEnemies()
{
	return enemies;
}

void Model::updatePlayer(glm::vec3 move){
	player->updatePosition(move);
	if (checkCollisions(player, end_zone)) {
		//win game
		cout << "You win" << endl;
		cout << "Final score: " << currentscore << " / " << maxscore << endl;
		playingbool = false;
	}
}

void Model::updateCollectables(){
	for (int i = 0; i < collectables.size(); i++) {
		if (collectables[i]->isAlive()) {
			if (checkCollisions(collectables[i], player)) {
				collectables[i]->setAlive(false);
				LightPower+=0.5;
				if (SpecLobeMod > 1) {
					SpecLobeMod-=0.5;
				}
				//increment player score
				currentscore++;
				cout << currentscore << " / " << maxscore << " collected!" << endl;
			}
			else {
				//rotate or something
			}

		}
	}
}

void Model::updateEnemies()
{
	for (Enemy* enemy : enemies) {
		for (GameObject* wall : walls) {
			if (checkCollisions(enemy, wall)) {
				enemy->reverseDirection();
				break;
			}
		}
		if (checkCollisions(enemy, player)) {
			resetGame();
		}
		enemy->updatePosition(enemy->getDirection());
	}
}

bool Model::checkCollisions(GameObject* a, GameObject* b) {
	
	//tried this but didnt work v well
	if (a->getPosition().x + a->getBoundingBox()->getMax().x >= b->getPosition().x + b->getBoundingBox()->getMin().x		//if max x of a is greater than min x of b
		&& a->getPosition().x + a->getBoundingBox()->getMin().x <= b->getPosition().x + b->getBoundingBox()->getMax().x) 	//and min x of a is less than max x of b
	{
		//if (a->getPosition().y + a->getBoundingBox()->getMax().y >= b->getPosition().y + b->getBoundingBox()->getMin().y		//if max y of a is greater than min y of b
		//	&& a->getPosition().y + a->getBoundingBox()->getMin().y <= b->getPosition().y + b->getBoundingBox()->getMax().y)	//and min y of a is less than max y of b
		//{
			if (a->getPosition().z + a->getBoundingBox()->getMax().z >= b->getPosition().z + b->getBoundingBox()->getMin().z		//if max z of a is greater than min x of b
				&& a->getPosition().z + a->getBoundingBox()->getMin().z <= b->getPosition().z + b->getBoundingBox()->getMax().z)	//and min z of a is less than max x of b
			{
				return true;
			}
		//}
	}
	return false; 
}

bool Model::playerTouchingWall()
{
	for (int i = 0; i < walls.size(); i++) {
		if (checkCollisions(player, walls[i])) {
			return true;
		}
	}
	return false;
}

glm::mat4 Model::ComputeViewMatrix() {
	viewM = glm::lookAt(
		glm::vec3(16, 20, 40),	//camera pos
		player->getPosition(),	//look where?
		glm::vec3(0, 1, 0)		//orientation
	);
	return viewM;
}

float Model::getLightPower()
{
	return LightPower;
}

float Model::getSpecLobeMod()
{
	return SpecLobeMod;
}

void Model::resetGame()
{
	//reset the game
	currentscore = 0;
	cout << "uh oh! score reset :(" << endl;
	LightPower = 0.0f;
	SpecLobeMod = 8.0f;
	player->setPosition(player_start_pos);
	for (GameObject* collectable : collectables) {
		if (!collectable->isAlive()) {
			collectable->setAlive(true);
		}
	}
}

bool Model::isPlaying()
{
	return playingbool;
}
