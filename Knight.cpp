#include "Knight.h"

//Constructors and destructor.
Knight::Knight() {

}

Knight::Knight(int color, float dirX, float dirY, int x, int y) {
	this->color = color;
	this->initTexture();
	this->initSprite();
	this->spriteKnight.setPosition(sf::Vector2f(dirX, dirY));
	this->spriteKnight.setOrigin(75.f, 75.f);
	this->x = x;
	this->y = y;
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

void Knight::render(sf::RenderTarget& target) {
	target.draw(this->spriteKnight);
}

void Knight::move(const float dirX, const float dirY) {
	this->spriteKnight.setPosition(dirX, dirY);
}

/*
	0 -> white
	1 -> black
	2 -> empty square
*/

//Return true if there is at least one square where to move.
bool Knight::isMoveLegal(int board[][8])
{
	//White.
	if (color == 0) {//Eight possible moves.
		if ((x + 2) <= 7 && (y - 1) >= 0 && (board[x + 2][y - 1] == 2 || board[x + 2][y - 1] == 1))
			return true;
		else if ((x + 2) <= 7 && (y + 1) <= 7 && (board[x + 2][y + 1] == 2 || board[x + 2][y + 1] == 1))
			return true;
		else if ((x + 1) <= 7 && (y - 2) >= 0 && (board[x + 1][y - 2] == 2 || board[x + 1][y - 2] == 1))
			return true;
		else if ((x - 1) >= 0 && (y - 2) >= 0 && (board[x - 1][y - 2] == 2 || board[x - 1][y - 2] == 1))
			return true;
		else if ((x - 2) >= 0 && (y - 1) >= 0 && (board[x - 2][y - 1] == 2 || board[x - 2][y - 1] == 1))
			return true;
		else if ((x - 2) >= 0 && (y + 1) <= 7 && (board[x - 2][y + 1] == 2 || board[x - 2][y + 1] == 1))
			return true;
		else if ((x - 1) >= 0 && (y + 2) <= 7 && (board[x - 1][y + 2] == 2 || board[x - 1][y + 2] == 1))
			return true;
		else if ((x + 1) <= 7 && (y + 2) <= 7 && (board[x + 1][y + 2] == 2 || board[x + 1][y + 2] == 1))
			return true;
	}
	else { //Black.
		if ((x + 2) <= 7 && (y - 1) >= 0 && (board[x + 2][y - 1] == 2 || board[x + 2][y - 1] == 0))
			return true;
		else if ((x + 2) <= 7 && (y + 1) <= 7 && (board[x + 2][y + 1] == 2 || board[x + 2][y + 1] == 0))
			return true;
		else if ((x + 1) <= 7 && (y - 2) >= 0 && (board[x + 1][y - 2] == 2 || board[x + 1][y - 2] == 0))
			return true;
		else if ((x - 1) >= 0 && (y - 2) >= 0 && (board[x - 1][y - 2] == 2 || board[x - 1][y - 2] == 0))
			return true;
		else if ((x - 2) >= 0 && (y - 1) >= 0 && (board[x - 2][y - 1] == 2 || board[x - 2][y - 1] == 0))
			return true;
		else if ((x - 2) >= 0 && (y + 1) <= 7 && (board[x - 2][y + 1] == 2 || board[x - 2][y + 1] == 0))
			return true;
		else if ((x - 1) >= 0 && (y + 2) <= 7 && (board[x - 1][y + 2] == 2 || board[x - 1][y + 2] == 0))
			return true;
		else if ((x + 1) <= 7 && (y + 2) <= 7 && (board[x + 1][y + 2] == 2 || board[x + 1][y + 2] == 0))
			return true;
	}

	return false;
}
