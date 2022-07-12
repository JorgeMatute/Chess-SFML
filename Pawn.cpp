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

bool Pawn::isMoveLegal(int board[][8]) {  

	if (color == 0) { 
		if (fistMove == 0) { //Fisrt move (WHITE).
			if ((board[x][y - 1] == 2) && (board[x][y - 2] == 2)) {
				return true;
			}
			else if (board[x][y - 1] == 2) {
				return true;
			}
			else if ((((board[x][y - 1] == 1) || (board[x][y - 1] == 0)) && (board[x + 1][y-1] == 1) || (board[x - 1][y-1] == 1))){
				return true;
			}
			else if (((board[x][y - 1] == 1) || (board[x][y - 1] == 0))) {
				return false;
			}
			return true;
		}
		else {
			if ((board[x][y - 1] == 2) || (board[x + 1][y-1] == 1) || (board[x - 1][y-1] == 1)) {
				return true;
			}
		}
		return false;
	}
	else {
		if (fistMove == 0) { //Fisrt move (BLACK).
			if ((board[x][y + 1] == 2) || (board[x][y + 2] == 2)) {
				return true;
			}
		}
		else {
			if ((board[x][y + 1] == 2)) {
				return true;
			}
		}
		return false;
	}
}

//Only forward movement.
int Pawn::movePiece(int board[][8]) {
	if (color == 0) {
		if (fistMove == 0) { //Fisrt move (WHITE).
			if (((board[x][y - 1] == 2) || (board[x][y - 2] == 2)) && (board[x][y - 1] != 0) || (board[x][y - 2] == 0)) {
				return (y - 2);
			}
		}
		else {
			if ((board[x][y - 1] == 2) && (board[x][y - 1] != 0)) {
				return (y - 1);
			}
		}
		return 0;
	}
	else {
		if (fistMove == 0) { //Fisrt move (BLACK).
			if ((board[x][y + 1] == 2) || (board[x][y + 2] == 2) && (board[x][y + 1] != 1) || (board[x][y + 2] != 1)) {
				return (y + 2);
			}
		}
		else {
			if ((board[x][y + 1] == 2) && (board[x][y + 1] != 1)) {
				return (y + 1);
			}
		}
		return 0; 
	}			  
}

//

