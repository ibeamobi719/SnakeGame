// MainFrame.cpp
#include "MainFrame.h"
#include "PageOne.h"
#include "GamePage.h"

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title), gamePage(nullptr)
{
    CreateControls();
    SetUpSizers();
    BindEventHandlers();
}

void MainFrame::CreateControls()
{
    book = new wxSimplebook(this, wxID_ANY);

    home = new wxPanel(book);
    difficultyPage = new PageOne(book, book);

    playButton = new wxButton(home, wxID_ANY, "PLAY");
    wxFont mainFont(wxFontInfo(wxSize(0, 48)).Bold());
    headlineText = new wxStaticText(home, wxID_ANY, "SNAKE GAME");
    headlineText->SetFont(mainFont);

    book->AddPage(home, "Home", true);
    book->AddPage(difficultyPage, "Difficulty", false);
}

void MainFrame::SetUpSizers()
{
    wxBoxSizer* homeSizer = new wxBoxSizer(wxVERTICAL);
    homeSizer->Add(headlineText, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 20);
    homeSizer->Add(playButton, 0, wxALIGN_CENTER | wxBOTTOM, 10);
    home->SetSizer(homeSizer);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(book, 1, wxEXPAND | wxALL, 5);
    SetSizer(mainSizer);
    mainSizer->SetSizeHints(this);
}

void MainFrame::BindEventHandlers()
{
    playButton->Bind(wxEVT_BUTTON, &MainFrame::SwitchPage, this);
    Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainFrame::SwitchPage, this);
}

void MainFrame::SwitchPage(wxCommandEvent& evt)
{
    wxObject* obj = evt.GetEventObject();
    wxString label = dynamic_cast<wxButton*>(obj)->GetLabel();

    if (label == "PLAY") {
        book->SetSelection(1); // Difficulty page
    }
    else if (label == "EASY" || label == "MEDIUM" || label == "HARD") {
        int speed = 100;
        if (label == "MEDIUM") speed = 70;
        if (label == "HARD") speed = 40;

        if (gamePage) {
            book->RemovePage(book->FindPage(gamePage));
            delete gamePage;
        }

        gamePage = new GamePage(book, book, speed);
        book->AddPage(gamePage, "Game", true);
        gamePage->StartGame();
    }
    else if (label == "BACK") {
        int current = book->GetSelection();
        if (current > 0) book->SetSelection(current - 1);
    }
}
