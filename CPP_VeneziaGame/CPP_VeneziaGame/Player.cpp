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
	m_Interface.DrawPoint("Life : ", 1, HEIGHT - 3);
	for (int i = 0; i < m_iLife; i++)
	{
		m_Interface.DrawPoint("¢¾", iWidth++, HEIGHT - 3);
	}
}

void Player::ShowPlayerScore()
{
	m_Interface.DrawMidText("Score : ", WIDTH, HEIGHT - 3);
	cout << m_iScore;
}

void Player::ShowPlayerName()
{
	if (m_strName.empty())
	{
		m_Interface.DrawMidText("Name : ", WIDTH * 2 - 20, HEIGHT - 3);
		cout << " ? ? ? ";
	}
	else
	{
		m_Interface.DrawMidText("Name : ", WIDTH * 2 - 20, HEIGHT - 3);
		cout << m_strName;
	}
}


Player::~Player()
{
}