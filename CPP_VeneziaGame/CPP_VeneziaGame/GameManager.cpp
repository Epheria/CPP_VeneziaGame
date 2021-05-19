#include "GameManager.h"

GameManager::GameManager()
{
}

void GameManager::ShowMenu()
{
	int iSelect;

	while (1)
	{
		system("cls");
		SKY_BLUE
		InterfaceManager.BoxDraw(START_X, START_Y, WIDTH, HEIGHT - 5);
		BLUE
			InterfaceManager.DrawMidText("☆ ★ 베 네 치 아 ★ ☆", WIDTH, HEIGHT / 2 - 4 );
			InterfaceManager.DrawMidText("1.Game Start", WIDTH, HEIGHT / 2 - 1 );
			InterfaceManager.DrawMidText("2.Rank", WIDTH, HEIGHT / 2 + 2 );
			InterfaceManager.DrawMidText("3.Exit", WIDTH, HEIGHT / 2 + 5 );
			ShowPlayerStatus();
			iSelect = InterfaceManager.MenuSelectCursor(3, 3, WIDTH / 3, HEIGHT / 2 - 1);

			switch (iSelect)
			{
			case 1:
				PlayGame();
				break;
			case 2:
				break;
			case 3:
				return;
			}
	}
}

void GameManager::ShowPlayerStatus()
{
	m_Player.ShowPlayerLife();
	m_Player.ShowPlayerScore();
	m_Player.ShowPlayerName();
}

void GameManager::PlayGame()
{
	system("cls");
	SKY_BLUE
	InterfaceManager.BoxDraw(START_X, START_Y, WIDTH, HEIGHT - 5);
	ShowPlayerStatus();
	InterfaceManager.DrawMidText("이름 입력 : ", WIDTH, HEIGHT / 2 + 2);
	InterfaceManager.BoxDraw(WIDTH, HEIGHT / 2 + 4, 10, 4);
	BLUE
		LoadStory();
}

void GameManager::LoadStory()
{
	ifstream fLoad;
	int iLine, iHeight = HEIGHT / 2 -8;
	string buf;
	vector<string> tmp;

	fLoad.open("veneziaStory.txt");

	if (fLoad.is_open())
	{
		fLoad >> iLine;
		for (int i = 0; i < iLine; i++)
		{
			getline(fLoad, buf);
			tmp.push_back(buf);
		}

		for (int i = 0; i < iLine - MAX_LINE; i++)
		{
			iHeight = HEIGHT / 2 - 8;
			InterfaceManager.gotoxy(WIDTH, HEIGHT / 2 - 8);
			for (int j = i; i < MAX_LINE; j++)
			{
				InterfaceManager.gotoxy(WIDTH, iHeight++);
				Sleep(500);
				cout << tmp[j];
			}
		}
	}

	fLoad.close();
}

GameManager::~GameManager()
{
}