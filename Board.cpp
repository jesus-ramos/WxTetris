#include "Board.hpp"

Board::Board(wxFrame* parent) :
    wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
{
    timer = new wxTimer(this, 1);
    status_bar = parent->GetStatusBar();
    pieceFalling = true;
    started = false;
    paused = false;
    score = 0;
    curX = 0;
    curY = 0;
    
    Clear();

    Connect(wxEVT_PAINT, wxPaintEventHandler(Board::OnPaint));
    Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(Board::OnKeyDown));
    Connect(wxEVT_TIMER, wxCommandEventHandler(Board::OnTimer));
}

void Board::Start()
{
    if (paused)
        return;

    started = true;
    pieceFalling = true;
    score = 0;

    Clear();

    MakeNewPiece();
    timer->Start(TIMER_INTERVAL);
}

void Board::Pause()
{
    if (!started)
        return;

    paused = !paused;
    
    if (paused)
    {
        timer->Stop();
        status_bar->SetStatusText(wxT("Game Paused"));
    }
    else
    {
        timer->Start(TIMER_INTERVAL);
        wxString str;
        str.Printf(wxT("Score: %d"), score);
        status_bar->SetStatusText(str);
    }
    Refresh();
}

void Board::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);

    wxSize size = GetClientSize();
    int top = size.GetHeight() - BoardHeight * Height();

    for (int i = 0; i < BoardHeight; i++)
        for (int j = 0; j < BoardWidth; j++)
        {
            PieceShape pieceShape = PieceAt(j, BoardHeight - j - 1);
            if (pieceShape == None)
                continue;
            DrawPieceSquare(dc, j * Width(), top + i * Height(),
                            pieceShape);
        }

    if (current.GetShape() == None)
        return;

    for (int i = 0; i < 4; i++)
    {
        int x = curX + current.x(i);
        int y = curY - current.y(i);
        DrawPieceSquare(dc, x * Width(),
                        top + (BoardHeight - y - 1) * Height(),
                        current.GetShape());
    }
}

void Board::OnKeyDown(wxKeyEvent& event)
{
    if (!started || current.GetShape() == None)
    {
        event.Skip();
        return;
    }

    int keyCode = event.GetKeyCode();

    if (keyCode == 'p')
    {
        Pause();
        return;
    }

    if (paused)
        return;

    switch (keyCode)
    {
        case WXK_SPACE:
            DropCurrentToBottom();
            break;
        case WXK_UP:
            DoMove(current.RotateLeft(), curX, curY);
            break;
        case WXK_DOWN:
            DoMove(current.RotateRight(), curX, curY);
            break;
        case WXK_LEFT:
            DoMove(current, curX - 1, curY);
            break;
        case WXK_RIGHT:
            DoMove(current, curX + 1, curY);
            break;
        default:
            event.Skip();
    }
}

void Board::OnTimer(wxCommandEvent& event)
{
    if (pieceFalling)
        DropCurrentOneLine();
    else
    {
        MakeNewPiece();
        pieceFalling = true;
    }
}

void Board::Clear()
{
    for (int i = 0; i < BoardHeight * BoardWidth; i++)
        board[i] = None;
}

void Board::DropCurrentToBottom()
{
    int y = curY;
    while (y)
    {
        if (!DoMove(current, curX, y - 1))
            break;
        y--;
    }
    PieceHitBottom();
}

void Board::DropCurrentOneLine()
{
    if (!DoMove(current, curX, curY - 1))
        PieceHitBottom();
}

void Board::PieceHitBottom()
{
    for (int i = 0; i < 4; i++)
    {
        int x = curX + current.x(i);
        int y = curY - current.y(i);
        PieceAt(x, y) = current.GetShape();
    }
    ClearFullLines();
    pieceFalling = false;
    MakeNewPiece();
}

void Board::ClearFullLines()
{
    int lines = 0;

    for (int i = BoardHeight - 1; i >= 0; i--)
    {
        bool lineFull = true;
        for (int j = 0; j < BoardWidth; j++)
            if (PieceAt(i, j) == None)
            {
                lineFull = false;
                break;
            }

        if (!lineFull)
            continue;

        lines++;
        for (int j = i; j < BoardHeight - 1; j++)
            for (int k = 0; k < BoardWidth; k++)
                PieceAt(j, k) = PieceAt(j, k + 1);
    }

    if (!lines)
        return;

    score += lines;
    wxString str;
    str.Printf(wxT("Score: %d"), score);
    status_bar->SetStatusText(str);

    pieceFalling = false;
    current.SetShape(None);
    Refresh();
}

void Board::MakeNewPiece()
{
    current.SetRandomShape();
    curX = BoardWidth / 2 + 1;
    curY = BoardHeight - 1 + current.MinY();

    if (!DoMove(current, curX, curY))
    {
        current.SetShape(None);
        timer->Stop();
        started = false;
        status_bar->SetStatusText(wxT("You Lose :("));
    }
}

bool Board::DoMove(const Piece& piece, int newX, int newY)
{
    for (int i = 0; i < 4; i++)
    {
        int x = newX + piece.x(i);
        int y = newY - piece.y(i);

        if (!InBounds(x, y) || PieceAt(x, y) != None)
            return false;
    }

    current = piece;
    curX = newX;
    curY = newY;
    
    Refresh();

    return true;
}
