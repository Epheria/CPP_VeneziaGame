#pragma once
#include "Macro.h"

class WordManager
{
private:
	vector<Word> m_WordList;
public:
	void LoadFile();
	int Rand();
	WordManager();
	~WordManager();
};

class Word
{
private:
	int m_ix;
	int m_iy;
	string m_strName;
public:
	void SetName(string Name)
	{
		m_strName = Name;
	}
	void SetPosx(int x)
	{
		m_ix = x;
	}
	void SetPosy(int y)
	{
		m_iy = y;
	}
	Word() {}
	~Word() {}
};