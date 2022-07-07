#include "Game.h"

//Constructor and destructor.
Game::Game() {
	this->initWindow();
	this->initVariables();
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
	this->window->display();
}

//Window main functions.
void Game::initWindow() {
	this->videoMode = sf::VideoMode(600, 600);
	this->window = new sf::RenderWindow(this->videoMode, "Ches", sf::Style::Close);
}

void Game::initVariables(){
	this->endGame = false;
}