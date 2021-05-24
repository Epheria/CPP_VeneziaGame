#include "Player.h"

Player::Player()
{
	m_iLife = 9;
	m_iScore = 0;
}

void Player::ShowPlayerLife()
{
	int iWidth;
	iWidth = 5;
	BLUE
	m_Interface.DrawPoint("Life : ", 1, HEIGHT - 3);
	for (int i = 0; i < m_iLife; i++)
	{
		RED
		cout << "¢¾";
	}
}

void Player::ShowPlayerScore()
{
	BLUE
	m_Interface.DrawMidText("Score : ", WIDTH, HEIGHT - 3);
	YELLOW
	cout << m_iScore;
}

void Player::ShowPlayerName()
{
	m_Interface.ErasePoint(WIDTH * 2 - 20, HEIGHT - 3);
	if (m_strName.empty())
	{
		BLUE
		m_Interface.DrawMidText("Name : ", WIDTH * 2 - 20, HEIGHT - 3);
		PURPLE
		cout << "???";
	}
	else
	{
		BLUE
		m_Interface.DrawMidText("Name : ", WIDTH * 2 - 20, HEIGHT - 3);
		PURPLE
			cout << m_strName;
	}
}


Player::~Player()
{
}