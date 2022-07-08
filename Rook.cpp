#include "Rook.h"

//Constructors and destructor.
Rook::Rook() {

}

Rook::Rook(int color, float dirX, float dirY) {
	this->color = color;
	this->initTexture();
	this->initSprite();
	this->spriteRook.setPosition(sf::Vector2f(dirX, dirY));
	this->spriteRook.setOrigin(75.f, 75.f);
}

Rook::~Rook() {

}

void Rook::initTexture() {
	if (this->color == 0)
		this->textureRook.loadFromFile("Images/WhitePieces/W_Rook.png");
	else
		this->textureRook.loadFromFile("Images/BlackPieces/B_Rook.png");
}

void Rook::initSprite() {
	//Set the texture to the sprite.
	this->spriteRook.setTexture(this->textureRook);

	//Resize the sprite.
	this->spriteRook.scale(0.5f, 0.5f);
}

void Rook::update() {

}

void Rook::render(sf::RenderTarget& target) {
	target.draw(this->spriteRook);
}

void Rook::move(const float dirX, const float dirY) {

}
