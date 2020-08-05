#pragma once

#include<map>
#include<ctime>
#include<sstream>

#include"Player.h"
#include"Bullet.h"
#include"Enemy.h"

class Game
{
private:
	//window
	sf::RenderWindow* window;

	//Resources
	std::map<sf::String, sf::Texture*> textures;
	std::vector<Bullet*> bullets;

	//GUI
	sf::Font font;
	sf::Text pointText;

	//player
	Player* player;

	//Enemy
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;
	
	//game logic
	bool endgame;
	unsigned points;
	int health;
	
	//private fuction
	void initVariable();
	void initWindow();
	void initTexture();
	void initGUI();

	void initPlayer();
	void initEnemies();

public:
	Game();
	virtual ~Game();

	//function
	void run();

	void updatePollEvents();
	void updateInput();
	void updateGUI();

	void updateBullets();
	void updateEnemiesAndCombat();
	void update();
	void renderGUI();

	void render();
};

 