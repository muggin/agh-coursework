//
//  NDMainFrame.cpp
//  Network_Dynamics
//
//  Created by Wojciech Kryscinski on 13/12/14.
//  Copyright (c) 2014 Wojtek. All rights reserved.
//

#include "NDMainFrame.h"

NDMainFrame::NDMainFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(420, 800)) {
    
    CreateStatusBar(3);
    SetStatusText(wxT("Ready"), 0);
    
    this->menuBar = new wxMenuBar();
    
    // File Menu
    this->fileMenu = new wxMenu();
    this->fileMenu->Append(wxID_AUTHORS, wxT("Autorzy"), wxT("Pokaż informacje o autorach"));
    this->fileMenu->AppendSeparator();
    this->fileMenu->Append(wxID_QUIT, wxT("Zakończ"), wxT("Zakończ działanie programu"));
    
    menuBar->Append(this->fileMenu, wxT("Menu"));
    SetMenuBar(menuBar);

    initOutterPanels();
    initButtons();
    Layout();
    Centre();
}

BEGIN_EVENT_TABLE(NDMainFrame, wxFrame)
    EVT_MENU(wxID_AUTHORS, NDMainFrame::OnAbout)
    EVT_MENU(wxID_QUIT,  NDMainFrame::OnQuit)
    EVT_BUTTON(wxID_RUN_BUTTON,  NDMainFrame::onRun)
END_EVENT_TABLE()

void NDMainFrame::initOutterPanels() {
    wxBoxSizer* verticalSizer = new wxBoxSizer(wxVERTICAL);
    
    // Left Panel Setup
    this->statsPanel = new wxPanel(this, wxID_GRAPH_PANEL);
    this->statsPanel->SetBackgroundColour(wxColour(120, 120, 120));
    
    
    // Right Panel Setup
    this->histogramPanel = new SimpleHistogram(this, wxID_HISTOGRAM_PANEL);
    this->commandPanel = new wxPanel(this, wxID_COMMAND_PANEL);
    this->histogramPanel->SetBackgroundColour(wxColour(166, 166, 166));
    this->commandPanel->SetBackgroundColour(wxColour(166, 166, 166));
    
    verticalSizer->Add(histogramPanel, 4, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 5);
    verticalSizer->Add(statsPanel, 2, wxEXPAND | wxLEFT | wxRIGHT, 5);
    verticalSizer->Add(commandPanel, 1, wxEXPAND | wxBOTTOM | wxLEFT | wxRIGHT, 5);
    
    this->SetSizer(verticalSizer);
}

void NDMainFrame::initButtons() {
    wxGridSizer* verticalSizer = new wxGridSizer(8, 2, 3, 3);
    
    // Section Header Setup
    verticalSizer->Add(new wxStaticText(this->commandPanel, -1, "Initial settings: "), 0, wxTOP | wxLEFT, 25);
    verticalSizer->Add(new wxStaticText(this, -1, wxT("")), 0);
    
    // Agent Count Control Setup
    wxStaticText* nodesCount = new wxStaticText(this->commandPanel, -1, "Nodes: ");
    this->agentCountCtrl = new wxSpinCtrl(this->commandPanel, -1, "Set field", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 150, 10000, 2500);
    verticalSizer->Add(nodesCount, 0, wxLEFT, 25);
    verticalSizer->Add(this->agentCountCtrl, 0, wxRIGHT, 25);
    
    // Connection Count Control Setup
    wxStaticText* connectionsCount = new wxStaticText(this->commandPanel, -1, "Connections: ");
    this->connectionCountCtrl = new wxSpinCtrl(this->commandPanel, -1, "Set field", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 150, 50);
    verticalSizer->Add(connectionsCount, 0, wxLEFT, 25);
    verticalSizer->Add(this->connectionCountCtrl, 0, wxRIGHT, 25);
    
    // Random Connection Count Control Setup
    wxStaticText* randConnectionsCount = new wxStaticText(this->commandPanel, -1, "Random connections: ");
    this->maxRandomCtrl = new wxSpinCtrl(this->commandPanel, -1, "Set field", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 50, 25);
    verticalSizer->Add(randConnectionsCount, 0, wxLEFT, 25);
    verticalSizer->Add(this->maxRandomCtrl, 0, wxRIGHT, 25);
    
    // Random Probability Control Setup
    wxStaticText* randomProbCount = new wxStaticText(this->commandPanel, -1, "Random probability: ");
    this->randomProbCtrl = new wxSpinCtrl(this->commandPanel, -1, "Set field", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 10);
    verticalSizer->Add(randomProbCount, 0, wxLEFT, 25);
    verticalSizer->Add(this->randomProbCtrl, 0, wxRIGHT, 25);
    
    // Graph Plot Checkbox Setup
    //wxStaticText* randomProbCount = new wxStaticText(this->commandPanel, -1, "Random probability: ");
    this->printGraphChBox = new wxCheckBox(this->commandPanel, -1, "Print Graph");
    verticalSizer->Add(this->printGraphChBox, 0, wxLEFT, 25);
    verticalSizer->Add(new wxStaticText(this, -1, wxT("")), 0);
    
    // Run Button Setup
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxVERTICAL);
    this->runButton = new wxButton(this->commandPanel, wxID_RUN_BUTTON, wxT("Run"));
    buttonSizer->Add(runButton, 0);
    verticalSizer->Add(buttonSizer, 0, wxLEFT, 25);
    verticalSizer->Add(new wxStaticText(this, -1, wxT("")), 0);
    
    this->commandPanel->SetSizer(verticalSizer);
    Centre();
}

void NDMainFrame::onRun(wxCommandEvent& event){
    SocialNetworkGraph mGraph;
    SocialNetworkAlgorithm mAlgorithm(mGraph);
    mGraph.generateSmallWorldSocialGraph(900, 100, 1, 10);
    for(int i=0;i<50;i++){
    mGraph.socialNetworkStatistics.calculateStatistics();
    std::map<unsigned long, int> mMap=mGraph.socialNetworkStatistics.getHistogram();
    std::vector <double> v;
    for( std::map<unsigned long, int>::iterator it = mMap.begin(); it != mMap.end(); ++it ) {
        v.push_back(it->second );
    }
    histogramPanel->SetData(v);
    histogramPanel->Refresh();
    histogramPanel->Update();
        mAlgorithm.makeMove(0.01, 2, 1);
        mAlgorithm.makeMove(0.1, 2, 1);
    }
    
}

void NDMainFrame::OnAbout(wxCommandEvent& event) {
    wxMessageBox("Aleksander Wójcik\nFilip Pasternak\nWojciech Kryściński", "Twórcy aplikacji", wxOK | wxICON_INFORMATION);
}

void NDMainFrame::OnQuit(wxCommandEvent& event) {
    Close(true);
}