#include "Enemy.h"

void Enemy::initShape()
{
	this->shape.setRadius(rand() % 20 + 20);
	this->shape.setPointCount(rand() % 20 + 3);
	this->shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));
}

void Enemy::initVariable()
{
	this->type = 0;
	this->speed = 3.0f;
	this->hpMax = 10;
	this->hp = 0;
	this->damage = 1;
	

}

Enemy::Enemy(float pos_x,float pos_y)
{
	this->initShape();
	this->initVariable();
	this->shape.setPosition(pos_x, pos_y);
	
}

Enemy::~Enemy()
{
}

//Accessor
sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

//function
void Enemy::update()
{
	this->shape.move(0.0f, this->speed);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
