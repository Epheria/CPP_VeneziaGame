#pragma once
#include "Macro.h"
#include "Interface.h"

class Player
{
private:
	Interface m_Interface;
	int m_iScore;
	string m_strName;
	int m_iLife;

public:
	void ShowPlayerLife();
	void ShowPlayerScore();
	void ShowPlayerName();

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
	inline void InitScore()
	{
		m_iScore = 0;
	}
	void SetName(string name)
	{
		m_strName = name;
	}
	string GetName()
	{
		return m_strName;
	}
	Player();
	~Player();
};

