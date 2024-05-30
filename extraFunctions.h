#ifndef EXTRAFUCNTIONS_H
#define EXTRAFUCNTIONS_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "extraFunctions.h"
#include "Draw chess board.h"
#include "king.h"



void printPossiblemoves(std::vector<sf::FloatRect>& coord, sf::Sprite& rombo, sf::RenderWindow& window);

Helicopter checkIfMouseOnIt(std::vector<sf::FloatRect>& coord, sf::RenderWindow& window);

void setThePossibleMoves(chessPiece& x);

bool HasbeenClicked(chessPiece& piece, sf::RenderWindow& window);

void displaySelectScreen(sf::RenderWindow& window);



#endif // !EXTRAFUCNTIONS_H
