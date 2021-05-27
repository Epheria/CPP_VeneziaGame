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
	bool bflag_Pass = false, bflag_Die = false, bGameOver = false, bNextStage = false;
	bool bInputCheck = true;
	int iDrawClock = clock();
	int iMoveClock = clock();
	int iCompareClock = clock();
	int iBlindTime = clock();
	int iStopTime = clock();
	char ch;
	int iAllClear = 0;
	string input;
	vector<Word> tmp;

	system("cls");

	SKY_BLUE
		InterfaceManager.BoxDraw(START_X, START_Y, WIDTH, HEIGHT - 3);
	ShowPlayerStatus();
	InterfaceManager.gotoxy(WIDTH - 6, HEIGHT / 2);
	cout << "☆ " << iStage << " Stage ☆";
	Sleep(1000);
	InterfaceManager.BoxErase(WIDTH, HEIGHT / 2);
	InterfaceManager.DrawMidText("                   ", WIDTH, HEIGHT / 2);

	InterfaceManager.BoxDraw(WIDTH, HEIGHT / 2 + 4, 14, 5);
	while (1)
	{
		if (!input.empty())
		{
			BLUE
				InterfaceManager.DrawMidText(input, WIDTH, HEIGHT / 2 + 6);
		}
		if (_kbhit())
		{
			InterfaceManager.gotoxy(WIDTH - 4, HEIGHT / 2 + 6);

			if (bInputCheck == true)
			{
				ch = _getch();
				if (ch == KEY_ENTER)
				{
					bflag_Die = m_WordManager.DieCheck(tmp, input, iAllClear);
					if (bflag_Die == true)
					{
						bNextStage = m_Player.AddScore(iAllClear);
						iAllClear = 0;
						bInputCheck = true;
						if (bNextStage == true)
						{
							return iStage += 1;
						}
					}
					else
					{
						bInputCheck = false;
					}
					InterfaceManager.ErasePoint(WIDTH - 4, HEIGHT / 2 + 6, input);
					input.clear();
				}
				else if (ch == KEY_BACKSPACE)
				{
					InterfaceManager.ErasePoint(WIDTH - 4, HEIGHT / 2 + 6, input);
					if (!input.empty())
						input.pop_back();
					InterfaceManager.gotoxy(WIDTH - 4, HEIGHT / 2 + 6);
					BLUE
						InterfaceManager.DrawMidText(input, WIDTH, HEIGHT / 2 + 6);
				}
				else
				{
					if(input.length() <= 20)
						input += ch;
					BLUE
						InterfaceManager.DrawMidText(input, WIDTH, HEIGHT / 2 + 6);
				}
				iCompareClock = clock();
			}
		}
		if (bInputCheck == false)
		{
			RED
				InterfaceManager.DrawMidText("Failed compare!", WIDTH, HEIGHT / 2 + 6);
			if (clock() - iCompareClock >= COMPARE_TIME + 2000)
			{
				InterfaceManager.ErasePoint(WIDTH, HEIGHT / 2 + 6, "Failed compare!");
				iCompareClock = clock();
				bInputCheck = true;
			}
		}
		if (clock() - iBlindTime >= ITEM_BLINDTIME)
		{
			m_WordManager.SetBlind(false);
			iBlindTime = clock();
		}
		if (clock() - iStopTime >= ITEM_STOPTIME)
		{
			m_WordManager.SetStop(false);
			iStopTime = clock();
		}
		if (clock() - iDrawClock >= DRAW_SPEED - m_WordManager.SetDifficulty(iStage))
		{
			m_WordManager.CreateWord(tmp, iStopTime);
			iDrawClock = clock();
		}
		if (clock() - iMoveClock >= DROP_SPEED - m_WordManager.SetDifficulty(iStage))
		{
			m_WordManager.DropWord(tmp, iStopTime);
			bflag_Pass = m_WordManager.PassCheck(tmp);
			if (bflag_Pass == true)
			{
				bGameOver = m_Player.DamageLife();
				InterfaceManager.DrawPoint("                         ", 1, HEIGHT - 3);
				if (bGameOver == true)
				{
					m_RankManager.SaveRank(m_Player, iStage);
					system("cls");
					SKY_BLUE
						InterfaceManager.BoxDraw(START_X, START_Y, WIDTH, HEIGHT - 3);
					RED
						InterfaceManager.DrawMidText("☆ Game Over ☆", WIDTH, HEIGHT / 2);
					char tmpCh = _getch();
					m_Player.InitScore();
					m_Player.InitLife();
					return 0;
				}
			}
			iMoveClock = clock();
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
		InterfaceManager.BoxDraw(START_X, START_Y, WIDTH, HEIGHT - 3);
	ShowPlayerStatus();
	InterfaceManager.BoxDraw(WIDTH, HEIGHT / 2 + 4, 10, 5);
	InterfaceManager.DrawMidText("Skip : s", WIDTH, HEIGHT / 2 + 6);
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
					InterfaceManager.ErasePoint(WIDTH, iHeight, tmp[i -1]);
					InterfaceManager.DrawMidText(tmp[i], WIDTH, iHeight++);
				}
			}
			else
			{
				InterfaceManager.DrawMidText(tmp[i], WIDTH, iHeight++);
			}
			iCur++;
		}
	}

	fLoad.close();
}

void GameManager::SetPlayerName()
{
	string name;

	InterfaceManager.BoxErase(WIDTH, HEIGHT / 2 + 10);
	InterfaceManager.DrawMidText("이름 입력", WIDTH, HEIGHT / 2 + 2);
	InterfaceManager.BoxDraw(WIDTH, HEIGHT / 2 + 4, 10, 5);
	InterfaceManager.gotoxy(WIDTH - 2, HEIGHT / 2 + 6);
	cin >> name;
	m_Player.SetName(name);
	InterfaceManager.BoxErase(WIDTH, HEIGHT / 2 + 10);
}

void GameManager::ShowRank()
{
	m_RankManager.LoadRank(m_Player);
}

GameManager::~GameManager()
{
}