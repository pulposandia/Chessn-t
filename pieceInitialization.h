#ifndef PIECEINITIALIZATION_H
#define PIECEINITIALIZATION_H

void initializeWhitePieces(std::vector<chessPiece*>& whitePieces, bool isWhiteOnTop);
void initializeBlackPieces(std::vector<chessPiece*>& whitePieces, bool isBlackOnTop);
void setBottomInitialPosition(std::vector<chessPiece*>& Pieces);
void setTopInitialPosition(std::vector<chessPiece*>& Pieces);

#endif // !PIECEINITIALIZATION_H

