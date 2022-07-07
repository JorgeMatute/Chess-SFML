#include "Knight.h"

//Constructors and destructor.
Knight::Knight() {

}

Knight::Knight(int color, float dirX, float dirY) {
	this->color = color;
	this->initTexture();
	this->initSprite();
	this->spriteKnight.setPosition(sf::Vector2f(dirX, dirY));
}

Knight::~Knight() {

}

void Knight::initTexture() {
	if (this->color == 0)
		this->textureKnight.loadFromFile("Images/WhitePieces/W_Knight.png");
	else
		this->textureKnight.loadFromFile("Images/BlackPieces/B_Knight.png");
}

void Knight::initSprite() {
	//Set the texture to the sprite.
	this->spriteKnight.setTexture(this->textureKnight);

	//Resize the sprite.
	this->spriteKnight.scale(0.5f, 0.5f);
}

void Knight::update() {

}

void Knight::render(sf::RenderTarget& target) {
	target.draw(this->spriteKnight);
}

void Knight::move(const float dirX, const float dirY) {

}
