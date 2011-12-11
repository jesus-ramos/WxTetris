#ifndef _BOARD_HPP
#define _BOARD_HPP

#include <wx/wx.h>

#include "Piece.hpp"

#define TIMER_INTERVAL 500

const wxColour colors[] = 
{
    wxColour(0, 0, 0),       wxColour(204, 102, 102),
    wxColour(102, 204, 102), wxColour(102, 102, 204),
    wxColour(204, 204, 102), wxColour(204, 102, 204),
    wxColour(102, 204, 204), wxColour(218, 170, 0)
};

const wxColour light[] = 
{
    wxColour(0, 0, 0),       wxColour(248, 159, 171),
    wxColour(121, 252, 121), wxColour(121, 121, 252),
    wxColour(252, 252, 121), wxColour(252, 121, 252),
    wxColour(121, 252, 252), wxColour(252, 198, 0)
};

const wxColour dark[] = 
{
    wxColour(0, 0, 0),      wxColour(128, 59, 59),
    wxColour(59, 128, 59),  wxColour(59, 59, 128),
    wxColour(128, 128, 59), wxColour(128, 59, 128),
    wxColour(59, 128, 128), wxColour(128, 98, 0)
};


class Board : public wxPanel
{
public:
    Board(wxFrame* parent);
    void Start();
    void Pause();
    void Reset();

    /* wx event handlers */
protected:
    void OnPaint(wxPaintEvent& event);
    void OnKeyDown(wxKeyEvent& event);
    void OnTimer(wxCommandEvent& event);

private:
    /* Little hack to predefine the size */
    enum
    {
        BoardWidth = 11,
        BoardHeight = 22
    };

    PieceShape& PieceAt(int x, int y) { return board[y * BoardWidth + x]; }
    int Width() { return GetClientSize().GetWidth() / BoardWidth; }
    int Height() { return GetClientSize().GetHeight() / BoardHeight; }
    static bool InBounds(int x, int y) { return x >= 0 && x < BoardWidth && y >= 0 && y < BoardHeight; }
    void Clear();
    void DropCurrentToBottom();
    void DropCurrentOneLine();
    void PieceHitBottom();
    void ClearFullLines();
    void MakeNewPiece();
    bool DoMove(const Piece& piece, int newX, int newY);
    void DrawPieceSquare(wxPaintDC& dc, int x, int y, PieceShape shape);

    wxTimer* timer;
    wxStatusBar* statusBar;
    bool started;
    bool paused;
    bool pieceDoneFalling;
    Piece current;
    int curX;
    int curY;
    int score;
    PieceShape board[BoardWidth * BoardHeight];
};

#endif
