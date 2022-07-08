#include "Game.h"

//Constructor and destructor.
Game::Game() {
	this->initVariables();
	this->initWindow();
	this->setBoardPositions();
	this->setCirclesPositions();
	this->initPieces();
	this->initCircles();
}

Game::~Game() { //Avoiding memory leaks.
	//Delete window.
	delete this->window;

	//Delete pieces.

	//Kings.
	delete this->king_W;
	delete this->king_B;

	//Queens.
	delete this->queen_W;
	delete this->queen_B;

	//Pawns.
	for (int i = 0; i < 8; i++) {
		delete pawn_W[i];
	}

	//Rooks.
	delete this->rook1_W;
	delete this->rook2_W;
	delete this->rook1_B;
	delete this->rook2_B;

	//Knights.
	delete this->knight1_W;
	delete this->knight2_W;
	delete this->knight1_B;
	delete this->knight2_B;

	//Bishops.
	delete this->bishop1_W;
	delete this->bishop2_W;
	delete this->bishop1_B;
	delete this->bishop2_B;

	//Squares.
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			delete this->circles[row][col];
		}
	}
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

	//Pieces movements.
	movements();
}

void Game::update() {
	this->pollEvents();
}

void Game::render() {
	this->window->clear();
	
	//Render stuff.
	this->window->draw(this->spriteBoard);
	this->initBackground();

	//Circles.
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			window->draw(*this->circles[row][col]);
			//this->circles[row][col]->setFillColor(sf::Color::Transparent);
			//this->circles[row][col]->remove
		}
	}

	//Pieces.

	//Kings.
	this->king_W->render(*this->window);
	this->king_B->render(*this->window);
	
	//Queens.
	this->queen_W->render(*this->window);
	this->queen_B->render(*this->window);

	//Pawns.
	for (int i = 0; i < 8; i++) {
		this->pawn_W[i]->render(*this->window);
		this->pawn_B[i]->render(*this->window);
	}

	//Rooks.
	this->rook1_W->render(*this->window);
	this->rook2_W->render(*this->window);
	this->rook1_B->render(*this->window);
	this->rook2_B->render(*this->window);

	//Knights.
	this->knight1_W->render(*this->window);
	this->knight2_W->render(*this->window);
	this->knight1_B->render(*this->window);
	this->knight2_B->render(*this->window);

	//Bishops.
	this->bishop1_W->render(*this->window);
	this->bishop2_W->render(*this->window);
	this->bishop1_B->render(*this->window);
	this->bishop2_B->render(*this->window);






	this->window->display();
}

//Game init functions.
void Game::initWindow() {
	this->videoMode = sf::VideoMode(600, 600);
	this->window = new sf::RenderWindow(this->videoMode, "Chess", sf::Style::Close);
	this->window->setVerticalSyncEnabled(false);
	this->window->setFramerateLimit(140);
}

void Game::initVariables(){
	this->endGame = false;

}

void Game::initPieces() {

	//Kings.
	this->king_W = new King(0, board[4][4].x, board[7][7].y);
	this->king_B = new King(1, board[4][4].x, board[0][0].y);

	//Queens.
	this->queen_W = new Queen(0, board[3][3].x, board[7][7].y);
	this->queen_B = new Queen(1, board[3][3].x, board[0][0].y);

	//Pawns.
	for (int col = 0; col < 8; col++) {
		this->pawn_W[col] = new Pawn(0, board[col][col].x, board[6][6].y);
		this->pawn_B[col] = new Pawn(1, board[col][col].x, board[1][1].y);
	}

	//Rooks.
	this->rook1_W = new Rook(0, board[0][0].x, board[7][7].y);
	this->rook2_W = new Rook(0, board[7][7].x, board[7][7].y);
	this->rook1_B = new Rook(1, board[0][0].x, board[0][0].y);
	this->rook2_B = new Rook(1, board[7][7].x, board[0][0].y);

	//Knights.
	this->knight1_W = new Knight(0, board[1][1].x, board[7][7].y);
	this->knight2_W = new Knight(0, board[6][6].x, board[7][7].y);
	this->knight1_B = new Knight(1, board[1][1].x, board[0][0].y);
	this->knight2_B = new Knight(1, board[6][6].x, board[0][0].y);

	//Bishops.
	this->bishop1_W = new Bishop(0, board[2][2].x, board[7][7].y);
	this->bishop2_W = new Bishop(0, board[5][5].x, board[7][7].y);
	this->bishop1_B = new Bishop(1, board[2][2].x, board[0][0].y);
	this->bishop2_B = new Bishop(1, board[5][5].x, board[0][0].y);
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
	float y = 37.5;
	float x = 37.5;

	//Each square size: (75.0 x 75.0)
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			sf::Vector2f nuevoVector(x, y);
			this->board[row][col] = nuevoVector;
			if (col == 0)
				y += 37.5;
			else
				y += 75.0;
		}
		y = 75.0;
		x += 75.0;
	}
}

void Game::movements() {
	//Movements.
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

		// transform the mouse position from window coordinates to world coordinates
		sf::Vector2f mouse = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

		// retrieve the bounding box of the sprite
		sf::FloatRect bounds = this->pawn_W[0]->spritePawn.getGlobalBounds();


		if (bounds.contains(mouse)) {
			std::cout << "hola" << std::endl;

			//Aqui irian entonces las acciones o events.
		}

		//Con un loop podría añadir 64 shapes en las 64 posiciones que tengo de board.
		//de esa forma puedo recrear el tablero y ponerlos de rojo.
		//Asi si cuando toque una pieza que se pongan en rojo los disponibles y si
		//toca esa shape, que se mueva a las coordenadas de esa shape.
	}
}

void Game::setCirclesPositions() {
	float y = 37.5;
	float x = 37.5;

	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			sf::Vector2f nuevoVector(x, y);
			this->circlePositions[row][col] = nuevoVector;
			y += 75.0;
		}
		y = 37.5;
		x += 75.0;
	}
}

void Game::initCircles() {

	//Circles texture of possible moves.
	if (!this->textureCircles.loadFromFile("Images/Board/Circle.png")) {
		std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
	}

	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			this->circles[row][col] = new sf::RectangleShape(sf::Vector2f(75.0f, 75.0f));
			//this->circles[row][col]->setTexture(&this->textureCircles);
			this->circles[row][col]->setFillColor(sf::Color::Red);
			this->circles[row][col]->setOutlineColor(sf::Color::Black);
			this->circles[row][col]->setOutlineThickness(0.5);
			this->circles[row][col]->setOrigin(37.5f, 37.5f);
			this->circles[row][col]->setPosition(circlePositions[col][row]);
		}
	}
}