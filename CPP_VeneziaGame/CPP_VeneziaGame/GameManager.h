#pragma once
#include "Macro.h"
#include "Interface.h"
#include "Player.h"
#include "WordManager.h"

class GameManager
{
private:
	Interface InterfaceManager;
	Player m_Player;
	WordManager m_WordManager;
public:
	void ShowMenu();
	void PlayGame();
	int Stage(int iStage);
	void LoadStory();
	void SetPlayerName();
	void ShowPlayerStatus();

	GameManager();
	~GameManager();
};

