#pragma once
#include "wx/wx.h"
#include "Main.h"

class Main;


class App : public wxApp
{
public:
	App();
	~App();

private:
	Main* showMp = nullptr;

public:
	virtual bool OnInit();

};

