#pragma once
#include "product.h"

typedef struct {
	Product* products;
	unsigned int products_amount;
} ProductDatabase;

ProductDatabase* product_database_load(void);
int product_database_valid(const ProductDatabase* database);
void product_database_free(ProductDatabase* database);
Product* product_get_by_barcode(const ProductDatabase* database, Barcode barcode);