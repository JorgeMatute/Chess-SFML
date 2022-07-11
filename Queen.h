#pragma once

#include <iostream>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Queen {
public:
	//Constructors and destructor.
	Queen();
	Queen(int color, float dirX, float dirY);
	virtual ~Queen();

	//Functions.
	void update();
	void render(sf::RenderTarget& target);

	void move(const float dirX, const float dirY);

private:
	void initTexture();
	void initSprite();

private:
	sf::Texture textureQueen;
	int color;
public:
	sf::Sprite spriteQueen;
};

