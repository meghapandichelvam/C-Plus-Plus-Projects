#include "Game.h"

//private function
void Game::initVariables()
{
	this->window = nullptr;
	//Gamelogic
	this->endgame = false;
	this->points = 0;
	this->health = 20;
	this->enemeySpawnTimerMax = 20.0f;
	this->enemeySpawnTimer = this->enemeySpawnTimerMax;
	this->maxEnemies = 5;
	this->mouseHeld = false;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "My First Sfml Game", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::initFonts()
{
	//std::cout <<"path: "<< this->font.loadFromFile("$(SolutionDir)/Fonts / Dosis - Light.ttf")<<"\n";
	if (this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		std::cout << "ERROR::GAME::INITFONTS::Failed to load font!" << "\n";
	}
}

void Game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(24);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("NONE");
}

void Game::initEnemies()
{
	this->enemey.setPosition(10.0f,10.0f);
	this->enemey.setSize(sf::Vector2f(100.0f, 100.0f));
	//this->enemey.setScale(sf::Vector2f(0.5f, 0.5f));
	this->enemey.setFillColor(sf::Color::Cyan);
	/*this->enemey.setOutlineColor(sf::Color::Green);
	this->enemey.setOutlineThickness(1.0f);*/


}

//constructor/destructor
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initText(); 
	this->initEnemies();
}
Game::~Game()
{
	delete this->window;
}
 
//Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endgame;
}





//function
void Game::spawnEnemey()
{
	/*
	-retun void
	-spawn enemies and set their type and color. spawn them at random position 
	-set random type
	-set the random position
	-set the random color
	-adds enemy to vector
	*/

	this->enemey.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemey.getSize().x)),
	0.0f
	);

	//randomize enemey type
	int type = rand() % 6;
	switch (type)
	{
	case 0:
		this->enemey.setFillColor(sf::Color::Magenta);
		this->enemey.setSize(sf::Vector2f(20.0f, 20.0f));
		break;
	case 1:
		this->enemey.setFillColor(sf::Color::Blue);
		this->enemey.setSize(sf::Vector2f(30.0f, 30.0f));
		break;
	case 2:
		this->enemey.setFillColor(sf::Color::Cyan);
		this->enemey.setSize(sf::Vector2f(50.0f, 50.0f));
		break;
	case 3:
		this->enemey.setFillColor(sf::Color::Red);
		this->enemey.setSize(sf::Vector2f(70.0f, 70.0f));
		break;
	case 4:
		this->enemey.setFillColor(sf::Color::White);
		this->enemey.setSize(sf::Vector2f(80.0f, 80.0f));
		break;
	case 5:
		this->enemey.setFillColor(sf::Color::Green);
		this->enemey.setSize(sf::Vector2f(110.0f, 110.0f));
		break;
	default:
		this->enemey.setFillColor(sf::Color::Yellow);
		this->enemey.setSize(sf::Vector2f(110.0f, 110.0f));
		break;
	}

	

	//spawn the enemey
	this->enemies.push_back(this->enemey);

	

}
void Game::pollEvents()
{
	//Event polling 
	while (this->window->pollEvent(this->ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}
void Game::UpdateMousePosition()
{
	/*
	 return void
	 -update the mouse position
	 - mouse position relative to window

	*/

	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}
void Game::updateText()
{
	std::stringstream ss;

	ss << "points: " << this->points<<"\n"<<"health: "<<this->health<<"\n";

	this->uiText.setString(ss.str());
}
void Game::updateEnemies()
{
	/* 
	-return void
	-update the enemey spawn timer and spawns enemies
	-when the total amount of enemies is smaller than the maximum
	- moves the enemies downwards
	*/

	//updating the timer for the enemey spawning
	if (this->enemies.size() < this->maxEnemies)
	{
	
		if (this->enemeySpawnTimer >= this->enemeySpawnTimerMax)
		{
			//spawn the enemey and reset the timer
			this->spawnEnemey();
			this->enemeySpawnTimer = 0.0f;
		}
		else
			this->enemeySpawnTimer += 1.0f;
	}

	//move and update the enemies

	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool deleted = false;

		this->enemies[i].move(0.0f, 3.0f);

		//if the enemey is went beyond the bottom of screen
		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			this->health -= 1;
			std::cout << "health: " << this->health<<"\n";
		}
	}
	//check if click upon
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;
			bool deleted = false;
			for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
				{
					

					//gain points
					if(this->enemies[i].getFillColor() == sf::Color::Magenta)
						this->points += 11.0f;
					else if (this->enemies[i].getFillColor() == sf::Color::Blue)
						this->points += 9.0f;
					else if (this->enemies[i].getFillColor() == sf::Color::Cyan)
						this->points += 7.0f;
					else if (this->enemies[i].getFillColor() == sf::Color::Red)
						this->points += 5.0f;
					else if (this->enemies[i].getFillColor() == sf::Color::White)
						this->points += 3.0f;
					else if (this->enemies[i].getFillColor() == sf::Color::Green)
						this->points += 1.0f;


					std::cout << "points: " << this->points<<"\n";

					//delete the enemey
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);
				}

			}
		}
	}
	else
	{
		this->mouseHeld = false;
	}
}
void Game::update()
{
	this->pollEvents();
	if (this->endgame == false)
	{

		this->UpdateMousePosition();

		this->updateText();

		this->updateEnemies();
	}

	//end game condition
	if (this->health <= 0)
	{
		this->endgame = true;
	}
}
void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
}
void Game::renderEnemies(sf::RenderTarget& target)
{
	//render all the enemies
	for (auto& e : this->enemies)
	{
		target.draw(e);
	}
}
void Game::render()
{
	/*
	-return void
	-clear old frame
	-render objects
	- display frame in window
	
	render the game objects*/
	this->window->clear() ;

	//draw game objects
	this->renderEnemies(*this->window);

	this->renderText(*this->window);

	this->window->display();
}
//function