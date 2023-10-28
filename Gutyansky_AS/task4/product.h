#pragma once

#include "barcode.h"

typedef struct {
	Barcode barcode;
	char* name;
	unsigned int price;
	unsigned int discount;
} Product;

typedef struct {
	Product* products;
	unsigned int products_amount;
} ProductDatabase;

ProductDatabase* product_database_load();
int product_database_valid(const ProductDatabase* database);
void product_database_free(ProductDatabase* database);

void product_print_info(const Product* product);
Product* product_get_by_barcode(const ProductDatabase* database, Barcode barcode);