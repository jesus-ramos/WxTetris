#ifndef _PIECE_H
#define _PIECE_H

#define XCOORD 0
#define YCOORD 1

/* Define all the different shapes we can have */
enum PieceShape { None, Z, S, Line, T, Square, L, BackwardsL };

const int pieceCoords[8][4][2] =
{
    { {0,  0},  {0, 0},  {0,  0}, {0,  0} },
    { {0,  -1}, {0, 0},  {-1, 0}, {-1, 1} },
    { {0,  -1}, {0, 0},  {1,  0}, {1,  1} },
    { {0,  -1}, {0, 0},  {0,  1}, {0,  2} },
    { {-1, 0},  {0, 0},  {1,  0}, {0,  1} },
    { { 0, 0},  {1, 0},  {0,  1}, {1,  1} },
    { {-1, -1}, {0, -1}, {0,  0}, {0,  1} },
    { {1,  -1}, {0, -1}, {0,  0}, {0,  1} }
};

class Piece
{
public:
    Piece() { SetShape(None); }

    void SetShape(PieceShape shape);
    void SetRandomShape();

    PieceShape GetShape() const { return pieceShape; }

    int x(int i) const { return coords[i][XCOORD]; }
    int y(int i) const { return coords[i][YCOORD]; }
    int MinX() const;
    int MaxX() const;
    int MinY() const;
    int MaxY() const;

    Piece RotateLeft() const;
    Piece RotateRight() const;

private:
    void SetX(int idx, int val) { coords[idx][XCOORD] = val; }
    void SetY(int idx, int val) { coords[idx][YCOORD] = val; }
    PieceShape pieceShape;
    int coords[4][2];
};

#endif
