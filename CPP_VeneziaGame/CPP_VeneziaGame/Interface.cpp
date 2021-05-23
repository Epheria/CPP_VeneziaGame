#include "Interface.h"

Interface::Interface()
{
}

void Interface::ErasePoint(int x, int y)
{
	gotoxy(x - 5, y);
	cout << "              ";
	gotoxy(-1, -1);
	return;
}

void Interface::DrawPoint(string str, int x, int y)
{
	gotoxy(x * 2, y);
	cout << str;
	gotoxy(-1, -1);
	return;
}

void Interface::DrawMidText(string str, int x, int y)
{
	if (x > str.size() / 2)
		x -= str.size() / 2;
	gotoxy(x, y);
	cout << str;
	return;
}
void Interface::TextDraw(string str, int x, int y)
{
	gotoxy(x, y);
	cout << str;
}

void Interface::BoxErase(int Width, int Height)
{
	for (int y = 1; y < Height - 1; y++)
	{
		gotoxy(2, y);
		for (int x = 1; x < Width - 1; x++)
			cout << "  ";
	}
}

void Interface::BoxDraw(int Start_x, int Start_y, int Width, int Height)
{
	if (Start_x > Width)
		Start_x -= Width;
	for (int y = 0; y < Height; y++)
	{
		gotoxy(Start_x, Start_y + y);
		if (y == 0)
		{
			BLUE
				cout << "��";
			for (int x = 1; x < Width - 1; x++)
				cout << "��";
			cout << "��";
		}
		else if (y == Height - 1)
		{
			BLUE
				cout << "��";
			for (int x = 1; x < Width - 1; x++)
				cout << "��";
			cout << "��";
		}
		else
		{
			BLUE
				cout << "��";
			for (int x = 1; x < Width - 1; x++)
				cout << "  ";
			cout << "��";
		}
	}
	return;
}

int Interface::MenuSelectCursor(int MenuLen, int AddCol, int x, int y)
{
	int Select = 1;
	RED
		DrawPoint("��", x, y);
	ORIGINAL
		while (1)
		{
			switch (_getch())
			{
			case UP:
				if (Select - 1 >= 1)
				{
					ErasePoint(x, y);
					y -= AddCol;
					Select--;
				}
				break;
			case DOWN:
				if (Select + 1 <= MenuLen)
				{
					ErasePoint(x, y);
					y += AddCol;
					Select++;
				}
				break;
			case ENTER:
				return Select;
			}
			RED
				DrawPoint("��", x, y);
			ORIGINAL
		}
}

Interface::~Interface()
{
}