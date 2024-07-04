#include <SFML/Graphics.hpp>
#include "title screen.h"
#include "Draw chess board.h"

//advances the animation of the dancing pawns (either color)
void dancingPawn(sf::Clock& clock, sf::IntRect& pawnRec, sf::Sprite& pawn, int initPosition)
{
	if (clock.getElapsedTime().asSeconds() >= 0.25f)
	{
		if (pawnRec.left == initPosition + (16 * 3) )
			pawnRec.left = initPosition;
		else
			pawnRec.left += 16;
		pawn.setTextureRect(pawnRec);
		pawn.setScale(9.375, 9.375);
		clock.restart();
	}
}



//sets up the select screen
void displayTitleScreen(sf::RenderWindow& window, bool& isWhiteOnTop, bool& isBlackOnTop)
{
	sf::Texture whitePiece;
	if (!whitePiece.loadFromFile("Chess Pieces.png"))
		static_assert(true && "it didnt work");
	sf::Texture blackPiece;
	if (!blackPiece.loadFromFile("Chess Pieces.png"))
		static_assert(true && "it didnt work");

	int textureSize{ 16 };
	int yWhitePawn(96);
	int xWhitePawn(0);
	sf::IntRect wPawnRec(xWhitePawn, yWhitePawn, textureSize, textureSize);

	sf::Sprite whitePawn;
	whitePawn.setTexture(whitePiece);
	whitePawn.setTextureRect(wPawnRec);
	whitePawn.setScale(9.375, 9.375);
	whitePawn.setPosition(sf::Vector2f{ 135.8, 407.5 });

	int yBlackPawn(96);
	int xBlackPawn(80);
	sf::IntRect bPawnRec(xBlackPawn, yBlackPawn, textureSize, textureSize);

	sf::Sprite blackPawn;
	blackPawn.setTexture(blackPiece);
	blackPawn.setTextureRect(bPawnRec);
	blackPawn.setScale(9.375, 9.375);
	blackPawn.setPosition(sf::Vector2f{ 529.2, 407.5 });


	sf::Clock clock; //sets the lock uused tob time sprite animation


	// loads in logo
	sf::Texture logo;
	if (!logo.loadFromFile("chess logo.png"))
		static_assert(true && "it didnt work");
	sf::Sprite chessLogo;
	chessLogo.setTexture(logo);
	chessLogo.setPosition(sf::Vector2f{ 195, 75 });

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left))
			{
				if (whitePawn.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
				{
					isBlackOnTop = true;
					return;
				}

				if (blackPawn.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
				{
					isWhiteOnTop = true;
					return;
				}
			}
		}

		//programs an animated white pawn
		if (whitePawn.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
		{
			dancingPawn(clock, wPawnRec, whitePawn, 16);
		}
		else
		{
			wPawnRec.left = xWhitePawn;
			whitePawn.setTextureRect(wPawnRec);
			whitePawn.setScale(9.375, 9.375);
		}

		if (blackPawn.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
		{
			dancingPawn(clock, bPawnRec, blackPawn, xBlackPawn + textureSize);
		}
		else
		{
			bPawnRec.left = xBlackPawn;
			blackPawn.setTextureRect(bPawnRec);
			blackPawn.setScale(9.375, 9.375);
		}


		//sets up the backgournd of the menu by making a square with sf::vertex array an chaging the colors of the veertex so it makes a gradient
		sf::VertexArray backGround(sf::Quads, 4);
		backGround[0].position = sf::Vector2f(0, 0);
		backGround[1].position = sf::Vector2f(0, 800 + origin.x);
		backGround[2].position = sf::Vector2f(800 + origin.x, 800 + origin.x);
		backGround[3].position = sf::Vector2f(800 + origin.x, 0);

		backGround[0].color = sf::Color{ 192,192,192 };
		backGround[1].color = sf::Color{ 52,255,52 };
		backGround[2].color = sf::Color{ 52,255,52 };
		backGround[3].color = sf::Color{ 192,192,192 };



		window.clear();
		window.draw(backGround);
		window.draw(chessLogo);
		window.draw(whitePawn);
		window.draw(blackPawn);
		window.display();
	}


}