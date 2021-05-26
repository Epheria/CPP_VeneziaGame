#pragma once
#include "Macro.h"
#include "Interface.h"

class Word
{
private:
	int m_ix;
	int m_iy;
	string m_strName;
	ITEM m_eItem;
	Interface DrawManager;
public:
	void Drop();
	void Show(bool m_bBlind);
	void Erase(string name);
	void SetItem();

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
	inline ITEM GetItem()
	{
		return m_eItem;
	}
	Word() {}
	~Word() {}
};

class WordManager
{
private:
	bool m_bStop;
	bool m_bBlind;
	bool m_bAllClear;
	int m_iWordSpeed;
	int m_iWordNum;
	vector<Word> m_WordList;
	Interface DrawManager;
public:
	void LoadFile();
	inline int Rand();
	void CreateWord(vector<Word>& tmp, int iStopTime);
	void DropWord(vector<Word>& tmp, int iBlindTime, int iStopTime);
	bool DieCheck(vector<Word>& tmp, string input, int& iScore);
	bool PassCheck(vector<Word>& tmp);
	void UseItem(vector<Word>::iterator iter);
	int SetDifficulty(int iStage)
	{
		for (int i = 1; i < iStage; i++)
		{
			m_iWordSpeed += 200;
		}

		return m_iWordSpeed;
	}
	WordManager();
	~WordManager();
};