#pragma once
#include "Macro.h"
#include "Interface.h"

class Word
{
private:
	int m_ix;
	int m_iy;
	string m_strName;
	Interface DrawManager;
public:
	void Drop();
	void Show();
	void Erase(string name);
	void Pass();
	void Die();

	inline void SetName(string Name)
	{
		m_strName = Name;
	}
	inline void SetPosx(int x)
	{
		m_ix = x;
	}
	inline void SetPosy(int y)
	{
		m_iy = y;
	}
	inline int GetPosx()
	{
		return m_ix;
	}
	inline int GetPosy()
	{
		return m_iy;
	}
	inline string GetName()
	{
		return m_strName;
	}
	Word() {}
	~Word() {}
};

class WordManager
{
private:
	int m_iWordNum;
	vector<Word> m_WordList;
	Interface DrawManager;
public:
	void LoadFile();
	inline int Rand();
	void CreateWord(vector<Word>& tmp);
	void DropWord(vector<Word>& tmp);
	bool DieCheck(vector<Word>& tmp, string input);
	bool PassCheck(vector<Word>& tmp);
	int SetDifficulty(int iStage)
	{
		int iValue = 0;
		for (int i = 1; i < iStage; i++)
		{
			iValue += 200;
		}

		return iValue;
	}
	WordManager();
	~WordManager();
};