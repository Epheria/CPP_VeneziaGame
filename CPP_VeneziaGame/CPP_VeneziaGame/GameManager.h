#pragma once
#include "Macro.h"
#include "Interface.h"
#include "Player.h"

class GameManager
{
private:
	Interface InterfaceManager;
	Player m_Player;
public:
	void ShowMenu();
	void PlayGame();
	void LoadStory();
	void ShowPlayerStatus();

	GameManager();
	~GameManager();
};

