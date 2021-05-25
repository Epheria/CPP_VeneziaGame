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

		if (iStage == 5)
		{
			m_RankManager.SaveRank(m_Player, iStage);
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
	char ch;
	string input;
	vector<Word> tmp;

	system("cls");

	SKY_BLUE
		InterfaceManager.BoxDraw(START_X, START_Y, WIDTH, HEIGHT - 3);
	ShowPlayerStatus();
	InterfaceManager.gotoxy(WIDTH - 2, HEIGHT / 2);
	cout << "☆ " << iStage << " Stage ☆";
	Sleep(1000);
	InterfaceManager.BoxErase(WIDTH, HEIGHT / 2);
	InterfaceManager.DrawMidText("                   ", WIDTH, HEIGHT / 2);

	InterfaceManager.BoxDraw(WIDTH, HEIGHT / 2 + 4, 10, 5);
	while (1)
	{
		InterfaceManager.gotoxy(WIDTH - 4, HEIGHT / 2 + 6);
		if (!input.empty())
			cout << input;
		if (_kbhit())
		{
			//InterfaceManager.BoxDraw(WIDTH, HEIGHT / 2 + 4, 10, 5);
			InterfaceManager.gotoxy(WIDTH - 4, HEIGHT / 2 + 6);

			if (bInputCheck == true)
			{
				ch = _getch();
				if (ch == KEY_ENTER)
				{
					bflag_Die = m_WordManager.DieCheck(tmp, input);
					if (bflag_Die == true)
					{
						bNextStage = m_Player.AddScore();
						bInputCheck = true;
						if (bNextStage == true)
						{
							m_Player.InitScore();
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
					cout << input;
				}
				else
				{
					input += ch;
					cout << input;
				}
				iCompareClock = clock();
			}
			else
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
		}
		if (clock() - iDrawClock >= DRAW_SPEED - m_WordManager.SetDifficulty(iStage))
		{
			m_WordManager.CreateWord(tmp);
			iDrawClock = clock();
		}
		if (clock() - iMoveClock >= DROP_SPEED - m_WordManager.SetDifficulty(iStage))
		{
			m_WordManager.DropWord(tmp);
			bflag_Pass = m_WordManager.PassCheck(tmp);
			if (bflag_Pass == true)
			{
				bGameOver = m_Player.DamageLife();
				InterfaceManager.DrawPoint("                         ", 1, HEIGHT - 3);
				if (bGameOver == true)
				{
					system("cls");
					SKY_BLUE
						InterfaceManager.BoxDraw(START_X, START_Y, WIDTH, HEIGHT - 3);
					RED
						InterfaceManager.DrawMidText("☆ Game Over ☆", WIDTH, HEIGHT / 2);
					char tmpCh = _getch();
					m_RankManager.SaveRank(m_Player, iStage);
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
					InterfaceManager.DrawMidText("                                            ",WIDTH, iHeight);
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
	InterfaceManager.gotoxy(WIDTH, HEIGHT / 2 + 6);
	cin >> name;
	m_Player.SetName(name);
	InterfaceManager.BoxErase(WIDTH, HEIGHT / 2 + 10);
}

void GameManager::ShowRank()
{
	int iHeight = START_Y + 9;
	vector<Ranker> RankerList;
	RankerList = m_RankManager.LoadRank(m_Player);

	system("cls");
	GREEN
		InterfaceManager.BoxDraw(START_X, START_Y, WIDTH, HEIGHT - 3);
	BLUE
		InterfaceManager.BoxDraw(WIDTH, START_Y + 4, 20, 5);
	InterfaceManager.DrawMidText("Ranking", WIDTH, START_Y + 7);
	InterfaceManager.gotoxy(WIDTH, START_Y + 9);
	for (int i = 0; i < 60; i++)
		cout << "=";
	InterfaceManager.DrawMidText("Name", WIDTH- 10, START_Y + 9);
	InterfaceManager.DrawMidText("Score", WIDTH, START_Y + 9);
	InterfaceManager.DrawMidText("Stage", WIDTH + 10, START_Y + 9);

	for (vector<Ranker>::iterator iter = RankerList.begin(); iter != RankerList.end(); iter++)
	{
		InterfaceManager.gotoxy(WIDTH - 10, iHeight += 2);
		InterfaceManager.DrawMidText(iter->strName, WIDTH, iHeight);
		InterfaceManager.gotoxy(WIDTH, iHeight += 2);
		InterfaceManager.DrawMidText(iter->iScore, WIDTH, iHeight);
		InterfaceManager.gotoxy(WIDTH + 10, iHeight += 2);
		InterfaceManager.DrawMidText(iter->strName, WIDTH, iHeight);
	}
}

GameManager::~GameManager()
{
}