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
	Queen(int color, float dirX, float dirY, int x, int y);
	virtual ~Queen();

	//Functions.
	void render(sf::RenderTarget& target);

	void move(const float dirX, const float dirY);
	bool isMoveLegal(int board[][8]);

private:
	void initTexture();
	void initSprite();

private:
	sf::Texture textureQueen;

public:
	int color;
	int x;
	int y;
	sf::Sprite spriteQueen;
};

