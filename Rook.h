#pragma once

#include <iostream>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Rook {
public:
	//Constructors and destructor.
	Rook();
	Rook(int color, float dirX, float dirY, int x, int y);
	virtual ~Rook();

	//Functions.
	void render(sf::RenderTarget& target);

	void move(const float dirX, const float dirY);
	bool isMoveLegal(int board[][8]);

private:
	void initTexture();
	void initSprite();

private:
	sf::Texture textureRook;

public:
	int color;
	int x;
	int y;
	int firstMove = 0;
	sf::Sprite spriteRook;
};

