#include "King.h"

//Constructors and destructor.
King::King() {

}

King::King(int color, float dirX, float dirY, int x, int y) {
	this->color = color;
	this->initTexture();
	this->initSprite();
	this->spriteKing.setPosition(sf::Vector2f(dirX, dirY));
	this->spriteKing.setOrigin(75.f, 75.f);
	this->x = x;
	this->y = y;
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

void King::render(sf::RenderTarget& target) {
	target.draw(this->spriteKing);
}

void King::move(const float dirX, const float dirY) {
	this->spriteKing.setPosition(dirX, dirY);
}

/*
	0 -> white
	1 -> black
	2 -> empty square
*/

//Return true if there is at least one square where to move.
bool King::isMoveLegal(int board[][8])
{
	//White.
	if (color == 0) {
		//DOWN.
		if (((y + 1) < 8) && (board[x][y + 1] == 2 || board[x][y + 1] == 1)) //Making sure of the max and min range.
			return true;
		//UP.
		else if (((y - 1) >= 0) && (board[x][y - 1] == 2 || board[x][y - 1] == 1))
			return true;
		//RIGHT.
		else if (((x + 1) < 8) && (board[x + 1][y] == 2 || board[x + 1][y] == 1))
			return true;
		//LEFT.
		else if (((x - 1) >= 0) && (board[x - 1][y] == 2 || board[x - 1][y] == 1))
			return true;
		//Left - UP.
		else if ((((x - 1) >= 0) && ((y - 1) >= 0)) && (board[x - 1][y - 1] == 2 || board[x - 1][y - 1] == 1))
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
		if (((y + 1) < 8) && (board[x][y + 1] == 2 || board[x][y + 1] == 0))//Making sure of the max and min range.
			return true;
		else if (((y - 1) >= 0) && (board[x][y - 1] == 2 || board[x][y - 1] == 0))
			return true;
		else if (((x + 1) < 8) && (board[x + 1][y] == 2 || board[x + 1][y] == 0))
			return true;
		else if (((x - 1) >= 0) && (board[x - 1][y] == 2 || board[x - 1][y] == 0))
			return true;
		else if ((((x - 1) >= 0) && ((y - 1) >= 0)) && (board[x - 1][y - 1] == 2 || board[x - 1][y - 1] == 0))
			return true;
		else if ((((x - 1) >= 0) && ((y + 1) <= 7)) && (board[x - 1][y + 1] == 2 || board[x - 1][y + 1] == 0))
			return true;
		if ((((x + 1) <= 7) && ((y - 1) >= 0)) && (board[x + 1][y - 1] == 2 || board[x + 1][y - 1] == 0))
			return true;
		if ((((x + 1) <= 7) && ((y + 1) <= 7)) && (board[x + 1][y + 1] == 2 || board[x + 1][y + 1] == 0))
			return true;
	}
	return false;
}
