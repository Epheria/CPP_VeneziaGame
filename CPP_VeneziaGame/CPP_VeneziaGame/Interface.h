#pragma once
#include "Macro.h"
#define UP 'w'
#define DOWN 's'
#define ENTER 13

class Interface
{
public:
	static void BoxDraw(int Start_x, int Start_y, int Width, int Height);
	static void BoxErase(int Width, int Height);
	static void DrawPoint(string str, int x, int y);
	static void DrawMidText(string str, int x, int y);
	static void TextDraw(string str, int x, int y);
	static void ErasePoint(int x, int y);
	static void ErasePoint(int x, int y, string name);
	static int MenuSelectCursor(int MenuLen, int AddCol, int x, int y);
	Interface();
	static inline void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
	~Interface();
};

