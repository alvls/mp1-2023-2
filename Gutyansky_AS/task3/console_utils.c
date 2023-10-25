#include <stdbool.h>
#include <Windows.h>
#include <stdio.h>
#include <memory.h>
#include "console_utils.h"

int where_x(void) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!console)
		return -1;

	CONSOLE_SCREEN_BUFFER_INFO buf;

	GetConsoleScreenBufferInfo(console, &buf);
	return buf.dwCursorPosition.X;
}

int where_y(void) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!console) {
		return -1;
	}

	CONSOLE_SCREEN_BUFFER_INFO buf;

	GetConsoleScreenBufferInfo(console, &buf);
	return buf.dwCursorPosition.Y;
}

COORD where_xy(void) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { -1, -1 };
	if (!console) {
		return pos;
	}

	CONSOLE_SCREEN_BUFFER_INFO buf;

	GetConsoleScreenBufferInfo(console, &buf);
	return buf.dwCursorPosition;
}

void clear_screen(void) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!console)
		return;

	CONSOLE_SCREEN_BUFFER_INFO buf;
	GetConsoleScreenBufferInfo(console, &buf);

	WORD attr;
	DWORD count;
	COORD pos = buf.dwCursorPosition;
	ReadConsoleOutputAttribute(console, &attr, 1, pos, &count);

	int col = attr;
	int width = buf.dwSize.X;
	int height = buf.dwSize.Y;

	COORD z_pos = {
		.X = 0, .Y = 0
	};
	SetConsoleCursorPosition(console, z_pos);

	FillConsoleOutputAttribute(console, col, width * height, z_pos, &count);
	FillConsoleOutputCharacter(console, ' ', width * height, z_pos, &count);
}

void set_cursor_at(int x, int y) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!console) {
		return;
	}

	COORD pos = {
		.X = x,
		.Y = y
	};

	SetConsoleCursorPosition(console, pos);
}

void text_color(int color) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!console) {
		return;
	}

	CONSOLE_SCREEN_BUFFER_INFO buf;
	GetConsoleScreenBufferInfo(console, &buf);

	WORD attr;
	DWORD count;
	COORD pos = buf.dwCursorPosition;
	ReadConsoleOutputAttribute(console, &attr, 1, pos, &count);

	int bg_col = attr / 16;
	int col = color % 16;
	col = col + bg_col * 16;

	SetConsoleTextAttribute(console, col);

	char ch;
	pos = where_xy();
	ReadConsoleOutputCharacterA(console, &ch, 1, pos, &count);
	printf("%c", ch);
	set_cursor_at(pos.X, pos.Y);
}

void text_background(int color) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!console) {
		return;
	}

	CONSOLE_SCREEN_BUFFER_INFO buf;
	GetConsoleScreenBufferInfo(console, &buf);

	WORD attr;
	DWORD count;
	COORD pos = buf.dwCursorPosition;
	ReadConsoleOutputAttribute(console, &attr, 1, pos, &count);

	int text_col = attr % 16;
	int col = color % 16;
	col = color * 16 + text_col;

	SetConsoleTextAttribute(console, col);

	char ch;
	pos = where_xy();
	ReadConsoleOutputCharacterA(console, &ch, 1, pos, &count);
	printf("%c", ch);
	set_cursor_at(pos.X, pos.Y);
}

void text_attr(int color) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!console) {
		return;
	}

	SetConsoleTextAttribute(console, color);

	DWORD count;
	char ch;
	COORD pos = where_xy();
	ReadConsoleOutputCharacterA(console, &ch, 1, pos, &count);
	printf("%c", ch);
	set_cursor_at(pos.X, pos.Y);
}

void set_window_wh(int width, int height) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!console) {
		return;
	}

	SMALL_RECT rect = {
		.Left = 0,
		.Right = width - 1,
		.Top = 0,
		.Bottom = height - 1
	};
	COORD size = {
		.X = width,
		.Y = height
	};

	SetConsoleWindowInfo(console, true, &rect);
	SetConsoleScreenBufferSize(console, size);
}

void set_window_rs(SMALL_RECT rect, COORD size) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!console) {
		return;
	}

	SetConsoleScreenBufferSize(console, size);
	SetConsoleWindowInfo(console, true, &rect);
}

void get_window(SMALL_RECT* rect, COORD* size) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!console) {
		return;
	}

	CONSOLE_SCREEN_BUFFER_INFO buf;
	GetConsoleScreenBufferInfo(console, &buf);

	*rect = buf.srWindow;
	size->X = buf.dwSize.X;
	size->Y = buf.dwSize.Y;
}

void set_cursor_visible(bool isVisible) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!console) {
		return;
	}

	CONSOLE_CURSOR_INFO buf;
	GetConsoleCursorInfo(console, &buf);
	buf.bVisible = isVisible;
	SetConsoleCursorInfo(console, &buf);
}

void print_at(const char* format, int x, int y, ...) {
	set_cursor_at(x, y);

	va_list args;
	va_start(args, y);
	vprintf(format, args);
	va_end(args);
}

bool try_read_int(int* result, int minValue, int maxValue, int screen_x, int screen_y) {
	int read_arguments;

	print_at(">>> ", screen_x, screen_y);

	read_arguments = scanf_s("%d", result);
	while (getchar() != '\n');
	if (read_arguments == 1 && *result >= minValue && *result <= maxValue) {
		return true;
	}

	return false;
}