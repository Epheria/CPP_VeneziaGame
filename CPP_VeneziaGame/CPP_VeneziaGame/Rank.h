#pragma once
#include "Macro.h"
#include "Player.h"

typedef struct Ranker
{
	string strName;
	int iScore;
	int iStage;
}Ranker;

class Rank
{
private:
	Interface DrawManager;
public:
	void SaveRank(Player& m_Player, int iStage);
	void LoadRank(Player& m_Player);
	void Swap(vector<Ranker>& RankerList, vector<Ranker>& tmp2);
	Rank();
	~Rank();
};

