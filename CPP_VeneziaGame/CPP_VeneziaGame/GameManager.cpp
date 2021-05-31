#include "GameManager.h"

GameManager::GameManager()
{
}

void GameManager::ShowMenu()
{
	int iSelect;
	m_WordManager.LoadFile();

	while (1)
	{
		system("cls");
		SKY_BLUE
			Interface::BoxDraw(START_X, START_Y, WIDTH, HEIGHT - 5);
		BLUE
			Interface::DrawMidText("☆ ★ 베 네 치 아 ★ ☆", WIDTH, HEIGHT / 2 - 4 );
		Interface::DrawMidText("1.Game Start", WIDTH, HEIGHT / 2 - 1 );
		Interface::DrawMidText("2.Rank", WIDTH, HEIGHT / 2 + 2 );
		Interface::DrawMidText("3.Exit", WIDTH, HEIGHT / 2 + 5 );
			ShowPlayerStatus();
			iSelect = Interface::MenuSelectCursor(3, 3, WIDTH / 3, HEIGHT / 2 - 1);

			switch (iSelect)
			{
			case 1:
				PlayGame();
				break;
			case 2:
				ShowRank();
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
	int iStage = 1;

	LoadStory();
	SetPlayerName();

	while (1)
	{
		iStage = Stage(iStage);
		m_WordManager.InitItemStatus();
		if (iStage == 0 || iStage == 6)
		{
			return;
		}
	}	
}

int GameManager::Stage(int iStage)
{
	bool bflag_Pass = false, bGameOver = false, bflag_Die = false, bNextStage = false;
	int iDrawClock = clock();
	int iMoveClock = clock();
	int iBlindTime = clock();
	int iStopTime = clock();
	int iAllClear = 0;
	vector<Word> tmp;

	system("cls");

	SKY_BLUE
		Interface::BoxDraw(START_X, START_Y, WIDTH, HEIGHT - 3);
	ShowPlayerStatus();
	Interface::gotoxy(WIDTH - 6, HEIGHT / 2);
	cout << "☆ " << iStage << " Stage ☆";
	Sleep(1000);
	Interface::BoxErase(WIDTH, HEIGHT / 2);
	Interface::DrawMidText("                   ", WIDTH, HEIGHT / 2);

	Interface::BoxDraw(WIDTH, HEIGHT / 2 + 4, 14, 5);
	while (1)
	{
		if (m_Player.KeyInput() == true)
		{
			bflag_Die = m_WordManager.DieCheck(tmp, m_Player.GetInput(), iAllClear);
			if (bflag_Die == true)
			{
				bNextStage = m_Player.AddScore(iAllClear);
				iAllClear = 0;
				m_Player.InitInput();
				if (bNextStage == true)
					return iStage += 1;
			}
			else
			{
				m_Player.SetInputCheck();
				m_Player.InitInput();
			}
		}
		m_Player.CheckInput();

		m_WordManager.CreateWord(tmp, iStage);
		m_WordManager.DropWord(tmp, iStage);
		m_WordManager.StopCheck();
		m_WordManager.BlindCheck();
		
		bflag_Pass = m_WordManager.PassCheck(tmp);
		if (bflag_Pass == true)
		{
			bGameOver = m_Player.DamageLife();
			Interface::DrawPoint("                         ", 1, HEIGHT - 3);
			if (bGameOver == true)
			{
				m_RankManager.SaveRank(m_Player, iStage);
				system("cls");
				SKY_BLUE
					Interface::BoxDraw(START_X, START_Y, WIDTH, HEIGHT - 3);
				RED
					Interface::DrawMidText("☆ Game Over ☆", WIDTH, HEIGHT / 2);
				char tmpCh = _getch();
				m_Player.InitScore();
				m_Player.InitLife();
				return 0;
			}
		}
		ShowPlayerStatus();
	}
}

void GameManager::LoadStory()
{
	ifstream fLoad;
	char ch;
	int iLine, iCur = 0,iHeight = HEIGHT / 2 -8;
	string buf;
	vector<string> tmp;

	system("cls");
	SKY_BLUE
		Interface::BoxDraw(START_X, START_Y, WIDTH, HEIGHT - 3);
	ShowPlayerStatus();
	Interface::BoxDraw(WIDTH, HEIGHT / 2 + 4, 10, 5);
	Interface::DrawMidText("Skip : s", WIDTH, HEIGHT / 2 + 6);
	BLUE

	fLoad.open("veneziaStory.txt");

	if (fLoad.is_open())
	{
		fLoad >> iLine;
		for (int i = 0; i < iLine; i++)
		{
			getline(fLoad, buf);
			tmp.push_back(buf);
		}

		for (int i = 0; i < iLine; i++)
		{
			if (_kbhit())
			{
				ch = _getch();
				switch (ch)
				{
				case KEY_SKIP:
					return;
				}
			}
			Sleep(500);
			if (iCur >= 10 && iCur != 0)
			{
				iHeight = HEIGHT / 2 - 8;
				for (int i = iCur - MAX_LINE + 1; i < iCur + 1; i++)
				{
					Interface::ErasePoint(WIDTH, iHeight, tmp[i -1]);
					Interface::DrawMidText(tmp[i], WIDTH, iHeight++);
				}
			}
			else
			{
				Interface::DrawMidText(tmp[i], WIDTH, iHeight++);
			}
			iCur++;
		}
	}

	fLoad.close();
}

void GameManager::SetPlayerName()
{
	string name;
	char ch;
	
	Interface::BoxErase(WIDTH, HEIGHT / 2 + 10);
	Interface::DrawMidText("이름 입력", WIDTH, HEIGHT / 2 + 2);
	Interface::BoxDraw(WIDTH, HEIGHT / 2 + 4, 10, 5);
	Interface::gotoxy(WIDTH, HEIGHT / 2 + 6);

	while (1)
	{
			if (_kbhit())
			{
				ch = _getch();

				if (ch == KEY_ENTER)
				{
					Interface::ErasePoint(WIDTH, HEIGHT / 2 + 6, name);
					m_Player.SetName(name);
					return;
				}
				else if (ch == KEY_BACKSPACE)
				{
					Interface::ErasePoint(WIDTH, HEIGHT / 2 + 6, name);
					if (!name.empty())
						name.pop_back();
				}
				else
				{
					if (name.length() <= 14)
						name += ch;
					Interface::ErasePoint(WIDTH, HEIGHT / 2 + 6, name);
				}
			Interface::DrawMidText(name, WIDTH, HEIGHT / 2 + 6);
			}
	}
	Interface::BoxErase(WIDTH, HEIGHT / 2 + 10);
}

void GameManager::ShowRank()
{
	m_RankManager.LoadRank(m_Player);
}

GameManager::~GameManager()
{
}