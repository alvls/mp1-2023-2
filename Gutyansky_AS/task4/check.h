#pragma once
#include "product.h"

typedef struct {
	Product product;
	unsigned int amount;
} CheckRecord;

typedef struct {
	CheckRecord* records;
	size_t length;
	size_t memory_capacity;
} Check;

Check* check_create(void);
void check_free(Check* check);
int check_valid(const Check* check);
int check_try_add_product(Check* check, const Product* product);
void check_print(const Check* check);
void check_print_sum(const Check* check);
unsigned int check_total_price(const Check* check);
unsigned int check_total_discount(const Check* check);
unsigned int check_total_sum(const Check* check);