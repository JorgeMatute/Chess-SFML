#include "Game.h"

//Constructor and destructor.
Game::Game() {
	this->initVariables();
	this->initWindow();
}

Game::~Game() {
	delete this->window;
}

//Functions.
const bool Game::running() const {
	return this->window->isOpen();
}

void Game::pollEvents() {
	while (this->window->pollEvent(this->windowEvents)) {
		switch (this->windowEvents.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		}
	}
}

void Game::update() {
	this->pollEvents();
}

void Game::render() {
	this->window->clear();
	
	//Render stuff.
	this->window->draw(this->spriteBoard);

	this->window->display();
}

//Window main functions.
void Game::initWindow() {
	this->videoMode = sf::VideoMode(600, 600);
	this->window = new sf::RenderWindow(this->videoMode, "Ches", sf::Style::Close);
}

void Game::initVariables(){
	this->endGame = false;
	
	//Board sprite texture.
	this->textureBoard.loadFromFile("Images/Board/Board.png");
	this->spriteBoard = sf::Sprite(this->textureBoard, sf::IntRect(0, 0, 1200, 1200));
	this->spriteBoard.setScale(0.5f, 0.5f);

}