#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>

#include "console_utils.h"
#include "barcode.h"
#include "product.h"

typedef enum ApplicationState {
	MAIN_MENU,
	PRODUCT_INFO,
	SCAN_AND_ADD,
	CHECK_INFO,
	TOTAL_PRICE,
	EXIT
} ApplicationState;

void user_loop(void);
Barcode read_barcode(void);
ApplicationState main_menu(void);
ApplicationState product_info_menu(void);
ApplicationState scan_and_add_menu(void);
ApplicationState check_info_menu(void);
ApplicationState total_price_menu(void);

void main(void) {
	setlocale(LC_ALL, "rus");
	set_window_wh(120, 40);
	user_loop();
}

void user_loop() {
	ApplicationState app_state = MAIN_MENU;

	while (app_state != EXIT) {
		switch (app_state) {
		case MAIN_MENU:
			app_state = main_menu();
			break;
		case PRODUCT_INFO:
			app_state = product_info_menu();
			break;
		case SCAN_AND_ADD:
			app_state = scan_and_add_menu();
			break;
		case CHECK_INFO:
			app_state = check_info_menu();
			break;
		case TOTAL_PRICE:
			app_state = total_price_menu();
			break;
		}
	}
}

ApplicationState main_menu(void) {
	int choice;

	set_cursor_visible(0);

	do {
		clear_screen();

		set_cursor_at(0, 0);
		text_background(BLUE);
		text_color(WHITE);
		printf("E-�����");

		set_cursor_at(0, 2);
		text_background(BLACK);
		printf("�������� ��������:");
		set_cursor_at(0, 3);
		printf("1. ������ ���������� � ������");
		set_cursor_at(0, 4);
		printf("2. ������������� � �������� � ���");
		set_cursor_at(0, 5);
		printf("3. ���������� ���");
		set_cursor_at(0, 6);
		printf("4. ������ �������� ���������");
		set_cursor_at(0, 7);
		printf("5. �����");
		set_cursor_at(0, 8);
		printf(">>> ");
	} while (!try_read_int(&choice, 1, 5));

	set_cursor_visible(1);

	switch (choice)
	{
	case 1:
		return PRODUCT_INFO;
	case 2:
		return SCAN_AND_ADD;
	case 3:
		return CHECK_INFO;
	case 4:
		return TOTAL_PRICE;
	case 5:
		return EXIT;
	default:
		return MAIN_MENU;
	}
}

ApplicationState product_info_menu(void)
{
	Barcode barcode;
	Product* product;
	int choice;

	barcode = read_barcode();
	product = get_product_by_barcode(barcode);
	
	if (product == NULL) {
		do {
			set_cursor_at(0, 0);
			clear_screen();
			printf("����� � ����� ���������� �� ����������!\n\n\
1. ����������� ������ �����\n\
2. �����\n\
>>> ");
		} while (!try_read_int(&choice, 1, 2));

		switch (choice) {
		case 1:
			return PRODUCT_INFO;
		case 2:
			return MAIN_MENU;
		}
	}
	else {
		do {
			set_cursor_at(0, 0);
			clear_screen();
			print_product_info(product);
			printf("\n\n1. �������� � ���\n\
2. ����������� ������ �����\n\
3. �����\n\
>>> ");
		} while (!try_read_int(&choice, 1, 3));

		switch (choice) {
		case 1:
			printf("�����");
			return MAIN_MENU;
		case 2:
			return PRODUCT_INFO;
		case 3:
			return MAIN_MENU;
		}
	}


}

ApplicationState scan_and_add_menu(void)
{

}

ApplicationState check_info_menu(void)
{
	
}

ApplicationState total_price_menu(void)
{
	
}

Barcode read_barcode(void)
{
	int read_params;
	int read_chars;
	char buffer[5];
	Barcode barcode;
	char is_barcode_valid;

	do {
		clear_screen();
		set_cursor_at(0, 0);
		printf("������� �������� (4 ������� �� 0 �� 9):\n>>> ");
		is_barcode_valid = 1;
		read_params = scanf("%4s%n", buffer, &read_chars);
		while (getchar() != '\n');
		is_barcode_valid = (read_params == 1 && read_chars == 4);

		if (is_barcode_valid) {
			for (char i = 0; i < 4; i++) {
				if (buffer[i] < '0' || buffer[i] > '9') {
					is_barcode_valid = 0;
					break;
				}

				barcode.values[i] = buffer[i];
			}
		}
	} while (!is_barcode_valid);

	return barcode;
}