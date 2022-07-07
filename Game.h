#pragma once
#include "Pawn.h"

class Game {
public:
	//Constructor and destructor.
	Game();
	~Game();

	//Accessors.

	//Modifiers.

	//Functions.
	const bool running() const;
	void pollEvents();

	void update();
	void render();

private:
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	bool endGame;
	sf::Event windowEvents;
	sf::Texture textureBoard;
	sf::Sprite spriteBoard;


	void initWindow();
	void initVariables();

};

