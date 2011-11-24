#ifndef _PIECES_H
#define _PIECES_H

/* Define all the different shapes we can have */
enum PieceShape { None, Z, S, Line, T, Square, L, BackwardsL };

class Piece
{
public:
    Shape() { SetShape(None); }
    
    void SetShape(PieceShape shape);
    void SetRandomShape();

    PieceShape GetShape() const { return pieceShape; }

    int x(int i) const { return loc[i][0]; }
    int y(int i) const { return loc[i][1]; }

private:
    PieceShape pieceShape;
    int loc[4][2];
};

#endif
