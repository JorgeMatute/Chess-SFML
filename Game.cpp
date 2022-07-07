#include "Game.h"

//Constructor and destructor.
Game::Game() {
	this->initVariables();
	this->initWindow();
	this->setBoardPositions();
	this->initPieces();
}

Game::~Game() { //Avoiding memory leaks.
	//Delete window.
	delete this->window;

	//Delete pieces.
	delete this->king_W;
	delete this->king_B;

	//
	delete pawn_W[0];
	//
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

	//Move pieces.
}

void Game::update() {
	this->pollEvents();
}

void Game::render() {
	this->window->clear();
	
	//Render stuff.
	this->window->draw(this->spriteBoard);
	this->initBackground();

	//Pieces.
	this->king_W->render(*this->window);
	this->king_B->render(*this->window);
	//
	this->pawn_W[0]->render(*this->window);
	//


	this->window->display();
}

//Game init functions.
void Game::initWindow() {
	this->videoMode = sf::VideoMode(600, 600);
	this->window = new sf::RenderWindow(this->videoMode, "Chess", sf::Style::Close);
	this->window->setVerticalSyncEnabled(false);
	this->window->setFramerateLimit(60);
}

void Game::initVariables(){
	this->endGame = false;

}

void Game::initPieces() {
	this->king_W = new King(0, board[4][4].x, board[7][7].y);
	this->king_B = new King(1, board[4][4].x, board[0][0].y);

	//
	this->pawn_W[0] = new King(1, board[4][4].x, board[4][4].y);
	//
}

void Game::initBackground() {
	if (!this->textureBoard.loadFromFile("Images/Board/Board.png")) {
		std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
	}
	this->spriteBoard = sf::Sprite(this->textureBoard, sf::IntRect(0, 0, 1200, 1200));
	this->spriteBoard.setScale(0.5f, 0.5f);
}

//Defines the position of each square on the board.
void Game::setBoardPositions() {
	float y = 0.0;
	float x = 0.0;

	//Each square size: (75.0 x 75.0)
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			sf::Vector2f nuevoVector(x, y);
			this->board[row][col] = nuevoVector;
			y += 75.0;
		}
		y = 0.0;
		x += 75.0;
	}
}
