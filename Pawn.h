#pragma once

#include <iostream>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Pawn {
public:
	//Constructors and destructor.
	Pawn();
	Pawn(int color, float dirX, float dirY, int x, int y);
	virtual ~Pawn();

	//Functions.
	void render(sf::RenderTarget& target);

	//Movement functions.
	void move(const float dirX, const float dirY);
	bool isMoveLegal(int board[][8]);

private:
	void initTexture();
	void initSprite();

private:
	sf::Texture texturePawn;

public:
	int color;
	int x;
	int y;
	int fistMove = 0;
	sf::Sprite spritePawn;
};



