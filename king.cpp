#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>
#include "king.h"
#include "Draw chess board.h"

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


protectingKing& chessPiece::protectingKingFrom(std::vector<chessPiece*>& pieces)
{
	protectingKing failState{ false, sf::Vector2f{-1,-1} };
	protectingKing dangersDirection{ true, sf::Vector2f{0,0} };

	//ignore this function if the clicked piece is king
	if (m_type == King)
		return failState;
	// with a loop looks for the king of same color in case I re-order the vector in  a weird way
	sf::Vector2f kingPosition{};
	for (size_t i = 0; i < pieces.size(); i++)
	{
		if (pieces[i]->getColor() == m_color && pieces[i]->getPieceType() == King)
		{
			kingPosition = pieces[i]->getPosition();
			break;
		}
	}
	// does math to get the direction to the king from this* piece. Only if it deems the piece is in the kings sight.
	sf::Vector2f vectorPieceKing{ kingPosition - m_position };
	if ((abs(vectorPieceKing.x) == abs(vectorPieceKing.y)) || (vectorPieceKing.x == 0.f || vectorPieceKing.y == 0.f))
	{
		vectorPieceKing /= 100.f;
		if (vectorPieceKing.x != 0.f)
			vectorPieceKing.x /= abs(vectorPieceKing.x);
		if (vectorPieceKing.y != 0.f)
			vectorPieceKing.y /= abs(vectorPieceKing.y);
	
		dangersDirection.direction = vectorPieceKing * -1.f;  //flips it so now the vector is looking from the king to the piece
		sf::Vector2f nextSquare{};

		//loop to check if the king is alredy protected with another piece
		for (float i = 1; i < 8; i++)
		{
			nextSquare = (vectorPieceKing * 100.f * i) + m_position;
			if (nextSquare.y >= 800 || nextSquare.x >= 800 || nextSquare.y < 0 || nextSquare.x < 0)
				break;
			Helicopter variable{ isOnAnotherPiece(pieces, nextSquare) };
			if (!variable.booleant)
				continue;
			//if there is another piece that is protecting the king then allow this* piece to move freely
			if (variable.booleant && (pieces[variable.index]->getPieceType() != King))
				return failState;
		}

		//this loop checks for the pieces after this* piece in the direction we found above
		for (float i = 1; i < 8; i++)
		{
			nextSquare = (dangersDirection.direction * 100.f * i) + m_position;
			if (nextSquare.y >= 800 || nextSquare.x >= 800 || nextSquare.y < 0 || nextSquare.x < 0)
				break;
			Helicopter variable{ isOnAnotherPiece(pieces, nextSquare) };
			//if there is no piece in the next squre from this* piece then move to the next square
			if (!variable.booleant)
				continue;
			//if there is a piece and is oppositive color then return the direction
			if (variable.booleant && pieces[variable.index]->getColor() != m_color)
			{//only forbids movement if a bishop is lookaing at the king in a diagonal and if a rook is looking at the king in a stright line
				if (pieces[variable.index]->getPieceType() == Queen)
					return dangersDirection;
				else if ((abs(dangersDirection.direction.x) + abs(dangersDirection.direction.y)) == 2.f && (pieces[variable.index]->getPieceType() == BishopL || pieces[variable.index]->getPieceType() == BishopR))
					return dangersDirection;
				else if ((abs(dangersDirection.direction.x) + abs(dangersDirection.direction.y)) == 1.f && (pieces[variable.index]->getPieceType() == RookL || pieces[variable.index]->getPieceType() == RookR))
					return dangersDirection;
			}
			//if a same color piece is found then return a fail state
			else
				return failState;
		}
	
	}
	//std::cout << "x: " << m_position.x << " y: " << m_position.y << '\n';
	//std::cout << "x: " << vectorPieceKing.x << " y: " << vectorPieceKing.y << '\n';
	//if no piece of different color is found returna fail state
	return failState;
}

//gets a vewctor from main and fills it up with the square of the possible moves of a piece according to its position
void chessPiece::getAreasOfPMoves(std::vector<sf::FloatRect>& x, std::vector<chessPiece*>& pieces)
{
	x.clear();
	sf::Vector2f possibleMove{};
	protectingKing isProtectingKing{ protectingKingFrom(pieces) };
	for (size_t j = 0; j < m_validMoves.size(); j++)
	{
		// if the piece is protecting the king from check then do not allow that piece to move away and leave the king unprotected
		if (isProtectingKing.booleant && (m_validMoves[j] != isProtectingKing.direction))
		{
			if (m_type >= 8)
				break;
			continue;
		}
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