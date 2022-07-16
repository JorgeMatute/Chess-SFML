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
	Pawn* pawn_W[8];
	Rook* rook_W[2];
	Knight* knight_W[2];
	Bishop* bishop_W[2];
	King* king_W;
	Queen* queen_W;

	Pawn* pawn_B[8];
	Rook* rook_B[2];
	Knight* knight_B[2];
	Bishop* bishop_B[2];
	King* king_B;
	Queen* queen_B;

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

	bool pawnMoves_W[8]; 
	bool rookMoves_W[2];
	bool knightMoves_W[2];
	bool bishopMoves_W[2];
	bool kingMoves_W;
	bool queenMoves_W;

	bool pawnMoves_B[8];
	bool rookMoves_B[2];
	bool knightMoves_B[2];
	bool bishopMoves_B[2];
	bool kingMoves_B;
	bool queenMoves_B;

	//TESTING FUNCTION.
	void printOccupiedAndNonOcuppiedPositions();
	//

};

