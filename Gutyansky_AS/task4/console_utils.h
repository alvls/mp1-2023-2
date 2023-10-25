#pragma once
#include <stdbool.h>
#include <Windows.h>
#include <stdio.h>
#include <memory.h>
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
void set_cursor_at(int x, int y);
void text_color(int color);
void text_background(int color);
void text_attr(int color);
void set_window_wh(int width, int height);
void set_window_rs(SMALL_RECT rect, COORD size);
void get_window(SMALL_RECT* rect, COORD* size);
void set_cursor_visible(bool isVisible);
void print_at(const char* format, int x, int y, ...);
bool try_read_int(int* result, int minValue, int maxValue);