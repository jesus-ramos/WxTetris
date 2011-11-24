#ifndef _BOARD_HPP
#define _BOARD_HPP

#include <wx/wx.h>

#include "Piece.hpp"

#define TIMER_INTERVAL 300

class Board : public wxPanel
{
public:
    Board(wxFrame* parent);
    void Start();
    void Pause();

    /* wx event handlers */
protected:
    void OnPaint(wxPaintEvent& event);
    void OnKeyDown(wxKeyEvent& event);
    void OnTimer(wxCommandEvent& event);

private:
    /* Little hack to predefine the size */
    enum
    {
        BoardWidth = 10,
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
    wxStatusBar* status_bar;
    bool started;
    bool paused;
    bool pieceFalling;
    Piece current;
    int curX;
    int curY;
    int score;
    PieceShape board[BoardWidth * BoardHeight];
};

#endif
