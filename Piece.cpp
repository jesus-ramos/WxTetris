#include <cstdlib>
#include <algorithm>

#include "Piece.hpp"

using namespace std;

/* Let the macro abuse begin */
#define DEFINEFINDMINMAX(coord, op, Name)       \
    int Piece::Name() const                     \
    {                                           \
        int v = coords[0][coord];               \
        for (int i = 0; i < 4; i++)             \
            v = op(v, coords[i][coord]);        \
        return v;                               \
    }

/* I never said I was done abusing them was I? */
#define DEFINEROTATE(coeffy, coeffx, Name)      \
    Piece Piece::Name() const                   \
    {                                           \
        if (pieceShape == Square)               \
            return *this;                       \
                                                \
        Piece res;                              \
        res.pieceShape = pieceShape;            \
        for (int i = 0; i < 4; i++)             \
        {                                       \
            res.SetX(i, coeffy * y(i));         \
            res.SetY(i, coeffx * x(i));         \
        }                                       \
        return res;                             \
    }


void Piece::SetShape(PieceShape shape)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 2; j++)
            coords[i][j] = pieceCoords[shape][i][j];
    pieceShape = shape;
}

void Piece::SetRandomShape()
{
    int rand_shape_idx = rand() % 7 + 1;
    SetShape(PieceShape(rand_shape_idx));
}

/* Good luck debugging this, suckers */
DEFINEFINDMINMAX(XCOORD, min, MinX);
DEFINEFINDMINMAX(XCOORD, max, MaxX);
DEFINEFINDMINMAX(YCOORD, min, MinY);
DEFINEFINDMINMAX(YCOORD, max, MaxY);

DEFINEROTATE(1, -1, RotateLeft);
DEFINEROTATE(-1, 1, RotateRight);
