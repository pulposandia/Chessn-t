#ifndef PIECES_H
#define PIECES_H
#include <SFML/Graphics.hpp>
#include <vector>

//sets an enum class to hold what piece is being inspeceted during the frame
enum piece
{
	BishopL,
	BishopR,
	RookL,
	RookR,
	KnightL,
	KnightR,
	King,
	Queen,
	Pawn1,
	Pawn2,
	Pawn3,
	Pawn4,
	Pawn5,
	Pawn6,
	Pawn7,
	Pawn8,
	none,
};

//enum that holds the color of the pieces
enum coloring
{
	white,
	black,
};

//sets up a stuck that is use in the funciton that checks if piece is about to get 
struct Helicopter
{
	bool booleant{};
	size_t index{};
};

struct protectingKing
{
	bool booleant{};
	sf::Vector2f direction{};
};

class chessPiece
{
public:
	chessPiece(piece type, sf::Texture& texture, float maxDistance, coloring color)
		: m_type{ type }, m_maxDistance { maxDistance }, m_color{color}
	{
		m_sprite.setTexture(texture);
	};


public:
	sf::Sprite& getSprite() { return m_sprite; }
	std::vector<sf::Vector2f>& getMovesVector() { return m_validMoves; }
	const piece& getPieceType() { return m_type; }
	const coloring& getColor() { return m_color; }
	const sf::Vector2f& getPosition() { return m_position; }
	bool hasBeenCapture() { return m_isCaptured; }

public:
	void getAreasOfPMoves(std::vector<sf::FloatRect>& x, std::vector<chessPiece*>& pieces);
	const sf::FloatRect& getSquare();
	void setPosition(sf::Vector2f& position);
	void setPosition(sf::Vector2f& position, std::vector<chessPiece*>& pieces);
	
	
// private variables start here
private:
	sf::Sprite m_sprite;
	sf::FloatRect m_atSquare;
	sf::Vector2f m_position;
	bool m_isCaptured{ false };
	bool m_hasAlreadyMove{ false };
	coloring m_color;

private:
	float m_maxDistance{};
	piece m_type{};
	std::vector<sf::Vector2f> m_validMoves;

private:
	Helicopter isOnAnotherPiece(std::vector<chessPiece*>& pieces, sf::Vector2f& move);
	void firstMovePawn(std::vector<sf::FloatRect>& thePosibleMoves, std::vector<chessPiece*>& pieces);
	void addPawnEatings(std::vector<sf::FloatRect>& thePosibleMoves, std::vector<chessPiece*>& pieces);
	protectingKing& protectingKingFrom(std::vector<chessPiece*>& pieces);
	bool isAnyPieceOnTheWay(sf::Vector2f& direction, std::vector<chessPiece*>& pieces, bool isIgnoringKing = false);
	bool isDangerOnTheWay(sf::Vector2f& dangersDirection, std::vector<chessPiece*>& pieces);
	void setCapture(bool x) { m_isCaptured = x; }
};


#endif