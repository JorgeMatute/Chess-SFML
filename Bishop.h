#pragma once

#include <iostream>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Bishop {
public:
	//Constructors and destructor.
	Bishop();
	Bishop(int color, float dirX, float dirY);
	virtual ~Bishop();

	//Functions.
	void update();
	void render(sf::RenderTarget& target);

	void move(const float dirX, const float dirY);

private:
	void initTexture();
	void initSprite();

private:
	sf::Texture textureBishop;
	sf::Sprite spriteBishop;
	int color;
};

