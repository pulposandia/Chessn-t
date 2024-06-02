#include <SFML/Graphics.hpp>
#include <vector>
#include "king.h"
#include "pieceInitialization.h"
#include "extraFunctions.h"

void initializeWhitePieces(std::vector<chessPiece*>& whitePieces)
{
    int xTexture{ 16 };
    int yTexture{ 0 };
    int textureSize{ 16 };
    for (size_t i = 0; i < whitePieces.size(); i++)
    {
        //chooses the right sprite for each type of piece
        switch (whitePieces[i]->getPieceType())
        {
        case King:
            whitePieces[i]->getSprite().setTextureRect(sf::IntRect{ xTexture * 4 ,yTexture,textureSize,textureSize });
            break;
        case Queen:
            whitePieces[i]->getSprite().setTextureRect(sf::IntRect{ xTexture * 3 ,yTexture,textureSize,textureSize });
            break;
        case BishopL:
            whitePieces[i]->getSprite().setTextureRect(sf::IntRect{ xTexture * 2 ,yTexture,textureSize,textureSize });
            break;
        case BishopR:
            whitePieces[i]->getSprite().setTextureRect(sf::IntRect{ xTexture * 2 ,yTexture,textureSize,textureSize });
            break;
        case RookR:
            whitePieces[i]->getSprite().setTextureRect(sf::IntRect{ xTexture * 0 ,yTexture,textureSize,textureSize });
            break;
        case RookL:
            whitePieces[i]->getSprite().setTextureRect(sf::IntRect{ xTexture * 0 ,yTexture,textureSize,textureSize });
            break;
        case KnightL:
            whitePieces[i]->getSprite().setTextureRect(sf::IntRect{ xTexture * 1 ,yTexture,textureSize,textureSize });
            break;
        case KnightR:
            whitePieces[i]->getSprite().setTextureRect(sf::IntRect{ xTexture * 1 ,yTexture,textureSize,textureSize });
            break;
            //assuming only valid chess pieces are send to this function the pawn are set next:
        default:
            whitePieces[i]->getSprite().setTextureRect(sf::IntRect{ xTexture * 5 ,yTexture,textureSize,textureSize });
            break;

        }
        whitePieces[i]->getSprite().setScale(6.25, 6.25);
    }
}

void initializeBlackPieces(std::vector<chessPiece*>& blackPieces)
{
    int xTexture{ 16 };
    int yTexture{ 16 };
    int textureSize{ 16 };
    for (size_t i = 0; i < blackPieces.size(); i++)
    {
        //chooses the right sprite for each type of piece
        switch (blackPieces[i]->getPieceType())
        {
        case King:
            blackPieces[i]->getSprite().setTextureRect(sf::IntRect{ xTexture * 4 ,yTexture,textureSize,textureSize });
            break;
        case Queen:
            blackPieces[i]->getSprite().setTextureRect(sf::IntRect{ xTexture * 3 ,yTexture,textureSize,textureSize });
            break;
        case BishopL:
            blackPieces[i]->getSprite().setTextureRect(sf::IntRect{ xTexture * 2 ,yTexture,textureSize,textureSize });
            break;
        case BishopR:
            blackPieces[i]->getSprite().setTextureRect(sf::IntRect{ xTexture * 2 ,yTexture,textureSize,textureSize });
            break;
        case RookR:
            blackPieces[i]->getSprite().setTextureRect(sf::IntRect{ xTexture * 0 ,yTexture,textureSize,textureSize });
            break;
        case RookL:
            blackPieces[i]->getSprite().setTextureRect(sf::IntRect{ xTexture * 0 ,yTexture,textureSize,textureSize });
            break;
        case KnightL:
            blackPieces[i]->getSprite().setTextureRect(sf::IntRect{ xTexture * 1 ,yTexture,textureSize,textureSize });
            break;
        case KnightR:
            blackPieces[i]->getSprite().setTextureRect(sf::IntRect{ xTexture * 1 ,yTexture,textureSize,textureSize });
            break;
            //assuming only valid chess pieces are send to this function the pawn are set next:
        default:
            blackPieces[i]->getSprite().setTextureRect(sf::IntRect{ xTexture * 5 ,yTexture,textureSize,textureSize });
            break;

        }
        blackPieces[i]->getSprite().setScale(6.25, 6.25);
    }
}

void setBottomInitialPosition(std::vector<chessPiece*>& whitePieces)
{
    sf::Vector2f boardPosition{ 0.f + origin.x, 700.f };
    float sizeOfSquare{ 100.f };
    bool isInTop{ false };
    for (size_t i = 0; i < whitePieces.size(); i++)
    {
        whitePieces[i]->setPosition(boardPosition);
        if (i < 7)
            boardPosition.x += sizeOfSquare;
        if (i == 7)
            boardPosition.y -= sizeOfSquare;
        if (i > 7)
            boardPosition.x -= sizeOfSquare;

        setThePossibleMoves(*whitePieces[i], isInTop);
    }
}

void setTopInitialPosition(std::vector<chessPiece*>& blackPieces)
{
    sf::Vector2f boardPosition{ 0.f + origin.x, 0.f };
    float sizeOfSquare{ 100.f };
    bool isInTop{ true };
    for (size_t i = 0; i < blackPieces.size(); i++)
    {
        blackPieces[i]->setPosition(boardPosition);
        if (i < 7)
            boardPosition.x += sizeOfSquare;
        if (i == 7)
            boardPosition.y += sizeOfSquare;
        if (i > 7)
            boardPosition.x -= sizeOfSquare;

        setThePossibleMoves(*blackPieces[i], isInTop);
    }
}
