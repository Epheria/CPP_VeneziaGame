#include "WordManager.h"


WordManager::WordManager()
{
	m_bBlind = false;
	m_bStop = false;
	m_bAllClear = false;
	m_iWordNum = 0;
	m_iWordSpeed = 0;
	m_iDrawClock = clock();
	m_iMoveClock = clock();
	m_iBlindTime = clock();
	m_iStopTime = clock();
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
		m_iWordNum = iNum;
		for (int i = 0; i < iNum; i++)
		{
			fLoad >> buf;
			tmp.SetName(buf);
			tmp.SetPosx(Rand());
			tmp.SetPosy(1);
			tmp.RandItem();

			m_WordList.push_back(tmp);
		}
	}
	fLoad.close();
}

void WordManager::CreateWord(vector<Word>& tmp, int iStage)
{
	if (m_bStop == true)
	{
		return;
	}

	Word wTmp;

	if (clock() - m_iDrawClock >= DRAW_SPEED - SetDifficulty(iStage))
	{
		int index = rand() % m_iWordNum;
		//for (vector<Word>::iterator iter = m_WordList.begin(); iter != m_WordList.end(); iter++)
		//{
		//	if (m_WordList[index].GetName() == iter->GetName())
		//	{
		//		index = rand() % m_iWordNum;
		//	}
		//}
		wTmp = m_WordList[index];
		tmp.push_back(wTmp);
		m_iDrawClock = clock();
	}
}

void WordManager::DropWord(vector<Word>& tmp, int iStage)
{
	if (m_bStop == true)
	{
		return;
	}

	if (clock() - m_iMoveClock >= DROP_SPEED - SetDifficulty(iStage))
	{
		for (vector<Word>::iterator iter = tmp.begin(); iter != tmp.end(); iter++)
		{
			iter->Erase(iter->GetName(), m_bBlind);
			iter->Drop();
			iter->Show(m_bBlind);
			if ((iter->GetPosx() >= WIDTH - 20 && iter->GetPosx() <= WIDTH + 10))
			{
				Interface::BoxDraw(WIDTH, HEIGHT / 2 + 4, 14, 5);
			}
		}
		m_iMoveClock = clock();
	}
}

bool WordManager::PassCheck(vector<Word>& tmp)
{
	for (vector<Word>::iterator iter = tmp.begin(); iter != tmp.end(); iter++)
	{
		if (iter->GetPosy() == DEADZONE)
		{
			iter->Erase(iter->GetName(), m_bBlind);
			Interface::gotoxy(0, HEIGHT - 4);
			for (int i = 0; i < 60; i++)
			{
				if (i == 0)
				{
					cout << "¦¦";
				}
				else if (i == 59)
				{
					cout << "¦¥";
				}
				else
				{
					cout << "¦¡";
				}
			}
			tmp.erase(iter);
			return true;
		}
	}
	return false;
}

bool WordManager::DieCheck(vector<Word>& tmp, string input, int& iScore)
{
	int iKillCount = 0;
	for (vector<Word>::iterator iter = tmp.begin(); iter != tmp.end(); iter++)
	{
		if (iter->GetName() == input)
		{
			iter->Erase(iter->GetName(), m_bBlind);
			if (!(iter->GetItem() == ITEM_DEFAULT))
			{
				UseItem(iter);
				if (m_bAllClear == true)
				{
					for (vector<Word>::iterator iter = tmp.begin(); iter != tmp.end(); iter++)
					{
						iKillCount = tmp.size();
						iter->Erase(iter->GetName(), m_bBlind);
					}
					tmp.clear();
					iScore = iKillCount * 10;
					m_bAllClear = false;
					return true;
				}
			}
			tmp.erase(iter);
			return true;
		}
	}
	return false;
}

int WordManager::Rand()
{
	srand(time(NULL));
	int Posx;
	Posx = rand() % 100 + 10;
	for (vector<Word>::iterator iter = m_WordList.begin(); iter != m_WordList.end(); iter++)
	{
		if (Posx == iter->GetPosx())
		{
			Posx = rand() % 100 + 10;
		}
	}

	return Posx;
}

void WordManager::UseItem(vector<Word>::iterator iter)
{
	if (iter->GetItem() == ITEM_INCREASE)
	{
		m_iWordSpeed -= 100;
	}
	else if (iter->GetItem() == ITEM_DECREASE)
	{
		m_iWordSpeed += 100;
	}
	else if (iter->GetItem() == ITEM_STOP)
	{
		m_bStop = true;
		m_iStopTime = clock();
	}
	else if (iter->GetItem() == ITEM_ALLCLEAR)
	{
		m_bAllClear = true;
	}
	else if (iter->GetItem() == ITEM_BLIND)
	{
		m_bBlind = true;
		m_iBlindTime = clock();
	}
}

WordManager::~WordManager()
{
}

void Word::Drop()
{
	m_iy++;
}

void Word::Show(bool m_bBlind)
{
	if (m_bBlind == true)
	{
		YELLOW
			Interface::DrawMidText("======", m_ix, m_iy);
	}
	else
	{
		if (m_eItem == ITEM_DEFAULT)
		{
			BLUE
				Interface::DrawMidText(m_strName, m_ix, m_iy);
		}
		else if (m_eItem == ITEM_BLIND)
		{
			GREEN
				Interface::DrawMidText(m_strName, m_ix, m_iy);
		}
		else if (m_eItem == ITEM_ALLCLEAR)
		{
			GOLD
				Interface::DrawMidText(m_strName, m_ix, m_iy);
		}
		else if (m_eItem == ITEM_DECREASE)
		{
			ORIGINAL
				Interface::DrawMidText(m_strName, m_ix, m_iy);
		}
		else if (m_eItem == ITEM_INCREASE)
		{
			GRAY
				Interface::DrawMidText(m_strName, m_ix, m_iy);
		}
		else if (m_eItem == ITEM_STOP)
		{
			RED
				Interface::DrawMidText(m_strName, m_ix, m_iy);
		}
		//else
		//{
		//	PURPLE
		//		DrawManager.DrawMidText(m_strName, m_ix, m_iy);
		//}
	}
}

void Word::Erase(string name, bool m_bBlind)
{
	if (m_bBlind == true)
	{
		Interface::ErasePoint(m_ix, m_iy, "======");
	}
	else
	{
		Interface::ErasePoint(m_ix, m_iy, name);
	}
}

void Word::RandItem()
{
	int iRand;
	iRand = rand() % 10 + 1;

	if (iRand > 0 && iRand <= 1)
		m_eItem = ITEM_INCREASE;
	else if (iRand > 1 && iRand <= 2)
		m_eItem = ITEM_DECREASE;
	else if (iRand > 2 && iRand <= 3)
		m_eItem = ITEM_STOP;
	else if (iRand > 3 && iRand <= 4)
		m_eItem = ITEM_ALLCLEAR;
	else if (iRand > 4 && iRand <= 5)
		m_eItem = ITEM_BLIND;
	else if(iRand > 5 && iRand <= 11)
		m_eItem = ITEM_DEFAULT;
}