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
	vector<Ranker> tmp2;
	int iHeight = START_Y + 11;
	Ranker tmp;
	ifstream fLoad;
	int iSelect, index;
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

	Swap(RankerList, tmp2);
	int iMax = RankerList.size();
	int iMaxPage = RankerList.size() / 7 + 1;
	int iCurPageIndex = 1;

	while (1)
	{
		index = 0 + (iCurPageIndex - 1) * 7;

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

		for (int i = 0; i < 7; i++)
		{
			if (index <= iMax)
			{
				DrawManager.DrawMidText(RankerList[index].strName, WIDTH - 15, iHeight += 2);
				DrawManager.gotoxy(WIDTH, iHeight);
				cout << RankerList[index].iScore;
				DrawManager.gotoxy(WIDTH + 15, iHeight);
				cout << RankerList[index].iStage;
				index++;
			}
		}
		iHeight = START_Y + 11;
		DrawManager.DrawMidText("이전 페이지", WIDTH, START_Y + 27);
		DrawManager.DrawMidText("다음 페이지", WIDTH, START_Y + 29);
		DrawManager.DrawMidText("나가기", WIDTH, START_Y + 31);
		
		iSelect = DrawManager.MenuSelectCursor(3, 2, WIDTH / 4, START_Y + 27);

		if (iSelect == 1)
		{
			if (iCurPageIndex == 1)
				continue;
			iMax += 7;
			iCurPageIndex--;
			continue;
		}
		else if (iSelect == 2)
		{
			if (iCurPageIndex == iMaxPage)
				continue;
			iMax -= 7;
			iCurPageIndex++;
			continue;
		}
		else if(iSelect == 3)
		{
			return;
		}
	}
}

void Rank::Swap(vector<Ranker>& RankerList, vector<Ranker>& tmp2)
{
	for (int i = 0; i < RankerList.size() - 1; i++)
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
}

Rank::~Rank()
{
}