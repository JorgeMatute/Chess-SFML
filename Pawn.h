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
	void update();
	void render(sf::RenderTarget& target);

	void move(const float dirX, const float dirY);

private:
	void initTexture();
	void initSprite();

public:
	sf::Texture texturePawn;
	int color;
	int x;
	int y;
	sf::Sprite spritePawn;
	int fistMove = 0;

//Movement functions.
public:
	bool isMoveLegal(int board[][8]);
	int attack(int board[][8]);
};



