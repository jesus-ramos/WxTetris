#include "main.hpp"
#include "TetrisGame.hpp"

#ifdef __WXMAC__
#include <ApplicationServices/ApplicationServices.h>
#endif /* __WXMAC__ */

IMPLEMENT_APP(TetrisApp);

bool TetrisApp::OnInit()
{
#ifdef __WXMAC__
    ProcessSerialNumber psn;
    GetCurrentProcess(&psn);
    TransformProcessType(&psn, kProcessTransformToForegroundApplication);
#endif /* __WXMAC__ */
    TetrisGame* tetrisGame = new TetrisGame(wxT("WxTetris"));
    tetrisGame->Centre();
    tetrisGame->Show(true);
    
    return true;
}
