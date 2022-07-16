#include "Bishop.h"

//Constructors and destructor.
Bishop::Bishop() {

}

Bishop::Bishop(int color, float dirX, float dirY, int x, int y) {
	this->color = color;
	this->initTexture();
	this->initSprite();
	this->spriteBishop.setPosition(sf::Vector2f(dirX, dirY));
	this->spriteBishop.setOrigin(75.f, 75.f);
	this->x = x;
	this->y = y;
}

Bishop::~Bishop() {

}

void Bishop::initTexture() {
	if (this->color == 0)
		this->textureBishop.loadFromFile("Images/WhitePieces/W_Bishop.png");
	else
		this->textureBishop.loadFromFile("Images/BlackPieces/B_Bishop.png");
}

void Bishop::initSprite() {
	//Set the texture to the sprite.
	this->spriteBishop.setTexture(this->textureBishop);

	//Resize the sprite.
	this->spriteBishop.scale(0.5f, 0.5f);
}


void Bishop::render(sf::RenderTarget& target) {
	target.draw(this->spriteBishop);
}

void Bishop::move(const float dirX, const float dirY) {
	this->spriteBishop.setPosition(dirX, dirY);
}


/*
	0 -> white
	1 -> black
	2 -> empty square
*/

//Return true if there is at least one square where to move.
bool Bishop::isMoveLegal(int board[][8]) {

	//White.
	if (color == 0) {
		//Left - UP.
		if ((((x - 1) >= 0) && ((y - 1) >= 0)) && (board[x - 1][y - 1] == 2 || board[x - 1][y - 1] == 1))
			return true;
		//Left - DOWN.
		else if ((((x - 1) >= 0) && ((y + 1) <= 7)) && (board[x - 1][y + 1] == 2 || board[x - 1][y + 1] == 1))
			return true;
		//Right - UP.
		if ((((x + 1) <= 7) && ((y - 1) >= 0)) && (board[x + 1][y - 1] == 2 || board[x + 1][y - 1] == 1))
			return true;
		//Right - DOWN.
		if ((((x + 1) <= 7) && ((y + 1) <= 7)) && (board[x + 1][y + 1] == 2 || board[x + 1][y + 1] == 1))
			return true;
	}
	else { //Black.

		//Left - UP.
		if ((((x - 1) >= 0) && ((y - 1) >= 0)) && (board[x - 1][y - 1] == 2 || board[x - 1][y - 1] == 0))
			return true;
		//Left - DOWN.
		else if ((((x - 1) >= 0) && ((y + 1) <= 7)) && (board[x - 1][y + 1] == 2 || board[x - 1][y + 1] == 0))
			return true;
		//Right - UP.
		if ((((x + 1) <= 7) && ((y - 1) >= 0)) && (board[x + 1][y - 1] == 2 || board[x + 1][y - 1] == 0))
			return true;
		//Right - DOWN.
		if ((((x + 1) <= 7) && ((y + 1) <= 7)) && (board[x + 1][y + 1] == 2 || board[x + 1][y + 1] == 0))
			return true;
	}

	return false;
}
