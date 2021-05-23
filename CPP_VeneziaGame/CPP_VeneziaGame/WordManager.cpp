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
		iter->Erase();
		iter->Drop();			
		iter->Show();
	}
}

void WordManager::PassCheck(vector<Word>& tmp)
{
	for (vector<Word>::iterator iter = tmp.begin(); iter != tmp.end(); iter++)
	{
		if (iter->GetPosy() >= DEADZONE)
		{
			iter->Erase();
			tmp.erase(iter);
			return;
		}
	}
}

int WordManager::Rand()
{
	srand(time(NULL));
	int Posx;
	Posx = rand() % 110 + 1;
	for (vector<Word>::iterator iter = m_WordList.begin(); iter != m_WordList.end(); iter++)
	{
		if (Posx == iter->GetPosx())
		{
			Posx = rand() % 108 + 2;
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
	DrawManager.DrawMidText(m_strName, m_ix, m_iy);
}

void Word::Erase()
{
	DrawManager.ErasePoint(m_ix, m_iy);
}

void Word::Die()
{

}

void Word::Pass()
{

}