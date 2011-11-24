#include "TetrisGame.hpp"
#include "Board.hpp"

TetrisGame::TetrisGame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(180, 380))
{
    /* Set status bar to contain the current game score */
    wxStatusBar *statusBar = CreateStatusBar();
    statusBar->SetStatusText(wxT("0"));

    Board* board = new Board(this);
    board->SetFocus();
    board->Start();

    /* New seed for random number gen for random tiles */
    srand(time(NULL));
}
