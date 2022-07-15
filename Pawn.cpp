#include "Pawn.h"

//Constructors and destructor.
Pawn::Pawn() {

}

Pawn::Pawn(int color, float dirX, float dirY, int x, int y) {
	this->color = color;
	this->initTexture();
	this->initSprite();
	this->spritePawn.setPosition(sf::Vector2f(dirX, dirY));
	this->spritePawn.setOrigin(75.f, 75.f);
	this->x = x;
	this->y = y;
	this->fistMove = 0;
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

void Pawn::render(sf::RenderTarget& target) {
	target.draw(this->spritePawn);
}

void Pawn::move(const float dirX, const float dirY) {
	this->spritePawn.setPosition(dirX, dirY);
}

/*
0 -> white
1 -> black
2 -> empty square
*/

//Return true if there is at least one square to move.
bool Pawn::isMoveLegal(int board[][8]) {  

	if (color == 0) { 
		if (fistMove == 0) { //Fisrt move (WHITE).
			if ((board[x][y - 1] == 2) && (board[x][y - 2] == 2))
				return true;
			else if (board[x][y - 1] == 2)
				return true;
			else if ((((board[x][y - 1] == 1) || (board[x][y - 1] == 0)) && (board[x + 1][y - 1] == 1) || (board[x - 1][y - 1] == 1)))
				return true;
			else if (((board[x][y - 1] == 1) || (board[x][y - 1] == 0)))
				return false;
			return false;
		}
		else
			if ((board[x][y - 1] == 2) || (board[x + 1][y - 1] == 1) || (board[x - 1][y - 1] == 1)) {
				return true;
		}
		return false;
	}
	else {
		if (fistMove == 0) { //Fisrt move (BLACK).
			if ((board[x][y + 1] == 2) && (board[x][y + 2] == 2))
				return true;
			else if (board[x][y + 1] == 2)
				return true;
			else if ((((board[x][y + 1] == 0) || (board[x][y + 1] == 1)) && (board[x + 1][y + 1] == 0) || (board[x - 1][y + 1] == 0)))
				return true;
			else if (((board[x][y + 1] == 1) || (board[x][y - 1] == 0)))
				return false;
			return false;
		}
		else {
			if ((board[x][y + 1] == 2) || (board[x + 1][y + 1] == 0) || (board[x - 1][y + 1] == 0))
				return true;
		}
		return false;
	}
}