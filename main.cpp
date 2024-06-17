#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Draw chess board.h"
#include "king.h" 
#include "extraFunctions.h"
#include "pieceInitialization.h"
#include "icon.h"



int main()
{
    sf::RenderWindow window(sf::VideoMode(800 + origin.x, 800 + origin.x), "Chessn't", sf::Style::Close); //style define that cant be rezised
    window.setIcon(chess_icon.width, chess_icon.height, chess_icon.pixel_data); // sets the icon using code from icon header

    sf::Texture piesas;
    if (!piesas.loadFromFile("Chess Pieces Static.png"))
        return -1;

    sf::Texture rombotico;
    if (!rombotico.loadFromFile("rombo.png"))
        return -1;

    sf::Sprite rombo;
    rombo.setTexture(rombotico);

    //initizalize white pieces
    chessPiece torreLW{ RookL, piesas, 7.f, white };
    chessPiece caballoLW{ KnightL, piesas, 1.f, white };
    chessPiece alfilLW{ BishopL, piesas, 7.f, white };
    chessPiece reinaW{ Queen, piesas, 7.f, white };
    chessPiece reyW{ King, piesas, 1.f, white };
    chessPiece alfilRW{ BishopR, piesas, 7.f, white };
    chessPiece caballoRW{ KnightR, piesas, 1.f, white };
    chessPiece torreRW{ RookR, piesas, 7.f, white };
    chessPiece peon1W(Pawn1, piesas, 1.f, white);
    chessPiece peon2W(Pawn2, piesas, 1.f, white);
    chessPiece peon3W(Pawn3, piesas, 1.f, white);
    chessPiece peon4W(Pawn4, piesas, 1.f, white);
    chessPiece peon5W(Pawn5, piesas, 1.f, white);
    chessPiece peon6W(Pawn6, piesas, 1.f, white);
    chessPiece peon7W(Pawn7, piesas, 1.f, white);
    chessPiece peon8W(Pawn8, piesas, 1.f, white);

    //initizalize white pieces
    chessPiece torreLB{ RookL, piesas, 7.f, black };
    chessPiece caballoLB{ KnightL, piesas, 1.f, black };
    chessPiece alfilLB{ BishopL, piesas, 7.f, black };
    chessPiece reinaB{ Queen, piesas, 7.f, black };
    chessPiece reyB{ King, piesas, 1.f, black };
    chessPiece alfilRB{ BishopR, piesas, 7.f, black };
    chessPiece caballoRB{ KnightR, piesas, 1.f, black };
    chessPiece torreRB{ RookR, piesas, 7.f, black };
    chessPiece peon1B(Pawn1, piesas, 1.f, black);
    chessPiece peon2B(Pawn2, piesas, 1.f, black);
    chessPiece peon3B(Pawn3, piesas, 1.f, black);
    chessPiece peon4B(Pawn4, piesas, 1.f, black);
    chessPiece peon5B(Pawn5, piesas, 1.f, black);
    chessPiece peon6B(Pawn6, piesas, 1.f, black);
    chessPiece peon7B(Pawn7, piesas, 1.f, black);
    chessPiece peon8B(Pawn8, piesas, 1.f, black);



    //uses std::vector as a stack to hold the coordinates of possible moves of giving piece.
    std::vector<sf::FloatRect> possibleMoves{};
    
    //makes an vector with all the pieces pointers
    std::vector<chessPiece*> whitePieces{ &torreLW, &caballoLW, &alfilLW, &reinaW, &reyW, &alfilRW, &caballoRW, &torreRW, &peon1W, &peon2W, &peon3W, &peon4W, &peon5W, &peon6W, &peon7W, &peon8W};
    initializeWhitePieces(whitePieces);
    setBottomInitialPosition(whitePieces);

    //makes an vector with all black pieces
    std::vector<chessPiece*> blackPieces{ &torreLB, &caballoLB, &alfilLB, &reinaB, &reyB, &alfilRB, &caballoRB, &torreRB, &peon1B, &peon2B, &peon3B, &peon4B, &peon5B, &peon6B, &peon7B, &peon8B };
    initializeBlackPieces(blackPieces);
    setTopInitialPosition(blackPieces);

    //connate both pieces' vectors
    std::vector<chessPiece*> allPieces{};
    allPieces.reserve(whitePieces.size() + blackPieces.size());
    allPieces.insert(allPieces.end(), whitePieces.begin(), whitePieces.end());
    allPieces.insert(allPieces.end(), blackPieces.begin(), blackPieces.end());
 

    int counter{};
    bool isShowingMoves{ false };
    piece type{};
    coloring color{};

    displaySelectScreen(window); //displays a select screen to choose color 

    while (window.isOpen())
    {
        //draws board by painting the window gray and drawing the white squares on top
        window.clear(sf::Color(169, 169, 169));
        drawBoard(window);


        //handles events in que during this frame
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left))
            {
                if (isShowingMoves)
                {
                    //this part checks if users clikced in piece and then moves the piece
                    Helicopter isRomboCliked{ checkIfMouseOnIt(possibleMoves, window) };
                    if (isRomboCliked.booleant)

                    {
                        std::cout << "awebo\n";
                        sf::Vector2f newPosition{ possibleMoves[isRomboCliked.index].getPosition() };
                        //loops thru all pieces and finds the piece the user clicked last and moves it
                        for (size_t i = 0; i < allPieces.size(); i++)
                        {
                            if (type == allPieces[i]->getPieceType() && color == allPieces[i]->getColor())
                            {
                                allPieces[i]->setPosition(newPosition, allPieces);
                            }
                        }

                    }

                    isShowingMoves = false;
                }
                // if not currently showing moves check what piece has been cliked and change variables so next frame the piece's moves will be shown
                else
                    for (size_t i = 0; i < allPieces.size(); i++)
                    {
                        if (HasbeenClicked(*allPieces[i], window))
                        {
                            std::cout << "It works!\n";
                            allPieces[i]->getAreasOfPMoves(possibleMoves, allPieces);
                            type = allPieces[i]->getPieceType();
                            color = allPieces[i]->getColor();
                            isShowingMoves = true;
                        }
                    }
            }
        }
        //draws all pieces that havent been captured yet
        for (auto var : allPieces)
        {
            if (!var->hasBeenCapture())
                window.draw(var->getSprite());
        }
        //keeps drawing possible moves while users decides what to do
        if (isShowingMoves)
            printPossiblemoves(possibleMoves, rombo, window);
        
        

        window.display();
    }

    return 0;
}