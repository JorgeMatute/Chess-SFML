#pragma once

#include <iostream>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

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

	void initWindow();
	void initVariables();

};

