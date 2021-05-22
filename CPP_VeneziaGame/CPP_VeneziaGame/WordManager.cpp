#include "WordManager.h"


WordManager::WordManager()
{
}

void WordManager::LoadFile()
{
	int iNum;
	string buf;
	ifstream fLoad;
	Word tmp;

	fLoad.open("Word.txt");
	if (fLoad.is_open())
	{
		fLoad >> iNum;
		for (int i = 0; i < iNum; i++)
		{
			fLoad >> buf;
			tmp.SetName(buf);
			tmp.SetPosx(Rand());
			tmp.SetPosy(1);

			m_WordList.push_back(tmp);
		}
	}
	fLoad.close();
}

int WordManager::Rand()
{
	int Posx;
	srand(time(NULL));
	Posx = rand() % 110 + 1;

	return Posx;
}

WordManager::~WordManager()
{
}