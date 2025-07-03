#pragma once

#include <wx/wx.h>
#include <wx/simplebook.h>
#include <deque>

class GamePage : public wxPanel
{
public:
    GamePage(wxWindow* parent, wxSimplebook* book, int speed, wxWindowID id = wxID_ANY);

    void StartGame();
    void SetSpeed(int ms);

private:
    // Game state
    std::deque<wxPoint> snake;
    wxPoint food;
    wxPoint direction;
    int gameSpeed;

    // GUI Elements
    wxSimplebook* m_book;
    wxTimer* gameTimer;
    wxPanel* gamePanel;
    wxButton* backBtn;

    // Game logic
    void InitGame();
    void MoveSnake();
    void SpawnFood();
    void CheckCollision();

    // UI setup
    void CreateControls(int speed);
    void SetUpSizer();
    void BindEventHandlers();
    void SetFocusToGamePanel();

    // Event handlers
    void OnPaint(wxPaintEvent& evt);
    void OnTimer(wxTimerEvent& evt);
    void OnKeyDown(wxKeyEvent& evt);
    void SwitchPage(wxCommandEvent& evt);
};
