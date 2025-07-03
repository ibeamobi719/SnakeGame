#pragma once
#include <wx/wx.h>
#include <wx/simplebook.h>
#include "GamePage.h"

class PageOne : public wxPanel
{
public:
    PageOne(wxWindow* parent, wxSimplebook* book, wxWindowID id = wxID_ANY);

private:
    void CreateControls();
    void SetUpSizers();
    void BindEventHandlers();
    void SwitchPage(wxCommandEvent& evt);
    void OnSelectDifficulty(wxCommandEvent& evt);

    wxStaticText* headlineText;
    wxButton* easyBtn;
    wxButton* mediumBtn;
    wxButton* hardBtn;
    wxButton* backBtn;
    GamePage* gamePage;
    wxSimplebook* m_book;
};