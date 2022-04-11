#pragma once
#include "wx/wx.h"


class Main : public wxFrame
{
public:
	Main();
	~Main();

public:
	int nWidth = 10;
	int nHeight = 10;
	wxButton** btn;
	int* nField = nullptr;
	bool FirstClick = true;

	void OnButtonClicked(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();

};



