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

	inline int GetLife()
	{
		return m_iLife;
	}
	inline int GetScore()
	{
		return m_iScore;
	}
	void SetName(string name)
	{
		m_strName = name;
	}
	void GetName()
	{
		cout << m_strName;
	}
	Player();
	~Player();
};

