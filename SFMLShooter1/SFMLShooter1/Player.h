#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>

#include<iostream>

class Player
{

private:
	sf::Sprite sprite;
	sf::Texture texture;

	float movementSpeed;

	float attackCoolDown;
	float attackCoolDownMax;


	//private function
	void initVariable();
	void initSprite();
	void initTexture();


public:

	//constructor
	Player();
	 
	//destructor
	virtual ~Player();

	//Accessor
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds()const;
	//function
	void move(const float dirX, const float dirY);
	const bool canAttack();

	void updateAttack();
	void update();
	void render(sf::RenderTarget& target); 
};

