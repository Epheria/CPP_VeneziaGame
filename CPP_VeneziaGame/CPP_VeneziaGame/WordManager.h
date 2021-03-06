#pragma once
#include "Macro.h"
#include "Interface.h"

class Word
{
private:
	int m_ix;
	int m_iy;
	string m_strName;
	int m_eItem;
public:
	void Drop();
	void Show(bool m_bBlind);
	void Erase(string name, bool m_bBlind);
	void RandItem();

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
	inline int GetItem()
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
	int m_iDrawClock;
	int m_iMoveClock;
	int m_iBlindTime;
	int m_iStopTime;
	vector<Word> m_WordList;
public:
	void LoadFile();
	inline int Rand();
	void CreateWord(vector<Word>& tmp, int iStage);
	void DropWord(vector<Word>& tmp, int iStage);
	bool DieCheck(vector<Word>& tmp, string input, int& iScore);
	bool PassCheck(vector<Word>& tmp);
	void UseItem(vector<Word>::iterator iter);
	inline void InitItemStatus()
	{
		m_bStop = false;
		m_bBlind = false;
		m_bAllClear = false;
		m_iWordSpeed = 0;
	}
	int SetDifficulty(int iStage)
	{
		int iSpeed = m_iWordSpeed;
		for (int i = 1; i < iStage; i++)
		{
			iSpeed += 200;
		}

		return iSpeed;
	}
	inline bool GetStop()
	{
		return m_bStop;
	}
	inline bool GetBlind()
	{
		return m_bBlind;
	}
	inline void StopCheck()
	{
		if (m_bStop == true)
		{
			if (clock() - m_iStopTime >= ITEM_STOPTIME)
			{
				m_bStop = false;
				m_iStopTime = clock();
			}
		}
	}
	inline void BlindCheck()
	{
		if (m_bBlind == true)
		{
			if (clock() - m_iBlindTime >= ITEM_BLINDTIME)
			{
				m_bBlind = false;
				m_iBlindTime = clock();
			}
		}
	}
	WordManager();
	~WordManager();
};