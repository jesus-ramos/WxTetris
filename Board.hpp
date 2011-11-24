#ifndef _BOARD_HPP
#define _BOARD_HPP

#include <wx/wx.h>

#include "Piece.hpp"

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
    int Width() { return GetClientSize().GetWidth() / BoardWidth };
    int Height() { return GetClientSize().GetHeight / BoardHeight };
    void Clear();
    void DropCurrentToBottom();
    void DropCurrentOneLine();
    void PieceHitBottom();
    void ClearFullLines();
    void MakeNewPiece();
    bool DoMove(const Piece& piece, int newX, int newY);
    void DrawShape(wxPaintDC& dc, int x, int y, PieceShape shape);

    const int BoardWidth = 10;
    const int BoardHeight = 22;

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
