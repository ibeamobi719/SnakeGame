// MainFrame.h
#pragma once
#include <wx/wx.h>
#include <wx/simplebook.h>

class GamePage;
class PageOne;

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString& title);

private:
    void CreateControls();
    void SetUpSizers();
    void BindEventHandlers();
    void SwitchPage(wxCommandEvent& evt);

    wxSimplebook* book;
    wxPanel* home;
    wxButton* playButton;
    wxStaticText* headlineText;
    PageOne* difficultyPage;
    GamePage* gamePage;
};