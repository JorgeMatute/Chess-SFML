#include "Rook.h"

//Constructors and destructor.
Rook::Rook() {

}

Rook::Rook(int color, float dirX, float dirY, int x, int y) {
	this->color = color;
	this->initTexture();
	this->initSprite();
	this->spriteRook.setPosition(sf::Vector2f(dirX, dirY));
	this->spriteRook.setOrigin(75.f, 75.f);
	this->x = x;
	this->y = y;
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

void Rook::render(sf::RenderTarget& target) {
	target.draw(this->spriteRook);
}



void Rook::move(const float dirX, const float dirY) {
	this->spriteRook.setPosition(dirX, dirY);
}

/*
0 -> white
1 -> black
2 -> empty square
*/

//Return true if there is at least one square to move.
bool Rook::isMoveLegal(int board[][8]) {
	
	//White.
	if (color == 0) {
		if (((y + 1) < 8) && (board[x][y + 1] == 2 || board[x][y + 1] == 1)) //Making sure of the max and min range.
			return true;
		else if (((y - 1) >= 0) && (board[x][y - 1] == 2 || board[x][y - 1] == 1))
			return true;
		else if (((x + 1) < 8) && (board[x + 1][y] == 2 || board[x + 1][y] == 1))
			return true;
		else if (((x - 1) >= 0) && (board[x - 1][y] == 2 || board[x - 1][y] == 1))
			return true;
	}
	//Black.
	else {
		if (((y + 1) < 8) && (board[x][y + 1] == 2 || board[x][y + 1] == 0))//Making sure of the max and min range.
			return true;
		else if (((y - 1) >= 0) && (board[x][y - 1] == 2 || board[x][y - 1] == 0))
			return true;
		else if (((x + 1) < 8) && (board[x + 1][y] == 2 || board[x + 1][y] == 0))
			return true;
		else if (((x - 1) >= 0) && (board[x - 1][y] == 2 || board[x - 1][y] == 0))
			return true;
	}

	return false;
}