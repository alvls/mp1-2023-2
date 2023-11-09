#pragma once
#include "barcode.h"

typedef struct {
	Barcode barcode;
	char* name;
	unsigned int price;
	unsigned int discount;
} Product;

void product_print_info(const Product* product);