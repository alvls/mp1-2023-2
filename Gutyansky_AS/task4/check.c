#include <malloc.h>
#include <stdio.h>
#include <math.h>
#include "console_utils.h"
#include "check.h"

#define CHECK_INITIAL_CAPACITY 4

Check* check_create() {
	Check* check;
	CheckRecord* records;

	check = malloc(sizeof(Check));
	if (check == NULL) {
		return NULL;
	}

	records = (CheckRecord*)malloc(CHECK_INITIAL_CAPACITY * sizeof(CheckRecord));
	check->records = records;
	check->length = 0;
	check->memory_capacity = CHECK_INITIAL_CAPACITY;

	return check;
}

int check_valid(const Check* check) {
	return check != NULL && check->records != NULL && check->length <= check->memory_capacity;
}

int check_try_add_product(Check* check, const Product* product) {
	int i;
	Barcode product_code;
	CheckRecord* record;
	CheckRecord new_record;
	CheckRecord* reallocated_buffer;

	product_code = product->barcode;
	for (i = 0; i < check->length; i++) {
		record = &(check->records[i]);
		if (barcodes_equal(product_code, record->product.barcode)) {
			record->amount++;
			return 1;
		}
	}

	if (check->length == check->memory_capacity) {
		reallocated_buffer = realloc(check->records, (size_t)2 * check->memory_capacity * sizeof(CheckRecord));
		if (reallocated_buffer == NULL) {
			return 0;
		}

		check->memory_capacity *= (size_t)2;
		check->records = reallocated_buffer;
	}

	new_record.product = *product;
	new_record.amount = 1;

	check->records[check->length++] = new_record;
	return 1;
}

void check_print(const Check* check) {
	int i;
	unsigned int total_price;
	unsigned int total_discount;
	unsigned int total_sum;
	CheckRecord record;
	Product product;

	text_background(DARKGRAY);
	text_color(WHITE);
	printf("%-40s %-10s %-15s %-20s\n", "Название", "Кол-во", "Цена/шт(руб.)", "Общая стоимость(руб.)");
	text_background(BLACK);
	for (i = 0; i < check->length; i++) {
		record = check->records[i];
		product = record.product;
		printf("%-40s %-10u %-15u %-20u\n", product.name, record.amount, product.price, product.price * record.amount);
	}

	total_price = check_total_price(check);
	total_discount = check_total_discount(check);
	total_sum = check_total_sum(check);

	printf("\nОбщая стоимость: %uруб\nСкидка: %uруб\nИтог: %uруб\n", total_price, total_discount, total_sum);
}

void check_print_sum(const Check* check) {
	unsigned int total_sum;

	total_sum = check_total_sum(check);
	printf("К оплате: % uруб\n", total_sum);
}

unsigned int check_total_price(const Check* check) {
	unsigned int s;
	CheckRecord record;
	int i;

	s = 0;
	for (i = 0; i < check->length; i++) {
		record = check->records[i];
		s += record.product.price * record.amount;
	}

	return s;
}

unsigned int check_total_discount(const Check* check) {
	unsigned int s;
	unsigned int total;
	unsigned int discount_rubles;
	double discount;
	CheckRecord record;
	int i;

	s = 0;
	total = 0;
	for (i = 0; i < check->length; i++) {
		record = check->records[i];
		s += record.product.discount * record.amount;
		total += 100 * record.amount;
	}

	discount = (double)s / (double)total;
	discount_rubles = (unsigned int)floor((double)check_total_price(check) * discount);

	return discount_rubles;
}

unsigned int check_total_sum(const Check* check) {
	unsigned int price;
	unsigned int discount;
	unsigned int sum;

	price = check_total_price(check);
	discount = check_total_discount(check);
	sum = price - discount;
	
	return sum;
}

void check_free(Check* check) {
	free(check->records);
	free(check);
}


