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
public:
	void SaveRank(Player& m_Player, int iStage);
	vector<Ranker> LoadRank(Player& m_Player);
	Rank();
	~Rank();
};

