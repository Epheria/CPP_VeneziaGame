#include "Rank.h"

Rank::Rank()
{
}

void Rank::SaveRank(Player& m_Player, int iStage)
{
	ofstream fSave;
	fSave.open("Rank.txt", ios::app);
	if (fSave.is_open())
	{
		fSave << endl;
		fSave << m_Player.GetName() << " " << m_Player.GetScore() << " " << iStage;
		fSave.close();
	}
}

void Rank::LoadRank(Player& m_Player)
{
	vector<Ranker> RankerList;
	int iHeight = START_Y + 11;
	Ranker tmp;
	ifstream fLoad;
	fLoad.open("Rank.txt");
	if (fLoad.is_open())
	{
		while (!fLoad.eof())
		{
			fLoad >> tmp.strName >> tmp.iScore >> tmp.iStage;
			RankerList.push_back(tmp);
		}
		fLoad.close();
	}

	system("cls");
	GREEN
		DrawManager.BoxDraw(START_X, START_Y, WIDTH, HEIGHT - 3);
	BLUE
		DrawManager.BoxDraw(WIDTH, START_Y + 4, 20, 5);
	DrawManager.DrawMidText("Ranking", WIDTH, START_Y + 6);
	DrawManager.gotoxy(START_X + 2, START_Y + 9);
	for (int i = 0; i < 116; i++)
		cout << "=";
	DrawManager.DrawMidText("Name", WIDTH - 15, START_Y + 11);
	DrawManager.DrawMidText("Score", WIDTH, START_Y + 11);
	DrawManager.DrawMidText("Stage", WIDTH + 15, START_Y + 11);

	vector<Ranker> tmp2;

	if (!RankerList.empty())
	{
		for(int i = 0; i < RankerList.size() - 1; i++)
		{
			for (int j = 0; j < RankerList.size() - i - 1; j++)
			{
				if (RankerList[j].iScore < RankerList[j + 1].iScore)
				{
					tmp2.push_back(RankerList[j]);
					RankerList[j] = RankerList[j + 1];
					RankerList[j + 1] = tmp2[0];
					tmp2.clear();
				}
			}
		}

		for (vector<Ranker>::iterator iter = RankerList.begin(); iter != RankerList.end(); iter++)
		{
			DrawManager.DrawMidText(iter->strName, WIDTH - 15, iHeight += 2);
			DrawManager.gotoxy(WIDTH, iHeight);
			cout << iter->iScore;
			DrawManager.gotoxy(WIDTH + 15, iHeight);
			cout << iter->iStage;
		}
	}

	char ch = _getch();
}

Rank::~Rank()
{
}