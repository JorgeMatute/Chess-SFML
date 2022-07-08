#include "Bishop.h"

//Constructors and destructor.
Bishop::Bishop() {

}

Bishop::Bishop(int color, float dirX, float dirY) {
	this->color = color;
	this->initTexture();
	this->initSprite();
	this->spriteBishop.setPosition(sf::Vector2f(dirX, dirY));
	this->spriteBishop.setOrigin(75.f, 75.f);
}

Bishop::~Bishop() {

}

void Bishop::initTexture() {
	if (this->color == 0)
		this->textureBishop.loadFromFile("Images/WhitePieces/W_Bishop.png");
	else
		this->textureBishop.loadFromFile("Images/BlackPieces/B_Bishop.png");
}

void Bishop::initSprite() {
	//Set the texture to the sprite.
	this->spriteBishop.setTexture(this->textureBishop);

	//Resize the sprite.
	this->spriteBishop.scale(0.5f, 0.5f);
}

void Bishop::update() {

}

void Bishop::render(sf::RenderTarget& target) {
	target.draw(this->spriteBishop);
}

void Bishop::move(const float dirX, const float dirY) {

}
