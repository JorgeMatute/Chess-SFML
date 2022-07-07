#include "King.h"

//Constructors and destructor.
King::King() {

}

King::King(int color, float dirX, float dirY) {
	this->color = color;
	this->initTexture();
	this->initSprite();
	this->spriteKing.setPosition(sf::Vector2f(dirX, dirY));
}

King::~King() {

}

void King::initTexture() {
	if(this->color == 0)
		this->textureKing.loadFromFile("Images/WhitePieces/W_King.png");
	else
		this->textureKing.loadFromFile("Images/BlackPieces/B_King.png");
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
