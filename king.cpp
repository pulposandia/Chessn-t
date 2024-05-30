#include <SFML/Graphics.hpp>
#include <vector>
#include "king.h"

const sf::FloatRect& chessPiece::getSquare()
{
	m_atSquare = m_sprite.getGlobalBounds();
	return m_atSquare;
}

void chessPiece::setPosition(sf::Vector2f& position)
{

	m_position = position;
	m_sprite.setPosition(m_position); 
}

//sets position but also checks if the new position is in top of another piece
void chessPiece::setPosition(sf::Vector2f& position, std::vector<chessPiece*>& pieces)
{
	Helicopter x{isOnAnotherPiece(pieces, position)};
	if (x.booleant)
		pieces[x.index]->setCapture(true);

	m_position = position;
	m_sprite.setPosition(m_position);

	if (!m_hasAlreadyMove) //if moved my the user for this first time record it with this bool
		m_hasAlreadyMove = !m_hasAlreadyMove;
}

//returns bool after checking if the given move falls on top of another piece
Helicopter chessPiece::isOnAnotherPiece(std::vector<chessPiece*>& pieces, sf::Vector2f& move)
{
	for (size_t i = 0; i < pieces.size(); i++)
	{
		if ( (move == pieces[i]->getPosition()) && !pieces[i]->hasBeenCapture() )
		{
			return { true, i };
		}
	}

	return {false, 0};
}

void chessPiece::firstMovePawn(std::vector<sf::FloatRect>& thePosibleMoves, std::vector<chessPiece*>& pieces)
{
	if (thePosibleMoves.empty()) //if the pawn is already blocked then no need to calculate anything
		return;
	float ySize{ 100 };
	float yJumpPosition{ (ySize * m_validMoves[0].y) + thePosibleMoves[0].getPosition().y };
	sf::Vector2f pawnJump{ thePosibleMoves[0].getPosition().x, yJumpPosition}; //sets the coordinates of the move
	
	if (!isOnAnotherPiece(pieces, pawnJump).booleant) //if the jump falls on any piece do add the move
		thePosibleMoves.push_back(sf::FloatRect{ pawnJump, sf::Vector2f{ySize, ySize} });

}

void chessPiece::addPawnEatings(std::vector<sf::FloatRect>& thePosibleMoves, std::vector<chessPiece*>& pieces)
{
	float sideOfSquare{ 100.f };
	sf::Vector2f possibleMove{};
	for (size_t j = 1; j < m_validMoves.size(); j++)
	{
		possibleMove = (m_validMoves[j] * sideOfSquare) + m_position;
		Helicopter pieceFallsOn(isOnAnotherPiece(pieces, possibleMove));
		if( pieceFallsOn.booleant && ((m_color != pieces[pieceFallsOn.index]->getColor())))
			thePosibleMoves.push_back(sf::FloatRect{ possibleMove, sf::Vector2f{100, 100} });

	}
}

//gets a vewctor from main and fills it up with the square of the possible moves of a piece according to its position
void chessPiece::getAreasOfPMoves(std::vector<sf::FloatRect>& x, std::vector<chessPiece*>& pieces)
{
	x.clear();
	sf::Vector2f possibleMove{};
	
	for (size_t j = 0; j < m_validMoves.size(); j++)
	{
		for (float i{ 1.f }; i <= m_maxDistance; i++)
		{
			possibleMove = (m_validMoves[j] * 100.f * i) + m_position;
			//adds the square where the possible move is: (position coordinates, area of the square) 
			// if the possible move lands outside the board it doesnt save it to the vector
			if (!(possibleMove.y >= 800 || possibleMove.x >= 800 || possibleMove.y < 0 || possibleMove.x < 0))
			{
				x.push_back(sf::FloatRect{ possibleMove, sf::Vector2f{100, 100} });

				//if the new possible move falls in another piece stops calculating moves in this particular direction and moves onto next direction
				Helicopter pieceFallsOn(isOnAnotherPiece(pieces, possibleMove));
				if (pieceFallsOn.booleant)
				{
					if ( (m_type >= 8) || (m_color == pieces[pieceFallsOn.index]->getColor())) //gets rid of the possible move if the piece it falls on is the same color
						x.pop_back();
					break;
				}
			}

		}
		if (m_type >= 8) //if it is a pawn do not calculate the diagonal moves, will do on another function
			break;
	}

	//dealing with pawns shinanigans
	if (m_type >= 8)
	{
		addPawnEatings(x, pieces);
		if (!m_hasAlreadyMove)
			firstMovePawn(x, pieces);
	}
		
	
}



