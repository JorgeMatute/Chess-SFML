#pragma once

#include "King.h"

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

	//Pieces.
	King* king_W;

	//Pieces inits.
	void initKing();

};

