#pragma once

#include "King.h"
#include "Pawn.h"

class Game {
public:
	//Constructor and destructor.
	Game();
	virtual ~Game(); 

	//Functions.
	const bool running() const;
	void pollEvents();

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

	//Pieces.
	King* king_W;
	Pawn* pawn_W[8];

	King* king_B;
	Pawn* pawn_B[8];

	//PRUEBA PRUEBA PRUEBA. BORRAR ESTE 
	//ARRAY PARA VER LO QUE TENGO QUE BORRAR EN EL .CPP 
	//YA QUE SOLO ESTABA PROBANDO PERO YA VI QUE VOY A PODER HACER
	//ESTO PARA LOS PEONES.
	//PARA LAS DEMAS PIEZAS SI VOY A TRABAJAR INDIVIDUAL.


	//All board positions.
	sf::Vector2f board[8][8];
	void setBoardPositions();

};

