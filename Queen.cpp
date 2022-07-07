#include "Queen.h"

//Constructors and destructor.
Queen::Queen() {

}

Queen::Queen(int color, float dirX, float dirY) {
	this->color = color;
	this->initTexture();
	this->initSprite();
	this->spriteQueen.setPosition(sf::Vector2f(dirX, dirY));
}

Queen::~Queen() {

}

void Queen::initTexture() {
	if (this->color == 0)
		this->textureQueen.loadFromFile("Images/WhitePieces/W_Queen.png");
	else
		this->textureQueen.loadFromFile("Images/BlackPieces/B_Queen.png");
}

void Queen::initSprite() {
	//Set the texture to the sprite.
	this->spriteQueen.setTexture(this->textureQueen);

	//Resize the sprite.
	this->spriteQueen.scale(0.5f, 0.5f);
}

void Queen::update() {

}

void Queen::render(sf::RenderTarget& target) {
	target.draw(this->spriteQueen);
}

void Queen::move(const float dirX, const float dirY) {

}
