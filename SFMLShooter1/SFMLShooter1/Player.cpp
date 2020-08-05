#include "Player.h"


//private function

void Player::initTexture()
{
	//Load a texture from file
	if (!this->texture.loadFromFile("Texture/ship.png"))
	{
		std::cout << "ERROR::Player::INITTEXTURE::could not load the texture file" << "\n";
	}
}

void Player::initVariable()
{
	this->movementSpeed = 2.0f;
	this->attackCoolDownMax = 10.0f;
	this->attackCoolDown = this->attackCoolDownMax;
}

void Player::initSprite()
{
	//load a texture to the sprite
	this->sprite.setTexture(this->texture);

	//resize the sprite
	this->sprite.scale(0.1f, 0.1f);
}

//constructor
Player::Player()
{
	this->initVariable();
	this->initTexture();
	this->initSprite();
}

//destructor
Player::~Player()
{
}

//Accessor
const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

//function

void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

const bool Player::canAttack()
{
	if (this->attackCoolDown >= this->attackCoolDownMax)
	{
		this->attackCoolDown = 0.0f;
		return true;
	}

	return false;
}


void Player::updateAttack()
{
	if(this->attackCoolDown<this->attackCoolDownMax)
	this->attackCoolDown += 0.5f;
}

void Player::update()
{
	this->updateAttack();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
