#include "King.h"

King::King() {
	this->initTexture();
	this->initSprite();
}

King::~King() {

}

void King::initTexture() {
	//Load a texture from file.
	this->textureKing.loadFromFile("Images/WhitePieces/W_King.png");
}

void King::initSprite() {
	//Set the texture to the sprite.
	this->spriteKing.setTexture(this->textureKing);

	//Resize the sprite.
	this->spriteKing.scale(0.5f, 0.5f);
}

void King::update() {

}

void King::render(sf::RenderTarget& target) {
	target.draw(this->spriteKing);
}

void King::move(const float dirX, const float dirY) {

}
