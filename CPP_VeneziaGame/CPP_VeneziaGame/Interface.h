#pragma once
#include "Macro.h"
#define UP 'w'
#define DOWN 's'
#define ENTER 13

class Interface
{
public:
	void BoxDraw(int Start_x, int Start_y, int Width, int Height);
	void BoxErase(int Width, int Height);
	void DrawPoint(string str, int x, int y);
	void DrawMidText(string str, int x, int y);
	void TextDraw(string str, int x, int y);
	void ErasePoint(int x, int y);
	void ErasePoint(int x, int y, string name);
	int MenuSelectCursor(int MenuLen, int AddCol, int x, int y);
	Interface();
	inline void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
	~Interface();
};

