#include "Player.h"

Player::Player()
{
	m_iClock = clock();
	m_bInputCheck = true;
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

bool Player::KeyInput()
{
	if (m_bInputCheck == false)
		return false;

	char ch;
	if (_kbhit())
	{
		m_Interface.gotoxy(WIDTH - 4, HEIGHT / 2 + 6);
		ch = _getch();
		if (ch == KEY_ENTER)
		{
			m_Interface.ErasePoint(WIDTH - 4, HEIGHT / 2 + 6, m_strInput);
			return true;
		}
		else if (ch == KEY_BACKSPACE)
		{
			m_Interface.ErasePoint(WIDTH - 4, HEIGHT / 2 + 6, m_strInput);
			if (!m_strInput.empty())
				m_strInput.pop_back();
			m_Interface.gotoxy(WIDTH - 4, HEIGHT / 2 + 6);
			BLUE
				m_Interface.DrawMidText(m_strInput, WIDTH, HEIGHT / 2 + 6);
		}
		else
		{
			if (m_strInput.length() <= 20)
				m_strInput += ch;
			BLUE
				m_Interface.DrawMidText(m_strInput, WIDTH, HEIGHT / 2 + 6);
		}
	}
	m_Interface.DrawMidText(m_strInput, WIDTH, HEIGHT / 2 + 6);
	return false;
}

void Player::CheckInput()
{
	if (m_bInputCheck == false)
	{
		RED
			m_Interface.DrawMidText("Failed compare!", WIDTH, HEIGHT / 2 + 6);

		if (clock() - m_iClock >= COMPARE_TIME + 2000)
		{
			m_Interface.ErasePoint(WIDTH, HEIGHT / 2 + 6, "Failed compare!");
			m_bInputCheck = true;
			m_iClock = clock();
		}
	}
}

Player::~Player()
{
}