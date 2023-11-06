#pragma once
#include <stdbool.h>
#include <Windows.h>
#include <stdarg.h>

enum TColor {
	BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY,
	DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED,
	LIGHTMAGENTA, YELLOW, WHITE
};

int where_x(void);
int where_y(void);
COORD where_xy(void);
void clear_screen(void);
void set_cursor_at(short x, short y);
void text_color(int color);
void text_background(short color);
void text_attr(short color);
void set_window_wh(short width, short height);
void set_window_rs(SMALL_RECT rect, COORD size);
void get_window(SMALL_RECT* rect, COORD* size);
void set_cursor_visible(bool isVisible);
void print_at(const char* format, short x, short y, ...);
bool try_read_int(int* result, int minValue, int maxValue);