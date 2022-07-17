#pragma once

#include <iostream>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class King {
public:
	//Constructors and destructor.
	King();
	King(int color, float dirX, float dirY, int x, int y);
	virtual ~King();
	
	//Functions.
	void render(sf::RenderTarget& target);

	void move(const float dirX, const float dirY);
	bool isMoveLegal(int board[][8]);

private:
	void initTexture();
	void initSprite();

private:
	sf::Texture textureKing;

public:
	int color;
	int x;
	int y;
	sf::Sprite spriteKing;
};

