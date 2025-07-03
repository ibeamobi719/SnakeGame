#include "GamePage.h"

constexpr int ID_TIMER = 1001;

GamePage::GamePage(wxWindow* parent, wxSimplebook* book, int speed, wxWindowID id)
    : wxPanel(parent, id), gameSpeed(speed), m_book(book)
{
    CreateControls(speed);
    SetUpSizer();
    BindEventHandlers();
    InitGame();
}

void GamePage::SetSpeed(int ms)
{
    gameSpeed = ms;
    gameTimer->Start(gameSpeed);
}

void GamePage::OnPaint(wxPaintEvent& evt)
{
    wxPaintDC dc(gamePanel);

    dc.SetBrush(*wxRED_BRUSH);
    dc.DrawCircle(food.x, food.y, 10);

    dc.SetBrush(*wxGREEN_BRUSH);
    for (const wxPoint& segment : snake) {
        dc.DrawRectangle(segment.x, segment.y, 10, 10);
    }
}

void GamePage::OnTimer(wxTimerEvent& evt)
{
    wxLogDebug("Timer Tick");
    MoveSnake();
    CheckCollision();
    gamePanel->Refresh();
}

void GamePage::OnKeyDown(wxKeyEvent& evt)
{
    wxPoint newDir = direction;
    int key = evt.GetKeyCode();

    switch (key) {
    case WXK_UP:    
        newDir = wxPoint(0, -1); 
        break;
    case WXK_DOWN:  
        newDir = wxPoint(0, 1);  
        break;
    case WXK_LEFT:  
        newDir = wxPoint(-1, 0); 
        break;
    case WXK_RIGHT: 
        newDir = wxPoint(1, 0);  
        break;
    case WXK_ESCAPE:
        gameTimer->Stop();
        m_book->SetSelection(m_book->GetSelection() - 1);
        return;
    default:
        evt.Skip();
        return;
    }

    if (direction + newDir != wxPoint(0, 0)) {
        direction = newDir;
    }
}

void GamePage::SwitchPage(wxCommandEvent& evt)
{
    if (evt.GetEventObject() == backBtn) {
        gameTimer->Stop();
        int current = m_book->GetSelection();
        if (current > 0) m_book->SetSelection(current - 1);
    }
}

void GamePage::CreateControls(int speed)
{
    food = wxPoint(100, 100);
    direction = wxPoint(1, 0);
    gameTimer = new wxTimer(this, ID_TIMER);
    gamePanel = new wxPanel(this, wxID_ANY);
    backBtn = new wxButton(this, wxID_ANY, "BACK");
}

void GamePage::SetUpSizer()
{
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(gamePanel, 1, wxEXPAND | wxALL, 10);
    mainSizer->Add(backBtn, 0, wxALIGN_RIGHT | wxALL, 10);
    SetSizer(mainSizer);
    Layout();

   
}

void GamePage::BindEventHandlers()
{
    gamePanel->Bind(wxEVT_PAINT, &GamePage::OnPaint, this);
    Bind(wxEVT_TIMER, &GamePage::OnTimer, this, ID_TIMER);
    Bind(wxEVT_KEY_DOWN, &GamePage::OnKeyDown, this);
    backBtn->Bind(wxEVT_BUTTON, &GamePage::SwitchPage, this);

    // Ensure gameplay gets key events 
    SetFocusToGamePanel();

}

void GamePage::InitGame()
{
    snake.clear();
    snake.push_front(wxPoint(50, 50));
    snake.push_front(wxPoint(40, 50));
    snake.push_front(wxPoint(30, 50));
    direction = wxPoint(1, 0);
    SpawnFood();
}

void GamePage::MoveSnake()
{
    wxPoint newHead = snake.front();
    newHead.x += direction.x * 10;
    newHead.y += direction.y * 10;

    wxLogDebug("Moving snake to (%d, %d)", newHead.x, newHead.y); // Debug

    snake.push_front(newHead);
    snake.pop_back();
}

void GamePage::SpawnFood()
{
    food.x = (rand() % 30) * 10;
    food.y = (rand() % 30) * 10;
}

void GamePage::CheckCollision()
{
    wxPoint head = snake.front();
    int panelWidth, panelHeight;
    gamePanel->GetClientSize(&panelWidth, &panelHeight);

    // Make sure snake stays within game screen
    if (head.x < 0 || head.y < 0 || head.x >= panelWidth || head.y >= panelHeight) {
        gameTimer->Stop();
        return;
    }

    // Controlling snake eating 
    if (head == food) {
        snake.push_back(snake.back());
        SpawnFood();
    }

    // Snake colliding with itself 
    for (size_t i = 1; i < snake.size(); ++i) {
        if (head == snake[i]) {
            gameTimer->Stop();
            return;
        }
    }
}

void GamePage::StartGame()
{
    InitGame();
    bool started = gameTimer->Start(gameSpeed);
    if (!started) {
        wxLogError("Failed to start game timer!");
    }
    SetFocusToGamePanel();
}

void GamePage::SetFocusToGamePanel()
{
    if (gamePanel) {
        gamePanel->SetFocus();
        gamePanel->SetFocusFromKbd();
        gamePanel->SetWindowStyleFlag(wxWANTS_CHARS);
    }
}
