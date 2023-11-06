#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>
#include "console_utils.h"
#include "product_database.h"
#include "check.h"

typedef enum ApplicationState {
	MAIN_MENU,
	PRODUCT_INFO,
	ADD_PRODUCT,
	CHECK_INFO,
	TOTAL_PRICE,
	EXIT
} ApplicationState;

void user_loop(ProductDatabase* database, Check* check);
Barcode read_barcode(void);
ApplicationState main_menu(void);
ApplicationState product_info_menu(ProductDatabase* database, Check* check);
ApplicationState add_product_menu(ProductDatabase* database, Check* check);
ApplicationState check_info_menu(Check* check);
ApplicationState total_price_menu(Check* check);

void main(void) {
	setlocale(LC_ALL, "rus");
	set_window_wh(120, 40);

	ProductDatabase* database = product_database_load();
	if (!product_database_valid(database)) {
		text_color(RED);
		printf("Ошибка: не удалось загрузить базу данных товаров!\n");
		system("pause");
		return;
	}

	Check* check = check_create();
	if (!check_valid(check)) {
		text_color(RED);
		printf("Ошибка: не хватает памяти для создания чека!\n");
		product_database_free(database);
		system("pause");
		return;
	}

	user_loop(database, check);

	product_database_free(database);
	check_free(check);
}

void user_loop(ProductDatabase* database, Check* check) {
	ApplicationState app_state = MAIN_MENU;

	while (app_state != EXIT) {
		switch (app_state) {
		case MAIN_MENU:
			app_state = main_menu();
			break;
		case PRODUCT_INFO:
			app_state = product_info_menu(database, check);
			break;
		case ADD_PRODUCT:
			app_state = add_product_menu(database, check);
			break;
		case CHECK_INFO:
			app_state = check_info_menu(check);
			break;
		case TOTAL_PRICE:
			app_state = total_price_menu(check);
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
		printf("E-КАССА");

		set_cursor_at(0, 2);
		text_background(BLACK);
		printf("Выберите действие:");
		set_cursor_at(0, 3);
		printf("1. Узнать информацию о товаре");
		set_cursor_at(0, 4);
		printf("2. Добавить товар в чек");
		set_cursor_at(0, 5);
		printf("3. Посмотреть чек");
		set_cursor_at(0, 6);
		printf("4. Узнать итоговую стоимость");
		set_cursor_at(0, 7);
		printf("5. Выйти");
		set_cursor_at(0, 8);
		printf(">>> ");
	} while (!try_read_int(&choice, 1, 5));

	set_cursor_visible(1);

	switch (choice)
	{
	case 1:
		return PRODUCT_INFO;
	case 2:
		return ADD_PRODUCT;
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

ApplicationState product_info_menu(ProductDatabase* database, Check* check) {
	Barcode barcode;
	Product* product;
	int choice;

	barcode = read_barcode();
	product = product_get_by_barcode(database, barcode);
	
	if (product == NULL) {
		do {
			set_cursor_at(0, 0);
			clear_screen();
			printf("Товар с таким штрихкодом не существует!\n\
1. Сканировать другой товар\n\
2. Назад\n\
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
			product_print_info(product);
			printf("\n1. Добавить в чек\n\
2. Сканировать другой товар\n\
3. Назад\n\
>>> ");
		} while (!try_read_int(&choice, 1, 3));

		switch (choice) {
		case 1:
			if (!check_try_add_product(check, product)) {
				text_color(RED);
				printf("Ошибка: не хватает памяти для создания чека!\n");
				system("pause");
				text_color(WHITE);
			}
			return MAIN_MENU;
		case 2:
			return PRODUCT_INFO;
		case 3:
			return MAIN_MENU;
		}
	}

	return MAIN_MENU;
}

ApplicationState add_product_menu(ProductDatabase* database, Check* check) {
	Barcode barcode;
	Product* product;
	int choice;

	barcode = read_barcode();
	product = product_get_by_barcode(database, barcode);

	if (product == NULL) {
		do {
			set_cursor_at(0, 0);
			clear_screen();
			printf("Товар с таким штрихкодом не существует!\n\
1. Сканировать другой товар\n\
2. Назад\n\
>>> ");
		} while (!try_read_int(&choice, 1, 2));

		switch (choice) {
		case 1:
			return ADD_PRODUCT;
		case 2:
			return MAIN_MENU;
		}
	}

	if (!check_try_add_product(check, product)) {
		text_color(RED);
		printf("Ошибка: не хватает памяти для создания чека!\n");
		system("pause");
		text_color(WHITE);
	}

	return MAIN_MENU;
}

ApplicationState check_info_menu(Check* check) {
	clear_screen();
	set_cursor_at(0, 0);
	check_print(check);
	system("pause");
	return MAIN_MENU;
}

ApplicationState total_price_menu(Check* check) {
	clear_screen();
	set_cursor_at(0, 0);
	check_print_sum(check);
	system("pause");
	return MAIN_MENU;
}

Barcode read_barcode(void) {
	int read_params;
	int read_chars;
	char buffer[5];
	Barcode barcode;
	char is_barcode_valid;

	do {
		clear_screen();
		set_cursor_at(0, 0);
		printf("Введите штрихкод (4 символа от 0 до 9):\n>>> ");
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
			}
			barcode = create_barcode(buffer[0], buffer[1], buffer[2], buffer[3]);
		}
	} while (!is_barcode_valid);

	return barcode;
}