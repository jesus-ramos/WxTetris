#include "Board.hpp"

Board::Board(wxFrame* parent) :
    wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
{
    timer = new wxTimer(this, 1);
    status_bar = parent->GetStatusBar();
    pieceDoneFalling = false;
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
    pieceDoneFalling = false;
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
            PieceShape pieceShape = PieceAt(j, BoardHeight - i - 1);
            if (pieceShape == None)
                continue;
            DrawPieceSquare(dc, j * Width(), top + i * Height(), pieceShape);
        }

    if (current.GetShape() == None)
        return;

    for (int i = 0; i < 4; i++)
    {
        int x = curX + current.x(i);
        int y = curY - current.y(i);
        DrawPieceSquare(dc, x * Width(), top + (BoardHeight - y - 1) * Height(),
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

    if (keyCode == 'p' || keyCode == 'P')
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
    if (pieceDoneFalling)
    {
        pieceDoneFalling = false;
        MakeNewPiece();
    }
    else
        DropCurrentOneLine();
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
        if (!DoMove(current, curX, --y))
            break;
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
    if (!pieceDoneFalling)
        MakeNewPiece();
}

void Board::ClearFullLines()
{
    int lines = 0;

    for (int i = BoardHeight - 1; i >= 0; i--)
    {
        bool lineFull = true;
        for (int j = 0; j < BoardWidth; j++)
            if (PieceAt(j, i) == None)
            {
                lineFull = false;
                break;
            }

        if (!lineFull)
            continue;

        lines++;
        for (int j = i; j < BoardHeight - 1; j++)
            for (int k = 0; k < BoardWidth; k++)
                PieceAt(k, j) = PieceAt(k, j + 1);
    }

    if (!lines)
        return;

    score += lines;
    wxString str;
    str.Printf(wxT("Score: %d"), score);
    status_bar->SetStatusText(str);

    pieceDoneFalling = true;
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

void Board::DrawPieceSquare(wxPaintDC& dc, int x, int y, PieceShape pieceShape)
{
    wxPen lightPen(light[int(pieceShape)]);
    lightPen.SetCap(wxCAP_PROJECTING);
    dc.SetPen(lightPen);

    dc.DrawLine(x, y + Height() - 1, x, y);
    dc.DrawLine(x, y, x + Width() - 1, y);

    wxPen darkPen(dark[int(pieceShape)]);
    darkPen.SetCap(wxCAP_PROJECTING);
    dc.SetPen(darkPen);

    dc.DrawLine(x + 1, y + Height() - 1, x + Width() - 1, y + Height() - 1);
    dc.DrawLine(x + Width() - 1, y + Height() - 1, x + Width() - 1, y + 1);

    dc.SetPen(*wxTRANSPARENT_PEN);
    dc.SetBrush(wxBrush(colors[int(pieceShape)]));
    
    dc.DrawRectangle(x + 1, y + 1, Width() - 2, Height() - 2);
}
