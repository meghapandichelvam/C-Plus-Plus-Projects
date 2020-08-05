#include "Game.h"

void Game::initVariable()
{
	this->endgame = false;
	this->points = 0;
	this->health = 20;
}

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800,800), "Space Shooter", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);

}

void Game::initTexture()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Texture/bullet.png");
}

void Game::initGUI()
{
	//Load font
	if (!this->font.loadFromFile("Fonts/PixellettersFull.ttf"))
		std::cout << "ERROR::GAME::Failed to load the font" << "\n";

	//init point text
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(24);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("test");
}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initEnemies()
{
	this->spawnTimerMax = 50.0f;
	this->spawnTimer = this->spawnTimerMax;
}

Game::Game()
{
	this->initVariable();
	this->initWindow();
	this->initTexture();
	this->initGUI();
	this->initPlayer();
	this->initEnemies();
}

Game::~Game()
{ 
	delete this->window;
	delete this->player;

	//delete  the texture
	for (auto &i : this->textures)
	{
		delete i.second;
	}

	//delete bullets
	for (auto* i : this->bullets)
	{
		delete i;
	}

	//delete enemy
	for (auto* i : this->enemies)
	{
		delete i;
	}
}

//function
void Game::run()
{
	while (this->window->isOpen())
	{
		this->update();
		this->render();
	}
	

}

void Game::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
			this->window->close();

		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
			this->window->close();
	}
}

void Game::updateInput()
{
	//move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->move(-1.0f, 0.0f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->move(1.0f, 0.0f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->player->move(0.0f, -1.0f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->move(0.0f, 1.0f);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack())
	{
		this->bullets.push_back(new Bullet(this->textures["BULLET"],
			this->player->getPos().x+this->player->getBounds().width/2.0f,
			this->player->getPos().y,
			0.0f,
			-1.0f,
			5.0f
		));
	}
}

void Game::updateGUI()
{
	std::stringstream ss;

	ss << "points: " << this->points << "\n" << "health: " << this->health << "\n";

	this->pointText.setString(ss.str());
}

void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();
		//bullet culing (top os screen)
		if (bullet->getBounds().top - bullet->getBounds().height < 0.0f)
		{
			//delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
			std::cout << this->bullets.size() << "\n";

		}
		++counter;
	}
}

void Game::updateEnemiesAndCombat()
{
	this->spawnTimer += 0.5f;

	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->enemies.push_back(new Enemy(rand() % this->window->getSize().x-20.0f, -100.0f));
		this->spawnTimer = 0.0f;
		 
	}
	
	for (int i=0;i<this->enemies.size();i++)
	{
		bool enemey_removed = false;
		this->enemies[i]->update();

		for (size_t k = 0; k < this->bullets.size() && !enemey_removed; k++)
		{
			if (this->bullets[k]->getBounds().intersects(this->enemies[i]->getBounds()))
			{
				this->points += 5.0f;
				this->bullets.erase(this->bullets.begin() + k);
				this->enemies.erase(this->enemies.begin() + i);
				enemey_removed = true;
			}
		}

		//remove enemy at the bottom
		if (!enemey_removed)
		{
			if (this->enemies[i]->getBounds().top > this->window->getSize().y)
			{
				this->health -= 1.0f;
				this->enemies.erase(this->enemies.begin() + i);
				std::cout << this->enemies.size() << "\n";
				enemey_removed = true;
			}
		}
	}
}

void Game::update()
{
	this->updatePollEvents();
	if (this->endgame == false)
	{

		this->updateInput();
		this->player->update();
		this->updateBullets();
		this->updateEnemiesAndCombat();
		this->updateGUI();
	}
	if (this->health <= 0)
	{
		this->endgame = true;
	}
}

void Game::renderGUI()
{
	this->window->draw(this->pointText);
}

void Game::render()
{
	this->window->clear();

	//draw all the stuffs
	this->player->render(*this->window);

	for (auto* bullet : this->bullets)
	{
		bullet->render(this->window);
	}
	  
	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}
	
	this->renderGUI();
	this->window->display();
}
