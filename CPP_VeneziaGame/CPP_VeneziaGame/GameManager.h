#pragma once
#include "Macro.h"
#include "Interface.h"
#include "Player.h"
#include "WordManager.h"
#include "Rank.h"
class GameManager
{
private:
	Player m_Player;
	WordManager m_WordManager;
	Rank m_RankManager;
public:
	void ShowMenu();
	void PlayGame();
	int Stage(int iStage);
	void LoadStory();
	void SetPlayerName();
	void ShowPlayerStatus();
	void ShowRank();
	GameManager();
	~GameManager();
};

