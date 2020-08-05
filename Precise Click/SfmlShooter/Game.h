#pragma once
#include<iostream>
#include<vector>
#include<ctime>
#include<sstream>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include <SFML/Network.hpp>

//class that act as the game engine
//wrapper class
class Game
{
private:
	//variables
	//window
	sf::RenderWindow* window; 
	sf::VideoMode videoMode;
	sf::Event ev;

	//mouse position
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Resources
	sf::Font font;

	//Text
	sf::Text uiText;

	//Game logic
	bool endgame;
	unsigned points;
	int health;
	float enemeySpawnTimer;
	float enemeySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;

	//Game Objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemey;


	//Private function
	void initVariables();
	void initWindow();
	void initFonts();
	void initText();
	void initEnemies();


public:
	//constructor/destructor
	Game();
	virtual ~Game();

	//Accessors
	const bool running()const;
	const bool getEndGame()const;
	//function
	void spawnEnemey();

	void pollEvents();
	void UpdateMousePosition();
	void updateText();
	void updateEnemies();
	void update();

	void renderText(sf::RenderTarget& target);
	void renderEnemies(sf::RenderTarget& target);
	void render();
};

