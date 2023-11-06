#include <stdio.h>
#include "product.h"
#include "console_utils.h"

void product_print_info(const Product* product) {
	text_background(DARKGRAY);
	text_color(WHITE);
	printf("%-40s %-15s %-10s\n", "Название", "Цена/шт(руб.)", "Скидка");
	text_background(BLACK);
	printf("%-40s %-15u %u%%\n", product->name, product->price, product->discount);
}
