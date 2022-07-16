#include "Game.h"
using namespace std;

//Constructor and destructor.
Game::Game() {
	this->initVariables();
	this->initWindow();
	this->setBoardPositions();
	this->initPieces();
	this->setSquaresPositions();
	this->initSquares();
	this->initSquareBounds();
	this->initBoardPos();
	this->turn = 0; //Pair = white turn.
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
			delete this->squares[row][col];
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

	//Squares (transparents).
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			window->draw(*this->squares[row][col]);
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
	this->window->setFramerateLimit(10);
}

void Game::initVariables() {
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
		this->pawn_W[col] = new Pawn(0, board[col][col].x, board[6][6].y, col, 6);
		this->pawn_B[col] = new Pawn(1, board[col][col].x, board[1][1].y, col, 1);
	}

	//Rooks.
	this->rook1_W = new Rook(0, board[0][0].x, board[7][7].y, 0, 7);
	this->rook2_W = new Rook(0, board[7][7].x, board[7][7].y, 7, 7);
	this->rook1_B = new Rook(1, board[0][0].x, board[0][0].y, 0, 0);
	this->rook2_B = new Rook(1, board[7][7].x, board[0][0].y, 7, 0);

	//Knights.
	this->knight1_W = new Knight(0, board[1][1].x, board[7][7].y);
	this->knight2_W = new Knight(0, board[6][6].x, board[7][7].y);
	this->knight1_B = new Knight(1, board[1][1].x, board[0][0].y);
	this->knight2_B = new Knight(1, board[6][6].x, board[0][0].y);

	//Bishops.
	this->bishop1_W = new Bishop(0, board[2][2].x, board[7][7].y, 2, 7);
	this->bishop2_W = new Bishop(0, board[5][5].x, board[7][7].y, 5, 7);
	this->bishop1_B = new Bishop(1, board[2][2].x, board[0][0].y, 2, 0);
	this->bishop2_B = new Bishop(1, board[5][5].x, board[0][0].y, 5, 0);
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

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

		//Help to exchange values.
		int aux = 0;

		//Old positions.
		int oldXpos;
		int oldYpos;

		// transform the mouse position from window coordinates to world coordinates
		sf::Vector2f mouse = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

		//White pieces (BOUNDS).
		sf::FloatRect boundsPawn_W[8];
		sf::FloatRect boundsKing_W;
		sf::FloatRect boundsQueen_W;
		sf::FloatRect boundsRook1_W;
		sf::FloatRect boundsRook2_W;
		sf::FloatRect boundsKnight1_W;
		sf::FloatRect boundsKnight2_W;
		sf::FloatRect boundsBishop1_W;
		sf::FloatRect boundsBishop2_W;

		//Black pieces (BOUNDS).
		sf::FloatRect boundsPawn_B[8];
		sf::FloatRect boundsKing_B;
		sf::FloatRect boundsQueen_B;
		sf::FloatRect boundsRook1_B;
		sf::FloatRect boundsRook2_B;
		sf::FloatRect boundsKnight1_B;
		sf::FloatRect boundsKnight2_B;
		sf::FloatRect boundsBishop1_B;
		sf::FloatRect boundsBishop2_B;

		//Defining pieces bounds.
		boundsKing_W = this->king_W->spriteKing.getGlobalBounds();
		boundsQueen_W = this->queen_W->spriteQueen.getGlobalBounds();
		boundsRook1_W = this->rook1_W->spriteRook.getGlobalBounds();
		boundsRook2_W = this->rook2_W->spriteRook.getGlobalBounds();
		boundsKnight1_W = this->knight1_W->spriteKnight.getGlobalBounds();
		boundsKnight2_W = this->knight2_W->spriteKnight.getGlobalBounds();
		boundsBishop1_W = this->bishop1_W->spriteBishop.getGlobalBounds();
		boundsBishop2_W = this->bishop2_W->spriteBishop.getGlobalBounds();

		boundsKing_B = this->king_B->spriteKing.getGlobalBounds();
		boundsQueen_B = this->queen_B->spriteQueen.getGlobalBounds();
		boundsRook1_B = this->rook1_B->spriteRook.getGlobalBounds();
		boundsRook2_B = this->rook2_B->spriteRook.getGlobalBounds();
		boundsKnight1_B = this->knight1_B->spriteKnight.getGlobalBounds();
		boundsKnight2_B = this->knight2_B->spriteKnight.getGlobalBounds();
		boundsBishop1_B = this->bishop1_B->spriteBishop.getGlobalBounds();
		boundsBishop2_B = this->bishop2_B->spriteBishop.getGlobalBounds();

		for (int i = 0; i < 8; i++) {
			boundsPawn_W[i] = this->pawn_W[i]->spritePawn.getGlobalBounds();
			boundsPawn_B[i] = this->pawn_B[i]->spritePawn.getGlobalBounds();
		}

		for (int i = 0; i < 8; i++) {
			if (whiteTurn()) { //Coloring the possible moves for each piece (WHITE).
				
				//Pawns.
				if (boundsPawn_W[i].contains(mouse)) {

					//Reset the pawn to move.
					for (int h = 0; h < 8; h++) {
						this->pawnMoves_W[h] = false;
					}

					//ROOK - KNIGHT - BISHOP -> Reset.
					for (int h = 0; h < 2; h++) {
						this->rookMoves_W[h] = false;
						this->bishopMoves_W[h] = false;
						this->knightMoves_W[h] = false;
					}
					this->kingMoves_W = false;
					this->queenMoves_W = false;
					

					if (pawn_W[i]->isMoveLegal(this->boardPos)) {
						initSquares();

						if (this->pawn_W[i]->fistMove == 0 && boardPos[this->pawn_W[i]->x][this->pawn_W[i]->y - 2] == 2) {
							this->squares[this->pawn_W[i]->x][this->pawn_W[i]->y - 1]->setFillColor(sf::Color::Red);
							this->squares[this->pawn_W[i]->x][this->pawn_W[i]->y - 2]->setFillColor(sf::Color::Red);
						}
						else if (boardPos[this->pawn_W[i]->x][this->pawn_W[i]->y - 1] == 2) {
							this->squares[this->pawn_W[i]->x][this->pawn_W[i]->y - 1]->setFillColor(sf::Color::Red);
						}

						//Making sure it doesn't go out range (array boardPos).
						if ((this->pawn_W[i]->x + 1) < 8 && (this->pawn_W[i]->y - 1) < 8) {
							//Possible attack moves.
							if (this->boardPos[this->pawn_W[i]->x + 1][this->pawn_W[i]->y - 1] == 1) {
								this->squares[this->pawn_W[i]->x + 1][this->pawn_W[i]->y - 1]->setFillColor(sf::Color::Red);
							}
						}

						//Making sure it doesn't go out range (array boardPos).
						if ((this->pawn_B[i]->x - 1) >= 0 && (this->pawn_B[i]->y - 1) < 8) {
							//Possible attack moves.
							if (this->boardPos[this->pawn_W[i]->x - 1][this->pawn_W[i]->y - 1] == 1) {
								this->squares[this->pawn_W[i]->x - 1][this->pawn_W[i]->y - 1]->setFillColor(sf::Color::Red);
							}
						}

						this->pawnMoves_W[i] = true;
					}
				}


				//Rook 1.
				if (boundsRook1_W.contains(mouse)) {
					
					//Reset the pawn to move.
					for (int h = 0; h < 8; h++) {
						this->pawnMoves_W[h] = false;
					}

					//ROOK - KNIGHT - BISHOP -> Reset.
					for (int h = 0; h < 2; h++) {
						this->rookMoves_W[h] = false;
						this->bishopMoves_W[h] = false;
						this->knightMoves_W[h] = false;
					}
					this->kingMoves_W = false;
					this->queenMoves_W = false;

					if (this->rook1_W->isMoveLegal(this->boardPos)) {
						initSquares();

						//VERTICAL - UP.
						for (int s = 1; s <= 7; s++) {
							if (this->rook1_W->y - s >= 0) {
								if (boardPos[this->rook1_W->x][this->rook1_W->y - s] == 2) {
									this->squares[this->rook1_W->x][this->rook1_W->y - s]->setFillColor(sf::Color::Red);
								}
								else if (boardPos[this->rook1_W->x][this->rook1_W->y - s] == 1) {
									this->squares[this->rook1_W->x][this->rook1_W->y - s]->setFillColor(sf::Color::Red);
									break;
								}
								else
									break;
							}
						}

						//VERTICAL - DOWN.
						for (int s = 1; s <= 7; s++) {
							if (this->rook1_W->y + s <= 7) {
								if (boardPos[this->rook1_W->x][this->rook1_W->y + s] == 2) {
									this->squares[this->rook1_W->x][this->rook1_W->y + s]->setFillColor(sf::Color::Red);
								}
								else if (boardPos[this->rook1_W->x][this->rook1_W->y + s] == 1) {
									this->squares[this->rook1_W->x][this->rook1_W->y + s]->setFillColor(sf::Color::Red);
									break;
								}
								else
									break;
							}
						}

						//HORIZONTAL - LEFT.
						for (int s = 1; s <= 7; s++) {
							if (this->rook1_W->x - s >= 0) {
								if (boardPos[this->rook1_W->x - s][this->rook1_W->y] == 2) {
									this->squares[this->rook1_W->x - s][this->rook1_W->y]->setFillColor(sf::Color::Red);
								}
								else if (boardPos[this->rook1_W->x - s][this->rook1_W->y] == 1) {
									this->squares[this->rook1_W->x - s][this->rook1_W->y]->setFillColor(sf::Color::Red);
									break;
								}
								else
									break;
							}
						}

						//HORIZONTAL - LEFT.
						for (int s = 1; s <= 7; s++) {
							if (this->rook1_W->x + s <= 7) {
								if (boardPos[this->rook1_W->x + s][this->rook1_W->y] == 2) {
									this->squares[this->rook1_W->x + s][this->rook1_W->y]->setFillColor(sf::Color::Red);
								}
								else if (boardPos[this->rook1_W->x + s][this->rook1_W->y] == 1) {
									this->squares[this->rook1_W->x + s][this->rook1_W->y]->setFillColor(sf::Color::Red);
									break;
								}
								else
									break;
							}
						}

						this->rookMoves_W[0] = true;
					}
				}


				//Rook 2.
				if (boundsRook2_W.contains(mouse)) {

					//Reset the pawn to move.
					for (int h = 0; h < 8; h++) {
						this->pawnMoves_W[h] = false;
					}

					//ROOK - KNIGHT - BISHOP -> Reset.
					for (int h = 0; h < 2; h++) {
						this->rookMoves_W[h] = false;
						this->bishopMoves_W[h] = false;
						this->knightMoves_W[h] = false;
					}
					this->kingMoves_W = false;
					this->queenMoves_W = false;

					if (this->rook2_W->isMoveLegal(this->boardPos)) {
						initSquares();

						//VERTICAL - UP.
						for (int s = 1; s <= 7; s++) {
							if (this->rook2_W->y - s >= 0) {
								if (boardPos[this->rook2_W->x][this->rook2_W->y - s] == 2) {
									this->squares[this->rook2_W->x][this->rook2_W->y - s]->setFillColor(sf::Color::Red);
								}
								else if (boardPos[this->rook2_W->x][this->rook2_W->y - s] == 1) {
									this->squares[this->rook2_W->x][this->rook2_W->y - s]->setFillColor(sf::Color::Red);
									break;
								}
								else
									break;
							}
						}

						//VERTICAL - DOWN.
						for (int s = 1; s <= 7; s++) {
							if (this->rook2_W->y + s <= 7) {
								if (boardPos[this->rook2_W->x][this->rook2_W->y + s] == 2) {
									this->squares[this->rook2_W->x][this->rook2_W->y + s]->setFillColor(sf::Color::Red);
								}
								else if (boardPos[this->rook2_W->x][this->rook2_W->y + s] == 1) {
									this->squares[this->rook2_W->x][this->rook2_W->y + s]->setFillColor(sf::Color::Red);
									break;
								}
								else
									break;
							}
						}

						//HORIZONTAL - LEFT.
						for (int s = 1; s <= 7; s++) {
							if (this->rook2_W->x - s >= 0) {
								if (boardPos[this->rook2_W->x - s][this->rook2_W->y] == 2) {
									this->squares[this->rook2_W->x - s][this->rook2_W->y]->setFillColor(sf::Color::Red);
								}
								else if (boardPos[this->rook2_W->x - s][this->rook2_W->y] == 1) {
									this->squares[this->rook2_W->x - s][this->rook2_W->y]->setFillColor(sf::Color::Red);
									break;
								}
								else
									break;
							}
						}

						//HORIZONTAL - LEFT.
						for (int s = 1; s <= 7; s++) {
							if (this->rook2_W->x + s <= 7) {
								if (boardPos[this->rook2_W->x + s][this->rook2_W->y] == 2) {
									this->squares[this->rook2_W->x + s][this->rook2_W->y]->setFillColor(sf::Color::Red);
								}
								else if (boardPos[this->rook2_W->x + s][this->rook2_W->y] == 1) {
									this->squares[this->rook2_W->x + s][this->rook2_W->y]->setFillColor(sf::Color::Red);
									break;
								}
								else
									break;
							}
						}

						this->rookMoves_W[1] = true;
					}
				}


				//Bishop 1.
				if (boundsBishop1_W.contains(mouse)) {

					//Reset the pawn to move.
					for (int h = 0; h < 8; h++) {
						this->pawnMoves_W[h] = false;
					}

					//ROOK - KNIGHT - BISHOP -> Reset.
					for (int h = 0; h < 2; h++) {
						this->rookMoves_W[h] = false;
						this->bishopMoves_W[h] = false;
						this->knightMoves_W[h] = false;
					}
					this->kingMoves_W = false;
					this->queenMoves_W = false;

					if (this->bishop1_W->isMoveLegal(this->boardPos)) {
						initSquares();

						//LEFT - UP.
						for (int s = 1; s <= 7; s++) {
							if ((this->bishop1_W->x - s >= 0) && (this->bishop1_W->y - s >= 0)) {
								if (boardPos[this->bishop1_W->x - s][this->bishop1_W->y - s] == 2) {
									this->squares[this->bishop1_W->x - s][this->bishop1_W->y - s]->setFillColor(sf::Color::Red);
								}
								else if (boardPos[this->bishop1_W->x - s][this->bishop1_W->y - s] == 1) {
									this->squares[this->bishop1_W->x - s][this->bishop1_W->y - s]->setFillColor(sf::Color::Red);
									break;
								}
								else
									break;
							}
						}

						//LEFT - DOWN.
						for (int s = 1; s <= 7; s++) {
							if ((this->bishop1_W->x - s >= 0) && (this->bishop1_W->y + s <= 7)) {
								if (boardPos[this->bishop1_W->x - s][this->bishop1_W->y + s] == 2) {
									this->squares[this->bishop1_W->x - s][this->bishop1_W->y - s]->setFillColor(sf::Color::Red);
								}
								else if (boardPos[this->bishop1_W->x - s][this->bishop1_W->y + s] == 1) {
									this->squares[this->bishop1_W->x - s][this->bishop1_W->y + s]->setFillColor(sf::Color::Red);
									break;
								}
								else
									break;
							}
						}
						
						//RIGHT - UP.
						for (int s = 1; s <= 7; s++) {
							if ((this->bishop1_W->x + s <= 7) && (this->bishop1_W->y - s >= 0)) {
								if (boardPos[this->bishop1_W->x + s][this->bishop1_W->y - s] == 2) {
									this->squares[this->bishop1_W->x + s][this->bishop1_W->y - s]->setFillColor(sf::Color::Red);
								}
								else if (boardPos[this->bishop1_W->x + s][this->bishop1_W->y - s] == 1) {
									this->squares[this->bishop1_W->x + s][this->bishop1_W->y - s]->setFillColor(sf::Color::Red);
									break;
								}
								else
									break;
							}
						}

						//RIGHT - DOWN.
						for (int s = 1; s <= 7; s++) {
							if ((this->bishop1_W->x + s <= 7) && (this->bishop1_W->y + s <= 7)) {
								if (boardPos[this->bishop1_W->x + s][this->bishop1_W->y + s] == 2) {
									this->squares[this->bishop1_W->x + s][this->bishop1_W->y + s]->setFillColor(sf::Color::Red);
								}
								else if (boardPos[this->bishop1_W->x + s][this->bishop1_W->y + s] == 1) {
									this->squares[this->bishop1_W->x + s][this->bishop1_W->y + s]->setFillColor(sf::Color::Red);
									break;
								}
								else
									break;
							}
						}


						this->bishopMoves_W[0] = false;
					}
				}



			}
			else {  //Coloring the possible moves for each piece (BLACK).

				if (boundsPawn_B[i].contains(mouse)) {

					//Reset the pawn to move.
					for (int h = 0; h < 8; h++) {
						this->pawnMoves_B[h] = false;
					}

					//ROOK - KNIGHT - BISHOP -> Reset.
					for (int h = 0; h < 2; h++) {
						this->rookMoves_B[h] = false;
					}


					if (pawn_B[i]->isMoveLegal(this->boardPos)) {
						initSquares();

						if (this->pawn_B[i]->fistMove == 0 && boardPos[this->pawn_B[i]->x][this->pawn_B[i]->y + 2] == 2) {
							this->squares[this->pawn_B[i]->x][this->pawn_B[i]->y + 1]->setFillColor(sf::Color::Red);
							this->squares[this->pawn_B[i]->x][this->pawn_B[i]->y + 2]->setFillColor(sf::Color::Red);
						}
						else if (boardPos[this->pawn_B[i]->x][this->pawn_B[i]->y + 1] == 2) {
							this->squares[this->pawn_B[i]->x][this->pawn_B[i]->y + 1]->setFillColor(sf::Color::Red);
						}

						//Making sure it doesn't go out range (array boardPos).
						if ((this->pawn_B[i]->x + 1) < 8 && (this->pawn_B[i]->y + 1) < 8) {
							//Possible attack moves.
							if (this->boardPos[this->pawn_B[i]->x + 1][this->pawn_B[i]->y + 1] == 0) {
								this->squares[this->pawn_B[i]->x + 1][this->pawn_B[i]->y + 1]->setFillColor(sf::Color::Red);
							}
						}
						
						//Making sure it doesn't go out range (array boardPos).
						if ((this->pawn_B[i]->x - 1) >= 0 && (this->pawn_B[i]->y + 1) < 8) {
							//Possible attack moves.
							if (this->boardPos[this->pawn_B[i]->x - 1][this->pawn_B[i]->y + 1] == 0) {
								this->squares[this->pawn_B[i]->x - 1][this->pawn_B[i]->y + 1]->setFillColor(sf::Color::Red);
							}
						}

						this->pawnMoves_B[i] = true;
					}
				}

				//Rook 1.
				if (boundsRook1_B.contains(mouse)) {

					//Reset the pawn to move.
					for (int h = 0; h < 8; h++) {
						this->pawnMoves_B[h] = false;
					}

					//ROOK - KNIGHT - BISHOP -> Reset.
					for (int h = 0; h < 2; h++) {
						this->rookMoves_B[h] = false;
					}


					if (this->rook1_B->isMoveLegal(this->boardPos)) {
						initSquares();

						//VERTICAL - UP.
						for (int s = 1; s <= 7; s++) {
							if (this->rook1_B->y - s >= 0) {
								if (boardPos[this->rook1_B->x][this->rook1_B->y - s] == 2) {
									this->squares[this->rook1_B->x][this->rook1_B->y - s]->setFillColor(sf::Color::Red);
								}
								else if (boardPos[this->rook1_B->x][this->rook1_B->y - s] == 0) {
									this->squares[this->rook1_B->x][this->rook1_B->y - s]->setFillColor(sf::Color::Red);
									break;
								}
								else
									break;
							}
						}

						//VERTICAL - DOWN.
						for (int s = 1; s <= 7; s++) {
							if (this->rook1_B->y + s <= 7) {
								if (boardPos[this->rook1_B->x][this->rook1_B->y + s] == 2) {
									this->squares[this->rook1_B->x][this->rook1_B->y + s]->setFillColor(sf::Color::Red);
								}
								else if (boardPos[this->rook1_B->x][this->rook1_B->y + s] == 0) {
									this->squares[this->rook1_B->x][this->rook1_B->y + s]->setFillColor(sf::Color::Red);
									break;
								}
								else
									break;
							}
						}

						//HORIZONTAL - LEFT.
						for (int s = 1; s <= 7; s++) {
							if (this->rook1_B->x - s >= 0) {
								if (boardPos[this->rook1_B->x - s][this->rook1_B->y] == 2) {
									this->squares[this->rook1_B->x - s][this->rook1_B->y]->setFillColor(sf::Color::Red);
								}
								else if (boardPos[this->rook1_B->x - s][this->rook1_B->y] == 0) {
									this->squares[this->rook1_B->x - s][this->rook1_B->y]->setFillColor(sf::Color::Red);
									break;
								}
								else
									break;
							}
						}

						//HORIZONTAL - LEFT.
						for (int s = 1; s <= 7; s++) {
							if (this->rook1_B->x + s <= 7) {
								if (boardPos[this->rook1_B->x + s][this->rook1_B->y] == 2) {
									this->squares[this->rook1_B->x + s][this->rook1_B->y]->setFillColor(sf::Color::Red);
								}
								else if (boardPos[this->rook1_B->x + s][this->rook1_B->y] == 0) {
									this->squares[this->rook1_B->x + s][this->rook1_B->y]->setFillColor(sf::Color::Red);
									break;
								}
								else
									break;
							}
						}

						this->rookMoves_B[0] = true;
					}
				}


				//Rook 2.
				if (boundsRook2_B.contains(mouse)) {

					//Reset the pawn to move.
					for (int h = 0; h < 8; h++) {
						this->pawnMoves_B[h] = false;
					}

					//ROOK - KNIGHT - BISHOP -> Reset.
					for (int h = 0; h < 2; h++) {
						this->rookMoves_B[h] = false;
					}


					if (this->rook2_B->isMoveLegal(this->boardPos)) {
						initSquares();

						//VERTICAL - UP.
						for (int s = 1; s <= 7; s++) {
							if (this->rook2_B->y - s >= 0) {
								if (boardPos[this->rook2_B->x][this->rook2_B->y - s] == 2) {
									this->squares[this->rook2_B->x][this->rook2_B->y - s]->setFillColor(sf::Color::Red);
								}
								else if (boardPos[this->rook2_B->x][this->rook2_B->y - s] == 0) {
									this->squares[this->rook2_B->x][this->rook2_B->y - s]->setFillColor(sf::Color::Red);
									break;
								}
								else
									break;
							}
						}

						//VERTICAL - DOWN.
						for (int s = 1; s <= 7; s++) {
							if (this->rook2_B->y + s <= 7) {
								if (boardPos[this->rook2_B->x][this->rook2_B->y + s] == 2) {
									this->squares[this->rook2_B->x][this->rook2_B->y + s]->setFillColor(sf::Color::Red);
								}
								else if (boardPos[this->rook2_B->x][this->rook2_B->y + s] == 0) {
									this->squares[this->rook2_B->x][this->rook2_B->y + s]->setFillColor(sf::Color::Red);
									break;
								}
								else
									break;
							}
						}

						//HORIZONTAL - LEFT.
						for (int s = 1; s <= 7; s++) {
							if (this->rook2_B->x - s >= 0) {
								if (boardPos[this->rook2_B->x - s][this->rook2_B->y] == 2) {
									this->squares[this->rook2_B->x - s][this->rook2_B->y]->setFillColor(sf::Color::Red);
								}
								else if (boardPos[this->rook2_B->x - s][this->rook2_B->y] == 0) {
									this->squares[this->rook2_B->x - s][this->rook2_B->y]->setFillColor(sf::Color::Red);
									break;
								}
								else
									break;
							}
						}

						//HORIZONTAL - LEFT.
						for (int s = 1; s <= 7; s++) {
							if (this->rook2_B->x + s <= 7) {
								if (boardPos[this->rook2_B->x + s][this->rook2_B->y] == 2) {
									this->squares[this->rook2_B->x + s][this->rook2_B->y]->setFillColor(sf::Color::Red);
								}
								else if (boardPos[this->rook2_B->x + s][this->rook2_B->y] == 0) {
									this->squares[this->rook2_B->x + s][this->rook2_B->y]->setFillColor(sf::Color::Red);
									break;
								}
								else
									break;
							}
						}

						this->rookMoves_B[1] = true;
					}
				}
			}
		}



		//Verify that the square is a possible move to then move the piece.
		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				if (this->boundsSquares[x][y].contains(mouse) && this->squares[x][y]->getFillColor() == sf::Color::Red) {
					for (int i = 0; i < 8; i++) {
						//White pawns.
						if (pawnMoves_W[i]) {

							//Updating the occupied positions.
							aux = this->boardPos[this->pawn_W[i]->x][this->pawn_W[i]->y];
							this->boardPos[this->pawn_W[i]->x][this->pawn_W[i]->y] = this->boardPos[x][y];
							this->boardPos[x][y] = aux;

							//Saving the old white pawn position.
							oldXpos = pawn_W[i]->x;
							oldYpos = pawn_W[i]->y;

							//New white pawn position.
							this->pawn_W[i]->x = x;
							this->pawn_W[i]->y = y;
							this->pawn_W[i]->move(board[x][x].x, board[y][y].y);

							//In case of attack.
							for (int u = 0; u < 8; u++) {
								if ((this->pawn_W[i]->x == this->pawn_B[u]->x) && (this->pawn_W[i]->y == this->pawn_B[u]->y)) {
									this->boardPos[oldXpos][oldYpos] = 2;
									//Removing the attacked piece.
									this->pawn_B[u]->move(-100.0f, -100.0f);
								}
							}
							//Rooks.
							if ((this->pawn_W[i]->x == this->rook1_B->x) && (this->pawn_W[i]->y == this->rook1_B->y)) {
								this->boardPos[oldXpos][oldYpos] = 2;
								this->rook1_B->move(-100.0f, -100.0f);
							}
							else if ((this->pawn_W[i]->x == this->rook2_B->x) && (this->pawn_W[i]->y == this->rook2_B->y)) {
								this->boardPos[oldXpos][oldYpos] = 2;
								this->rook2_B->move(-100.0f, -100.0f);
							}

							//Bishops.



							//Square color reset (transparent).
							initSquares();
							turn++;
							this->pawn_W[i]->fistMove++;
							this->pawnMoves_W[i] = false;
						}

						//Black pawns.
						else if (pawnMoves_B[i]) {

							//Updating the occupied positions.
							aux = this->boardPos[this->pawn_B[i]->x][this->pawn_B[i]->y];
							this->boardPos[this->pawn_B[i]->x][this->pawn_B[i]->y] = this->boardPos[x][y];
							this->boardPos[x][y] = aux;

							//Saving the old white pawn position.
							oldXpos = pawn_B[i]->x;
							oldYpos = pawn_B[i]->y;

							//New pawn position.
							this->pawn_B[i]->x = x;
							this->pawn_B[i]->y = y;
							this->pawn_B[i]->move(board[x][x].x, board[y][y].y);

							//In case of attack.
							for (int u = 0; u < 8; u++) {
								//Pawns.
								if ((this->pawn_B[i]->x == this->pawn_W[u]->x) && (this->pawn_B[i]->y == this->pawn_W[u]->y)) {
									this->boardPos[oldXpos][oldYpos] = 2;
									//Removing the attacked piece.
									this->pawn_W[u]->move(-100.0f, -100.0f);
								}
							}

							//Rooks.
							if ((this->pawn_B[i]->x == this->rook1_W->x) && (this->pawn_B[i]->y == this->rook1_W->y)) {
								this->boardPos[oldXpos][oldYpos] = 2;
								this->rook1_W->move(-100.0f, -100.0f);
							}
							else if ((this->pawn_B[i]->x == this->rook2_W->x) && (this->pawn_B[i]->y == this->rook2_W->y)) {
								this->boardPos[oldXpos][oldYpos] = 2;
								this->rook2_W->move(-100.0f, -100.0f);
							}

							//Bishops.



							//Square color reset (transparent).
							initSquares();
							turn++;
							this->pawn_B[i]->fistMove++;
							this->pawnMoves_B[i] = false;
						}
					}

					//ROOKS 1 (WHITE)
					if (rookMoves_W[0]) {

						//Updating the occupied positions.
						aux = this->boardPos[this->rook1_W->x][this->rook1_W->y];
						this->boardPos[this->rook1_W->x][this->rook1_W->y] = this->boardPos[x][y];
						this->boardPos[x][y] = aux;

						//Saving the old white pawn position.
						oldXpos = this->rook1_W->x;
						oldYpos = this->rook1_W->y;

						//New pawn position.
						this->rook1_W->x = x;
						this->rook1_W->y = y;
						this->rook1_W->move(board[x][x].x, board[y][y].y);


						//In case of attack.
						for (int u = 0; u < 8; u++) {
							//Pawns.
							if ((this->rook1_W->x == this->pawn_B[u]->x) && (this->rook1_W->y == this->pawn_B[u]->y)) {
								this->boardPos[oldXpos][oldYpos] = 2;
								//Removing the attacked piece.
								this->pawn_B[u]->move(-100.0f, -100.0f);
							}
						}

						//Rooks.
						if ((this->rook1_W->x == this->rook1_B->x) && (this->rook1_W->y == this->rook1_B->y)) {
							this->boardPos[oldXpos][oldYpos] = 2;
							this->rook1_B->move(-100.0f, -100.0f);
						}
						else if ((this->rook1_W->x == this->rook2_B->x) && (this->rook1_W->y == this->rook2_B->y)) {
							this->boardPos[oldXpos][oldYpos] = 2;
							this->rook2_B->move(-100.0f, -100.0f);
						}

						//Bishops.



						//Square color reset (transparent).
						initSquares();
						turn++;
						this->rookMoves_W[0] = false;
					}

					//Rook 2 (WHITE)
					if (rookMoves_W[1]) {

						//Updating the occupied positions.
						aux = this->boardPos[this->rook2_W->x][this->rook2_W->y];
						this->boardPos[this->rook2_W->x][this->rook2_W->y] = this->boardPos[x][y];
						this->boardPos[x][y] = aux;

						//Saving the old white pawn position.
						oldXpos = this->rook2_W->x;
						oldYpos = this->rook2_W->y;

						//New pawn position.
						this->rook2_W->x = x;
						this->rook2_W->y = y;
						this->rook2_W->move(board[x][x].x, board[y][y].y);


						//In case of attack.
						for (int u = 0; u < 8; u++) {
							//Pawns.
							if ((this->rook2_W->x == this->pawn_B[u]->x) && (this->rook2_W->y == this->pawn_B[u]->y)) {
								this->boardPos[oldXpos][oldYpos] = 2;
								//Removing the attacked piece.
								this->pawn_B[u]->move(-100.0f, -100.0f);
							}
						}

						//Rooks.
						if ((this->rook2_W->x == this->rook1_B->x) && (this->rook2_W->y == this->rook1_B->y)) {
							this->boardPos[oldXpos][oldYpos] = 2;
							this->rook1_B->move(-100.0f, -100.0f);
						}
						else if ((this->rook2_W->x == this->rook2_B->x) && (this->rook2_W->y == this->rook2_B->y)) {
							this->boardPos[oldXpos][oldYpos] = 2;
							this->rook2_B->move(-100.0f, -100.0f);
						}

						//Bishops.


						//Square color reset (transparent).
						initSquares();
						turn++;
						this->rookMoves_W[1] = false;
					}


					//ROOKS 1 (BLACK)
					if (rookMoves_B[0]) {

						//Updating the occupied positions.
						aux = this->boardPos[this->rook1_B->x][this->rook1_B->y];
						this->boardPos[this->rook1_B->x][this->rook1_B->y] = this->boardPos[x][y];
						this->boardPos[x][y] = aux;

						//Saving the old white pawn position.
						oldXpos = this->rook1_B->x;
						oldYpos = this->rook1_B->y;

						//New pawn position.
						this->rook1_B->x = x;
						this->rook1_B->y = y;
						this->rook1_B->move(board[x][x].x, board[y][y].y);


						//In case of attack.
						for (int u = 0; u < 8; u++) {
							//Pawns.
							if ((this->rook1_B->x == this->pawn_W[u]->x) && (this->rook1_B->y == this->pawn_W[u]->y)) {
								this->boardPos[oldXpos][oldYpos] = 2;
								//Removing the attacked piece.
								this->pawn_W[u]->move(-100.0f, -100.0f);
							}
						}

						//Rooks.
						if ((this->rook1_B->x == this->rook1_W->x) && (this->rook1_B->y == this->rook1_W->y)) {
							this->boardPos[oldXpos][oldYpos] = 2;
							this->rook1_W->move(-100.0f, -100.0f);
						}
						else if ((this->rook1_B->x == this->rook2_W->x) && (this->rook1_B->y == this->rook2_W->y)) {
							this->boardPos[oldXpos][oldYpos] = 2;
							this->rook2_W->move(-100.0f, -100.0f);
						}

						//Bishops.



						//Square color reset (transparent).
						initSquares();
						turn++;
						this->rookMoves_B[0] = false;
					}

					//Rook 2 (BLACK)
					if (rookMoves_B[1]) {

						//Updating the occupied positions.
						aux = this->boardPos[this->rook2_B->x][this->rook2_B->y];
						this->boardPos[this->rook2_B->x][this->rook2_B->y] = this->boardPos[x][y];
						this->boardPos[x][y] = aux;

						//Saving the old white pawn position.
						oldXpos = this->rook2_B->x;
						oldYpos = this->rook2_B->y;

						//New pawn position.
						this->rook2_B->x = x;
						this->rook2_B->y = y;
						this->rook2_B->move(board[x][x].x, board[y][y].y);


						//In case of attack.
						for (int u = 0; u < 8; u++) {
							//Pawns.
							if ((this->rook2_B->x == this->pawn_W[u]->x) && (this->rook2_B->y == this->pawn_W[u]->y)) {
								this->boardPos[oldXpos][oldYpos] = 2;
								//Removing the attacked piece.
								this->pawn_W[u]->move(-100.0f, -100.0f);
							}
						}

						//Rooks.
						if ((this->rook2_B->x == this->rook1_W->x) && (this->rook2_B->y == this->rook1_W->y)) {
							this->boardPos[oldXpos][oldYpos] = 2;
							this->rook1_W->move(-100.0f, -100.0f);
						}
						else if ((this->rook2_B->x == this->rook2_W->x) && (this->rook2_B->y == this->rook2_W->y)) {
							this->boardPos[oldXpos][oldYpos] = 2;
							this->rook2_W->move(-100.0f, -100.0f);
						}

						//Bishops.


						//Square color reset (transparent).
						initSquares();
						turn++;
						this->rookMoves_B[1] = false;
					}
					

				}
			}
		}
	}
}


