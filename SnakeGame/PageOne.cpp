#include "PageOne.h"
#include "GamePage.h"

PageOne::PageOne(wxWindow* parent, wxSimplebook* book, wxWindowID id)
    : wxPanel(parent, id), m_book(book), gamePage(nullptr)
{
    CreateControls();
    SetUpSizers();
    BindEventHandlers();
}

void PageOne::CreateControls()
{
    headlineText = new wxStaticText(this, wxID_ANY, "Select Difficulty");
    headlineText->SetFont(wxFontInfo(36).Bold());

    easyBtn = new wxButton(this, wxID_ANY, "EASY");
    mediumBtn = new wxButton(this, wxID_ANY, "MEDIUM");
    hardBtn = new wxButton(this, wxID_ANY, "HARD");
    backBtn = new wxButton(this, wxID_ANY, "BACK");
}

void PageOne::SetUpSizers()
{
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(headlineText, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 20);

    wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
    btnSizer->Add(easyBtn, 0, wxALL, 10);
    btnSizer->Add(mediumBtn, 0, wxALL, 10);
    btnSizer->Add(hardBtn, 0, wxALL, 10);

    mainSizer->Add(btnSizer, 0, wxALIGN_CENTER);
    mainSizer->AddSpacer(100);
    mainSizer->Add(backBtn, 0, wxALIGN_CENTER | wxTOP, 10);

    SetSizer(mainSizer);
}

void PageOne::BindEventHandlers()
{
    backBtn->Bind(wxEVT_BUTTON, &PageOne::SwitchPage, this);
    easyBtn->Bind(wxEVT_BUTTON, &PageOne::OnSelectDifficulty, this);
    mediumBtn->Bind(wxEVT_BUTTON, &PageOne::OnSelectDifficulty,this);
    hardBtn->Bind(wxEVT_BUTTON, &PageOne::OnSelectDifficulty,this);
}

void PageOne::SwitchPage(wxCommandEvent& evt)
{
    int current = m_book->GetSelection();
    if (evt.GetEventObject() == backBtn && current > 0) {
        m_book->SetSelection(current - 1);
    }
}

void PageOne::OnSelectDifficulty(wxCommandEvent& evt)
{
    wxButton* selectedButton = dynamic_cast<wxButton*>(evt.GetEventObject());
    int speed = 100;

    if (selectedButton == mediumBtn) speed = 70;
    else if (selectedButton == hardBtn) speed = 40;

    if (!gamePage) {
        gamePage = new GamePage(m_book, m_book, speed);
        m_book->AddPage(gamePage, "Game");
    }
    else {
        gamePage->SetSpeed(speed);
    }

    m_book->SetSelection(m_book->GetPageCount() - 1); // Switch to Game Page
    gamePage->StartGame();
}
