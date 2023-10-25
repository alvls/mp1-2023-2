#pragma once

#include "barcode.h"

typedef struct {
	Barcode barcode;
	char* name;
	char* description;
	unsigned int price;
	unsigned int discount;
} Product;

typedef struct {
	Product* products;
	size_t products_amount;
} ProductDatabase;

ProductDatabase load_product_database();
void free_product_database(ProductDatabase database);

void print_product_info(const Product* product);
Product* get_product_by_barcode(ProductDatabase database, Barcode barcode);