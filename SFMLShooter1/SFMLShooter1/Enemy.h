#ifndef ENEMY_H
#define ENEMY_H

#include<SFML/Graphics.hpp>


class Enemy
{
private:
	sf::CircleShape shape;

	int type;
	float speed;
	int hp;
	int hpMax;
	int damage;

	void initShape();
	void initVariable();

public:
	Enemy(float pos_x, float pos_y);
	virtual ~Enemy();

	//Accessor
	sf::FloatRect getBounds() const;

	//function
	void update();
	void render(sf::RenderTarget* target);
};
#endif // !ENEMY_H

