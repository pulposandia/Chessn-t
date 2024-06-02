#include <SFML/Graphics.hpp>
#include <vector>
#include "extraFunctions.h"
#include "Draw chess board.h"
#include "king.h"

void printPossiblemoves(std::vector<sf::FloatRect>& coord, sf::Sprite& rombo, sf::RenderWindow& window)
{
	for (auto var : coord)
	{
		rombo.setPosition(var.getPosition());
		//rombo.setPosition(sf::Vector2f{515.f, 300});
		window.draw(rombo);
	}
}

Helicopter checkIfMouseOnIt(std::vector<sf::FloatRect>& coord, sf::RenderWindow& window)
{
	for (size_t i{0} ; i < coord.size() ; i++)
	{
		if (coord[i].contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
		{
			return { true, i };
		}
		
	}

	return { false, 0 };
}

void setThePossibleMoves(chessPiece& x, bool isInTop)
{
	//sets all possible moves

	sf::Vector2f fake{ -10,-10 };
	sf::Vector2f up{ 0, 1 };
	sf::Vector2f left{ -1, 0 };
	sf::Vector2f right{ 1, 0 };
	sf::Vector2f down{ 0, -1 };
	sf::Vector2f diagonal1{ 1, 1 };
	sf::Vector2f diagonal2{ -1, 1 };
	sf::Vector2f diagonal3{ -1, -1 };
	sf::Vector2f diagonal4{ 1, -1 };

	std::vector<sf::Vector2f> movimientos{ fake, up, down, left, right, diagonal1, diagonal2, diagonal3, diagonal4 };

	switch (x.getPieceType())
	{
	case King:
		x.getMovesVector() = movimientos;
		return;
	case Queen:
		x.getMovesVector() = movimientos;
		return;
	case BishopL:
		for (size_t i = 5; i <= 8; i++)
			x.getMovesVector().push_back(movimientos[i]);
		return;
	case BishopR:
		for (size_t i = 5; i <= 8; i++)
			x.getMovesVector().push_back(movimientos[i]);
		return;
	case RookR:
		for (size_t i = 1; i <= 4; i++)
			x.getMovesVector().push_back(movimientos[i]);
		return;
	case RookL:
		for (size_t i = 1; i <= 4; i++)
			x.getMovesVector().push_back(movimientos[i]);
		return;
	case KnightL:
		x.getMovesVector() = std::vector<sf::Vector2f>{{ {1,-2},{-1,-2},{2,-1},{-2,-1},{2,1},{-2,1},{1,2},{-1,2} }};
		return;
	case KnightR:
		x.getMovesVector() = std::vector<sf::Vector2f>{ { {1,-2},{-1,-2},{2,-1},{-2,-1},{2,1},{-2,1},{1,2},{-1,2} } };
		return;
	//assuming only valid chess pieces are send to this function the pawn are set next:
	default:
		if (!isInTop)
		{
			x.getMovesVector().push_back(down);
			x.getMovesVector().push_back(diagonal4);
			x.getMovesVector().push_back(diagonal3);
		}
		if (isInTop)
		{
			x.getMovesVector().push_back(up);
			x.getMovesVector().push_back(diagonal1);
			x.getMovesVector().push_back(diagonal2);
		}

		return;
	}
}

//return bool that is only true if the chess piece was cliked and it hasnt been captured
bool HasbeenClicked(chessPiece& piece, sf::RenderWindow& window)
{
	return piece.getSquare().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))) && !piece.hasBeenCapture();
}

//sets up the select screen
void displaySelectScreen(sf::RenderWindow& window)
{
	sf::Texture playButton;
	if (!playButton.loadFromFile("Play-Idle.png"))
		static_assert(true && "it didnt work");
	sf::Sprite button;
	button.setTexture(playButton);



	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left))
			{
				if (button.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
					return;
			}
		}


		window.draw(button);
		window.display();
	}


}

