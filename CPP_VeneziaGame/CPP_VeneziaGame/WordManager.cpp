#include "WordManager.h"


WordManager::WordManager()
{
	m_iWordNum = 0;
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

			m_WordList.push_back(tmp);
		}
	}
	fLoad.close();
}

void WordManager::CreateWord(vector<Word>& tmp)
{
	srand(time(NULL));
	Word wTmp;
	int index = rand() % m_iWordNum;
	wTmp = m_WordList[index];
	tmp.push_back(wTmp);
}

void WordManager::DropWord(vector<Word>& tmp)
{
	for (vector<Word>::iterator iter = tmp.begin(); iter != tmp.end(); iter++)
	{
		iter->Erase(iter->GetName());
		iter->Drop();			
		iter->Show();
		if ((iter->GetPosx() >= WIDTH - 20 && iter->GetPosx() <= WIDTH + 10))
		{
			DrawManager.BoxDraw(WIDTH, HEIGHT / 2 + 4, 10, 5);
		}
	}
}

bool WordManager::PassCheck(vector<Word>& tmp)
{
	for (vector<Word>::iterator iter = tmp.begin(); iter != tmp.end(); iter++)
	{
		if (iter->GetPosy() == DEADZONE)
		{
			iter->Erase(iter->GetName());
			DrawManager.gotoxy(0, HEIGHT - 4);
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

bool WordManager::DieCheck(vector<Word>& tmp, string input)
{
	for (vector<Word>::iterator iter = tmp.begin(); iter != tmp.end(); iter++)
	{
		if (iter->GetName() == input)
		{
			iter->Erase(iter->GetName());
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

WordManager::~WordManager()
{
}

void Word::Drop()
{
	m_iy++;
}

void Word::Show()
{
	BLUE
	DrawManager.DrawMidText(m_strName, m_ix, m_iy);
}

void Word::Erase(string name)
{
	DrawManager.ErasePoint(m_ix, m_iy, name);
}

void Word::Die()
{

}

void Word::Pass()
{

}