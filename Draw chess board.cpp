#include <SFML/Graphics.hpp>
#include "Draw chess board.h"

sf::Vector2f origin{ 15.f, 0 };

void drawBoard(sf::RenderWindow& window)
{
    static sf::RectangleShape square(sf::Vector2f(100.f, 100.f));

    sf::RectangleShape vertical(sf::Vector2f(15.f, 800 + origin.x));
    sf::RectangleShape horizontal(sf::Vector2f(800 + origin.x, origin.x));
    vertical.setFillColor(sf::Color(30, 30, 30));
    horizontal.setFillColor(sf::Color(30, 30, 30));
    horizontal.setPosition(0.f, 800.f);


    //draws the even line's white squares
    for (float yCord{ origin.y }; yCord < 800; yCord += 200)
    {
        for (float xCord{ origin.x }; xCord < 800; xCord += 200)
        {
            square.setPosition(xCord, yCord);
            window.draw(square);
        }
    }

    //draws the odd line's white squares
    for (float yCord{ 100 + origin.y }; yCord < 800; yCord += 200)
    {
        for (float xCord{ 100 + origin.x }; xCord < 800; xCord += 200)
        {
            square.setPosition(xCord, yCord);
            window.draw(square);
        }
    }

    window.draw(vertical);
    window.draw(horizontal);
}