void Game::setSquaresPositions() {
	float y = 37.5;
	float x = 37.5;

	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			sf::Vector2f newVector(x, y);
			this->squarePositions[col][row] = newVector; //row-col.
			y += 75.0;
		}
		y = 37.5;
		x += 75.0;
	}
}

void Game::initSquares() {

	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			this->squares[row][col] = new sf::RectangleShape(sf::Vector2f(75.0f, 75.0f));
			this->squares[row][col]->setFillColor(sf::Color::Transparent);
			this->squares[row][col]->setOutlineColor(sf::Color::Black);
			this->squares[row][col]->setOutlineThickness(0.5);
			this->squares[row][col]->setOrigin(37.5f, 37.5f);
			this->squares[row][col]->setPosition(squarePositions[col][row]);
		}
	}
}

void Game::initBoardPos() {
	//Occupied squares.

	//White.
	for (int x = 0; x < 8; x++) {
		for (int y = 6; y < 8; y++) {
			boardPos[x][y] = 0; //White .
		}
	}

	//Black.
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 2; y++) {
			boardPos[x][y] = 1; //Black.
		}
	}

	//Unoccupied squares.
	for (int x = 0; x < 8; x++) {
		for (int y = 2; y < 6; y++) {
			boardPos[x][y] = 2; //2 -> empty.
		}
	}
}


//TESTING FUNCTION.
void Game::printOccupiedAndNonOcuppiedPositions() {
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			cout << "[" << boardPos[y][x] << "]";
		}
		cout << endl;
	}

	cout << endl;
}

//

bool Game::whiteTurn() {
	return (this->turn % 2) == 0;
}

void Game::initSquareBounds() {
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			this->boundsSquares[x][y] = this->squares[x][y]->getGlobalBounds();
		}
	}
}
