#pragma once

#include "King.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"

class Game {
public:
	//Constructor and destructor.
	Game();
	virtual ~Game(); 

	//Functions.
	const bool running() const;
	void pollEvents();
	void movements();

	void update();
	void render();

private:

	//General private attributes.
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	bool endGame;
	sf::Event windowEvents;

	//Board.
	sf::Texture textureBoard;
	sf::Sprite spriteBoard;


	//Init functions.
	void initWindow();
	void initVariables();
	void initBackground();
	void initPieces();
	void initSquares();
	void initSquareBounds();

	//Pieces.
	King* king_W;
	Queen* queen_W;
	Pawn* pawn_W[8];
	Rook* rook1_W;
	Rook* rook2_W;
	Knight* knight1_W;
	Knight* knight2_W;
	Bishop* bishop1_W;
	Bishop* bishop2_W;

	King* king_B;
	Queen* queen_B;
	Pawn* pawn_B[8];
	Rook* rook1_B;
	Rook* rook2_B;
	Knight* knight1_B;
	Knight* knight2_B;
	Bishop* bishop1_B;
	Bishop* bishop2_B;

	//Square shapes to determine the valid moves.
	sf::RectangleShape* squares[8][8];

	//All board positions.
	sf::Vector2f board[8][8];
	sf::Vector2f squarePositions[8][8];
	sf::FloatRect boundsSquares[8][8];
	void setBoardPositions();
	void setSquaresPositions();

	//Board indicating occupied and unoccupied positions.
	void initBoardPos();
	int boardPos[8][8]; 

	//Turns.
	bool whiteTurn();
	int turn;
	bool pawnMoves_W[8]; //Al coronar, el bool pasaria a esa nueva piece.

	bool pawnMoves_B[8];

	//prueba.
	void printOccupiedAndNonOcuppiedPositions();
	//

};

