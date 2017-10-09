//
//  TestApp.cpp
//  Network_Dynamics
//
//  Created by Wojciech Kryscinski on 09/12/14.
//  Copyright (c) 2014 Wojtek. All rights reserved.
//

#include "TestApp.h"
#include "NDMainFrame.h"

BEGIN_EVENT_TABLE ( Simple, wxFrame )
EVT_BUTTON(ON_START,  Simple::onStart)
END_EVENT_TABLE()

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    //Simple *frame = new Simple( "Network Dynamics" );
    //frame->Show( true );
    NDMainFrame* menu = new NDMainFrame(wxT("Network Dynamics Menu"));
    menu->Show();
    
    return true;
}

Simple::Simple(const wxString& title)
: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(1000, 500))
{
    wxPanel *panel = new wxPanel(this, -1);
    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
    
    wxStaticText *nodesCount=new wxStaticText(panel,-1,"Nodes: ");
    
    agentCountCtrl=new wxTextCtrl(panel, -1, "50");
    
    wxStaticText *connectionsCount=new wxStaticText(panel,-1,"Connections: ");
    wxTextCtrl *connectionsCountTxt=new wxTextCtrl(panel,-1,"5");
    
    wxStaticText *maxRandomTxt=new wxStaticText(panel,-1,"MaxRandom: ");

    wxTextCtrl *maxRandomCtrl=new wxTextCtrl(panel,-1,"2");
    
    wxStaticText *ranProbabTxt=new wxStaticText(panel,-1,"Random Probability (%): ");
    
    wxTextCtrl *ranProbabCtrl=new wxTextCtrl(panel,-1,"20");
    
    wxButton *startButton = new wxButton(panel, ON_START, wxT("Start"));
    hbox->Add(new wxPanel(panel, -1));
    
    hbox->Add(nodesCount);
    hbox->Add(agentCountCtrl);
    hbox->Add(connectionsCount);
    hbox->Add(connectionsCountTxt);
    hbox->Add(maxRandomTxt);
    hbox->Add(maxRandomCtrl);
    hbox->Add(ranProbabTxt);
    hbox->Add(ranProbabCtrl);
    hbox->Add(startButton);
    panel->SetSizer(hbox);
    
    Centre();
}

void Simple::onStart(wxCommandEvent& WXUNUSED(event))
{
    //START SIMULATE
    Close(true);
}
