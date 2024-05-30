#include <SFML/Graphics.hpp>
#include <vector>
#include "king.h"
#include "pieceInitialization.h"
#include "extraFunctions.h"

void initializeWhitePieces(std::vector<chessPiece*>& whitePieces)
{
    int xTexture{ 16 };
    int yTexture{ 16 };
    int textureSize{ 16 };
    for (size_t i = 0; i < whitePieces.size(); i++)
    {
        //chooses the right sprite for each type of piece
        switch (whitePieces[i]->getPieceType())
        {
        case King:
            whitePieces[i]->getSprite().setTextureRect(sf::IntRect{ xTexture * 4 ,0,textureSize,textureSize });
            break;
        case Queen:
            whitePieces[i]->getSprite().setTextureRect(sf::IntRect{ xTexture * 3 ,0,textureSize,textureSize });
            break;
        case BishopL:
            whitePieces[i]->getSprite().setTextureRect(sf::IntRect{ xTexture * 2 ,0,textureSize,textureSize });
            break;
        case BishopR:
            whitePieces[i]->getSprite().setTextureRect(sf::IntRect{ xTexture * 2 ,0,textureSize,textureSize });
            break;
        case RookR:
            whitePieces[i]->getSprite().setTextureRect(sf::IntRect{ xTexture * 0 ,0,textureSize,textureSize });
            break;
        case RookL:
            whitePieces[i]->getSprite().setTextureRect(sf::IntRect{ xTexture * 0 ,0,textureSize,textureSize });
            break;
        case KnightL:
            whitePieces[i]->getSprite().setTextureRect(sf::IntRect{ xTexture * 1 ,0,textureSize,textureSize });
            break;
        case KnightR:
            whitePieces[i]->getSprite().setTextureRect(sf::IntRect{ xTexture * 1 ,0,textureSize,textureSize });
            break;
            //assuming only valid chess pieces are send to this function the pawn are set next:
        default:
            whitePieces[i]->getSprite().setTextureRect(sf::IntRect{ xTexture * 5 ,0,textureSize,textureSize });
            break;

        }
        whitePieces[i]->getSprite().setScale(6.25, 6.25);
        setThePossibleMoves(*whitePieces[i]);
    }
}

void setWhiteInitialPosition(std::vector<chessPiece*>& whitePieces)
{
    sf::Vector2f boardPosition{ 0.f + origin.x, 700.f };
    float sizeOfSquare{ 100.f };
    for (size_t i = 0; i < whitePieces.size(); i++)
    {
        whitePieces[i]->setPosition(boardPosition);
        if (i < 7)
            boardPosition.x += sizeOfSquare;
        if (i == 7)
            boardPosition.y -= sizeOfSquare;
        if (i > 7)
            boardPosition.x -= sizeOfSquare;
    }
}
