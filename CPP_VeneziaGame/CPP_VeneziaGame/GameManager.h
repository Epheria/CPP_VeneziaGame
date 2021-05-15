#pragma once
#include "Macro.h"
#include "Interface.h"
class GameManager
{
private:
	Interface InterfaceManager;
public:
	void ShowMenu();

	GameManager();
	~GameManager();
};

