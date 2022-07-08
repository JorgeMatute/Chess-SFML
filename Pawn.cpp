#include "Pawn.h"

//Constructors and destructor.
Pawn::Pawn() {

}

Pawn::Pawn(int color, float dirX, float dirY) {
	this->color = color;
	this->initTexture();
	this->initSprite();
	this->spritePawn.setPosition(sf::Vector2f(dirX, dirY));
	this->spritePawn.setOrigin(75.f, 75.f);
}

Pawn::~Pawn() {

}

void Pawn::initTexture() {
	if (this->color == 0)
		this->texturePawn.loadFromFile("Images/WhitePieces/W_Pawn.png");
	else
		this->texturePawn.loadFromFile("Images/BlackPieces/B_Pawn.png");
}

void Pawn::initSprite() {
	//Set the texture to the sprite.
	this->spritePawn.setTexture(this->texturePawn);

	//Resize the sprite.
	this->spritePawn.scale(0.5f, 0.5f);
}

void Pawn::update() {

}

void Pawn::render(sf::RenderTarget& target) {
	target.draw(this->spritePawn);
}

void Pawn::move(const float dirX, const float dirY) {
	this->spritePawn.setPosition(dirX, dirY);
}


