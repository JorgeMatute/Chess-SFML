#pragma once

#include <iostream>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Piece {
public:
	
	enum TypePiece {
		PAWN,
		ROOK,
		KNIGHT,
		BISHOP,
		KING,
		QUEEN
	};

	//Constructors and destructors.
	Piece();
	Piece(int color, TypePiece typePiece, sf::Vector2f position);
	~Piece();

private:
	//Getters.
	int getColor();
	sf::Vector2f getPosition();
	int getTypePiece();
	//Setters.
	void setColor(int color);
	void setTypePiece(TypePiece typePiece);
	void asignTexture(sf::Texture* textureWhite[], int size1, sf::Texture* textureBlack[], int size2);

private:
	int color;
	TypePiece typePiece;
	sf::Vector2f position;
};

