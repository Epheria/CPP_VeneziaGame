#include "Macro.h"
#include "GameManager.h"

void main()
{
	system("mode con: cols=140 lines=50");
	GameManager mGameManager;
	mGameManager.ShowMenu();
}