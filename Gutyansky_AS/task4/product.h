#pragma once

#include "barcode.h"

typedef struct {
	Barcode barcode;
	char* name;
	char* description;
	unsigned int price;
	unsigned int discount;
} Product;

void print_product_info(const Product* product);
Product* get_product_by_barcode(Barcode barcode);