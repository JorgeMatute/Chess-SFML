#pragma once
#include "Piece.h"

class Pawn {
public:
	Pawn();
	~Pawn();

private:
	sf::RectangleShape pawnShape;

	void initVariables();
	void initShape();
};

