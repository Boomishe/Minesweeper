#include "Main.h"

wxBEGIN_EVENT_TABLE(Main, wxFrame)

wxEND_EVENT_TABLE()


Main::Main() : wxFrame(nullptr, wxID_ANY, "Main", wxPoint(30, 30), wxSize(800, 600))
{
	btn = new wxButton * [nWidth * nHeight];
	wxGridSizer* grid = new wxGridSizer(nWidth, nHeight, 0, 0);

	nField = new int[nWidth * nHeight];

	wxFont font(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);

	SetBackgroundColour(wxColour(115, 69, 183));


	for (int x = 0; x < nWidth; x++)
	{
		for (int y = 0; y < nHeight; y++)
		{
			btn[y * nWidth + x] = new wxButton(this, 10000 + (y * nWidth + x));
			btn[y * nWidth + x]->SetFont(font);
			btn[y * nWidth + x]->SetBackgroundColour(wxColour(200, 200, 150));
			grid->Add(btn[y * nWidth + x], 1, wxEXPAND | wxALL);

			btn[y * nWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Main::OnButtonClicked, this);
			nField[y * nWidth + x] = 0;
		}
	}
	this->SetSizer(grid);
	grid->Layout();

}

Main::~Main()
{
	delete[]btn;
}

void Main::OnButtonClicked(wxCommandEvent& evt)
{
	int x = (evt.GetId() - 10000) % nWidth;
	int y = (evt.GetId() - 10000) / nHeight;

	if (FirstClick)
	{
		int mines = 30;

		while (mines)
		{
			int rx = rand() % nWidth;
			int ry = rand() % nHeight;

			if (nField[ry * nWidth + rx] == 0 && rx != x && ry != y)
			{
				nField[ry * nWidth + rx] = -1;
				mines--;
			}
		}

		FirstClick = false;

	}

	btn[y * nWidth + x]->Enable(false);

	if (nField[y * nWidth + x] == -1)
	{
		wxMessageBox("Boom your dead:(");

		FirstClick = true;
		for (int x = 0; x < nWidth; x++)
			for (int y = 0; y < nHeight; y++)
			{
				nField[y * nWidth + x] = 0;
				btn[y * nWidth + x]->SetLabel("");
				btn[y * nWidth + x]->Enable(true);

			}
	}
	else
	{
		int mine_count = 0;
		for (int i = -1; i < 2; i++)
			for (int j = -1; j < 2; j++)
			{
				if (x + i >= 0 && x + i < nWidth && y + j >= 0 && y + j < nHeight)
				{
					if (nField[(y + j) * nWidth + (x + i)] == -1)
						mine_count++;
				}
			}

		if (mine_count > 0)
		{
			btn[y * nWidth + x]->SetLabel(std::to_string(mine_count));
		}

	}

	evt.Skip();


}
