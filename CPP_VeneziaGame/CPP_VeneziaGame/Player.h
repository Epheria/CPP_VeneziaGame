#pragma once
#include "Macro.h"
#include "Interface.h"
#include "WordManager.h"

class Player
{
private:
	int m_iScore;
	string m_strName;
	int m_iLife;

	int m_iClock;
	bool m_bInputCheck;
	string m_strInput;
public:
	void ShowPlayerLife();
	void ShowPlayerScore();
	void ShowPlayerName();
	bool KeyInput();
	void CheckInput();

	inline bool AddScore(int iAllClear, int iScore = 10)
	{
		m_iScore += iScore;
		m_iScore += iAllClear;
		if (m_iScore % 100 == 0 || iAllClear >= 100)
		{
			return true;
		}
		return false;
	}
	inline bool DamageLife(int iDamage = 1)
	{
		m_iLife -= iDamage;
		if (m_iLife == 0)
		{
			return true;
		}
		return false;
	}
	inline void InitLife()
	{
		m_iLife = 9;
	}
	inline int GetLife()
	{
		return m_iLife;
	}
	inline int GetScore()
	{
		return m_iScore;
	}
	inline string GetInput()
	{
		return m_strInput;
	}
	inline void InitInput()
	{
		m_iClock = clock();
		m_strInput.clear();
	}
	inline void InitScore()
	{
		m_iScore = 0;
	}
	void SetName(string name)
	{
		m_strName = name;
	}
	void SetInputCheck()
	{
		m_bInputCheck = false;
	}
	string GetName()
	{
		return m_strName;
	}
	Player();
	~Player();
};

