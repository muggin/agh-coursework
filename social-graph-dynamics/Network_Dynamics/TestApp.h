//
//  TestApp.h
//  Network_Dynamics
//
//  Created by Wojciech Kryscinski on 09/12/14.
//  Copyright (c) 2014 Wojtek. All rights reserved.
//

#ifndef __Network_Dynamics__TestApp__
#define __Network_Dynamics__TestApp__

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
class MyApp: public wxApp
{
public:
    virtual bool OnInit();
};


class Simple : public wxFrame
{
    wxTextCtrl *agentCountCtrl;
    wxTextCtrl *randomFactor;
public:
    Simple(const wxString& title);
    void onStart(wxCommandEvent& event);
    DECLARE_EVENT_TABLE()
    
};

enum
{
    ON_START = wxID_HIGHEST + 1, // declares an id which will be used to call our button
};

#endif /* defined(__Network_Dynamics__TestApp__) */
