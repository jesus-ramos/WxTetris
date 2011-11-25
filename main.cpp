#include "main.hpp"
#include "TetrisGame.hpp"

IMPLEMENT_APP(TetrisApp);

bool TetrisApp::OnInit()
{
    TetrisGame* tetrisGame = new TetrisGame(wxT("WxTetris"));
    tetrisGame->Centre();
    tetrisGame->Show(true);
    
    return true;
}
