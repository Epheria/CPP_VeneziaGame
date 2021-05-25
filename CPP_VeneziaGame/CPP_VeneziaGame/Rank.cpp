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
		fSave << m_Player.GetName() << " " << m_Player.GetScore() << " " << iStage << endl;
		fSave.close();
	}
}

vector<Ranker> Rank::LoadRank(Player& m_Player)
{
	vector<Ranker> RankerList;
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

	return RankerList;
}

Rank::~Rank()
{
}