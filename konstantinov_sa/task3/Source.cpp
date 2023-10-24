#define _CRT_SECURE_NO_WARNINGS
#include "windows.h"
#include "stdio.h"
#include "memory.h"

enum TColor {
    BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY,
    DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED,
    LIGHTMAGENTA, YELLOW, WHITE
};

//-----------------------------------------------------------------------------
int wherex(void)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        return -1;

    CONSOLE_SCREEN_BUFFER_INFO buf;

    GetConsoleScreenBufferInfo(Console, &buf);
    return buf.dwCursorPosition.X;
}

//-----------------------------------------------------------------------------
int wherey(void)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        return -1;

    CONSOLE_SCREEN_BUFFER_INFO buf;

    GetConsoleScreenBufferInfo(Console, &buf);
    return buf.dwCursorPosition.Y;
}

//-----------------------------------------------------------------------------
COORD WhereXY(void)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { -1, -1 };
    if (!Console)
        return pos;

    CONSOLE_SCREEN_BUFFER_INFO buf;

    GetConsoleScreenBufferInfo(Console, &buf);
    return buf.dwCursorPosition;
}

//-----------------------------------------------------------------------------
void clrscr(void)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        return;

    CONSOLE_SCREEN_BUFFER_INFO buf;
    GetConsoleScreenBufferInfo(Console, &buf);

    WORD Attr;
    DWORD Count;
    COORD pos = buf.dwCursorPosition;
    ReadConsoleOutputAttribute(Console, &Attr, 1, pos, &Count);

    int col = Attr;
    int width = buf.dwSize.X;
    int height = buf.dwSize.Y;

    COORD zpos;
    zpos.X = 0;
    zpos.Y = 0;
    SetConsoleCursorPosition(Console, zpos);

    FillConsoleOutputAttribute(Console, col, width * height, zpos, &Count);
    FillConsoleOutputCharacter(Console, ' ', width * height, zpos, &Count);
}

//-----------------------------------------------------------------------------
void gotoxy(int x, int y)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        return;

    COORD pos;
    pos.X = x;
    pos.Y = y;

    SetConsoleCursorPosition(Console, pos);
}

//-----------------------------------------------------------------------------
void textcolor(int color)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        return;

    CONSOLE_SCREEN_BUFFER_INFO buf;
    GetConsoleScreenBufferInfo(Console, &buf);

    WORD Attr;
    DWORD Count;
    COORD pos = buf.dwCursorPosition;
    ReadConsoleOutputAttribute(Console, &Attr, 1, pos, &Count);

    int bk_col = Attr / 16;
    int col = color % 16;
    col = col + bk_col * 16;

    SetConsoleTextAttribute(Console, col);

    char ch[2];
    pos = WhereXY();
    ReadConsoleOutputCharacter(Console, (LPSTR)ch, 1, pos, &Count);
    printf("%c", ch[0]);
    gotoxy(pos.X, pos.Y);
}

//-----------------------------------------------------------------------------
void textbackground(int color)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        return;

    CONSOLE_SCREEN_BUFFER_INFO buf;
    GetConsoleScreenBufferInfo(Console, &buf);

    WORD Attr;
    DWORD Count;
    COORD pos = buf.dwCursorPosition;
    ReadConsoleOutputAttribute(Console, &Attr, 1, pos, &Count);

    int text_col = Attr % 16;
    int col = color % 16;
    col = color * 16 + text_col;

    SetConsoleTextAttribute(Console, col);

    char ch[2];
    pos = WhereXY();
    ReadConsoleOutputCharacter(Console, (LPSTR)ch, 1, pos, &Count);
    printf("%c", ch[0]);
    gotoxy(pos.X, pos.Y);
}

//-----------------------------------------------------------------------------
void textattr(int color)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        return;

    SetConsoleTextAttribute(Console, color);

    DWORD Count;
    char ch[2];
    COORD pos = WhereXY();
    ReadConsoleOutputCharacter(Console, (LPSTR)ch, 1, pos, &Count);
    printf("%c", ch[0]);
    gotoxy(pos.X, pos.Y);
}

//-----------------------------------------------------------------------------
void setwindow(int width, int height)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        return;

    SMALL_RECT rect;
    rect.Left = 0;
    rect.Right = width - 1;
    rect.Top = 0;
    rect.Bottom = height - 1;
    COORD size;
    size.X = width;
    size.Y = height;
    SetConsoleWindowInfo(Console, true, &rect);
    //  printf("%d %d %d %d", rect.Left, rect.Top, rect.Right, rect.Bottom);
    SetConsoleScreenBufferSize(Console, size);
    //  printf("%d %d", size.X, size.Y);
}

//-----------------------------------------------------------------------------
void SetWindow(SMALL_RECT rect, COORD size)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        return;

    SetConsoleScreenBufferSize(Console, size);
    SetConsoleWindowInfo(Console, true, &rect);
}

//-----------------------------------------------------------------------------
void GetWindow(SMALL_RECT* rect, COORD* size)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        return;

    CONSOLE_SCREEN_BUFFER_INFO buf;
    GetConsoleScreenBufferInfo(Console, &buf);

    *rect = buf.srWindow;
    size->X = buf.dwSize.X;
    size->Y = buf.dwSize.Y;
}

//-----------------------------------------------------------------------------
void HideCursor(void)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        return;

    CONSOLE_CURSOR_INFO buf;
    GetConsoleCursorInfo(Console, &buf);
    buf.bVisible = false;
    SetConsoleCursorInfo(Console, &buf);
}

//-----------------------------------------------------------------------------
void ShowCursor(void)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        return;

    CONSOLE_CURSOR_INFO buf;
    GetConsoleCursorInfo(Console, &buf);
    buf.bVisible = true;
    SetConsoleCursorInfo(Console, &buf);
}

//VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV

#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<time.h>
#include<math.h>

// | test mode with debug hints
// V
//#define Test

//random in range
int rir(int l, int r) {
    return round(rand() * ((double)(r - l) / RAND_MAX) + l);
}

int checkuniq(int n) {
    int digits[10] = { 0 };
    while (n > 0) {
        int c = n % 10;
        if (digits[c]) {
            return 0;
        }
        digits[c] = 1;
        n /= 10;
    }
    return 1;
}

void printnum(int n, int places[5]) {
    for (int i = 0; i < n; i++) {
        printf("%d", places[i]);
    }
    printf("\n");
}

void gennum(int n, int places[5], int digits[10]) {
    places[0] = rir(1, 9);
    digits[places[0]] = 1;
    for (int i = 1; i < n; i++) {

        while (1) {
            int e = rir(0, 9);
            if (!digits[e])
            {
                places[i] = e;
                digits[e] = 1;
                break;
            }
        }
    }

#ifdef Test
    printnum(n, places);

    for (int i = 0; i < 10; i++) {
        printf("%d", i);
    }
    printf("\n");
    for (int i = 0; i < 10; i++) {
        printf("%d", digits[i]);
    }
#endif
}

void startmsg() {
    clrscr();
    gotoxy(10, 0);
    textcolor(GREEN);
    textbackground(BLUE);
    printf("Игра \"Быки и коровы\".\n");
    printf("Вам предстоит угадать загаданное компьютером число с различными цифрами.\n");
    textbackground(GREEN);
    printf("Компьютер сообщает, сколько цифр угадано без совпадения с их позициями в загаданном числе (то есть количество коров)\n");
    textbackground(BLUE);
    printf("и сколько угадано вплоть до позиции в загаданном числе (то есть количество быков).\n");
    textbackground(CYAN);
    printf("Цвет копии введённых вам символов помогает увидеть изменения с прошлого ввода.\n");
    textbackground(RED);
    printf("Чтобы сдаться введите 0.\n");
    textbackground(BLACK);
    printf("Введите количество цифр числа, которое будет загадано (2-5):\n");

}

void printchanges(int old, int n, int l) {
    char ob[5];
    char nb[5];
    sprintf(ob, "%d", old);
    sprintf(nb, "%d", n);
    for (int i = 0; i < l; i++) {
        char co = ob[i];
        char cn = nb[i];
        if (co == cn) {
            textbackground(BLUE);
            printf("%c", cn);
        }
        else {
            textbackground(GREEN);
            printf("%c", cn);
        }
    }
    textbackground(BLACK);
    printf(" ");
}

int main() {
    setlocale(LC_ALL, "");

    srand(time(NULL) * time(NULL));

    startmsg();
    int n = 0;
    while (!((n >= 2) && (n <= 5))) {
        if (!scanf("%d", &n))
            while (getchar() != '\n');
    }

    int mg = 1;
    for (int i = 0; i < n;i++)
        mg *= 10;

    int num[5] = { -1,-1,-1,-1,-1 };
    int digits[10] = { 0 };
    gennum(n, num, digits);
    printf("\n");
    clrscr();

    int vp = 0, tries = 0, oldg = -1;
    while (vp != n) {
        vp = 0;
        int g = -1, vd = 0;

        while ((!((mg / 10 <= g) && (g < mg))) || (!checkuniq(g))) {
            textcolor(GREEN);
            printf("      Введите %d-значное число с различными цифрами:\n", n);
            textcolor(WHITE);
            if (!scanf("%d", &g))
                while (getchar() != '\n');
            if (g == 0) {
                textbackground(RED);
                printf("Вы сдались, затратив %d попыток...\nЧисло было ", tries);
                printnum(n, num);
                system("pause");
                return 0;
            }
        }

        printchanges(oldg, g, n);
        oldg = g;
        tries += 1;
        for (int i = n - 1; i >= 0; i--) {
            int c = g % 10;
            g /= 10;
            //printf("c%d d%d n%d \n", c, digits[c], num[i]);
            if (digits[c])
                vd++;
            if (num[i] == c)
                vp++;
        }

        textcolor(CYAN);
        printf("Коров: %d ", vd - vp);
        textcolor(BROWN);
        printf("Быков: %d \n", vp);
        textcolor(WHITE);

    }
    textbackground(GREEN);
    printf("Угадано за %d попыток\n", tries);
    textbackground(BLACK);
    system("pause");
    return 0;
}

//-----------------------------------------------------------------------------
int main2()
{
    /*
      const int COUNT = 16 * 16;
      SMALL_RECT window;
      COORD buf;
      GetWindow(&window, &buf);
      HideCursor();
      printf("%d %d %d %d", window.Left, window.Top, window.Right, window.Bottom);
      setwindow(80, 25);
      getchar();
      textattr(LIGHTGRAY);
    */
    clrscr();

    gotoxy(10, 10);
    printf("test\n");
    /*
      gotoxy(0, 12);
      textattr(RED);
      printf("abcd");
      getchar();

      gotoxy(2, 12);
      textbackground(BLUE);
      printf("cdef");
      getchar();
    */
    gotoxy(4, 12);
    textcolor(BLUE);
    textbackground(GREEN);
    printf("efgh");
    /*
      for (int i = 0; i < COUNT; i++)
      {
        textcolor(i);
        textbackground(i / 16);
        printf("a");
      }
    */
    textattr(LIGHTGRAY);
    /*
      int page = GetConsoleOutputCP();
      printf("page = %d", page);
      SetConsoleOutputCP(1251);
      printf("нажмите любую клавишу");
    */
    printf("press any key");
    getchar();
    //  SetWindow(window, buf);

    ShowCursor();

    return 0;
}
//- end of file ---------------------------------------------------------------
