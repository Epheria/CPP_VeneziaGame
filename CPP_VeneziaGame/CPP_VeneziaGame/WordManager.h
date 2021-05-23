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
	void Erase();
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
	Word() {}
	~Word() {}
};

class WordManager
{
private:
	int m_iWordNum;
	vector<Word> m_WordList;
public:
	void LoadFile();
	inline int Rand();
	void CreateWord(vector<Word>& tmp);
	void DropWord(vector<Word>& tmp);
	//void DieCheck(vector<Word>& tmp);
	void PassCheck(vector<Word>& tmp);
	WordManager();
	~WordManager();
};