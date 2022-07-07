#include "Piece.h"

Piece::Piece(int color, TypePiece typePiece, sf::Vector2f position) {
	this->color = color;
	this->typePiece = typePiece;
	this->position = position;
}

Piece::Piece() {

}

//Getters.
int Piece::getColor() {
	return this->color;
}

sf::Vector2f Piece::getPosition() {
	return this->position;
}

//Setters.
void Piece::setColor(int color) {
	this->color = color;
}

void Piece::setTypePiece(TypePiece typePiece) {
	this->typePiece = typePiece;
}

int Piece::getTypePiece() {
	return this->typePiece;
}