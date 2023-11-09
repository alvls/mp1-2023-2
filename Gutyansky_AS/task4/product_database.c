#define _CRT_SECURE_NO_WARNINGS

#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include "product_database.h"

#define MAX_PRODUCTS_IN_DATABASE 10000

Product* load_products_from_file(const char* const filename, unsigned int* products_amount);

ProductDatabase* product_database_load(void) {
	const char* const filename = "database.dat";

	ProductDatabase* database;
	Product* products;
	unsigned int products_amount;

	database = malloc(sizeof(ProductDatabase));
	if (!database) {
		return NULL;
	}

	products = load_products_from_file(filename, &products_amount);
	if (!products) {
		free(database);
		return NULL;
	}

	database->products = products;
	database->products_amount = products_amount;

	return database;
}

int product_database_valid(const ProductDatabase* database) {
	return database != NULL && database->products != NULL;
}

void product_database_free(ProductDatabase* database) {
	unsigned int i;
	Product* products = database->products;
	for (i = 0; i < database->products_amount; i++) {
		if (products[i].name) {
			free(products[i].name);
		}
	}
	free(products);
	free(database);
}

Product* product_get_by_barcode(const ProductDatabase* database, Barcode barcode) {
	int i;
	int amount = database->products_amount;
	Product* products = database->products;

	for (i = 0; i < amount; i++) {
		if (barcodes_equal(products[i].barcode, barcode)) {
			return &products[i];
		}
	}

	return NULL;
}

Product* load_products_from_file(const char* const filename, unsigned int* products_amount) {
	Product* products;
	FILE* db_file;
	int read_res;
	char barcode_buffer[5];
	char product_name_buffer[128];
	int read_barcode_length;
	int read_name_length;
	char* temp_name;
	unsigned int product_price;
	unsigned int product_discount;
	int valid;
	unsigned int i;

	db_file = fopen(filename, "r");
	if (!db_file) {
		return NULL;
	}

	if (fscanf(db_file, "%u\n", products_amount) != 1
		|| *products_amount < 1 || *products_amount > MAX_PRODUCTS_IN_DATABASE) {
		fclose(db_file);
		return NULL;
	}

	products = (Product*)malloc(*products_amount * sizeof(Product));
	if (!products) {
		fclose(db_file);
		return NULL;
	}

	valid = 1;
	for (i = 0; i < *products_amount; i++) {
		read_res = fscanf(db_file, "%4[^;]%n;%127[^;]%n;%u;%u\n", barcode_buffer, &read_barcode_length,
			product_name_buffer, &read_name_length, &product_price, &product_discount);
		// string data + '\0'
		read_name_length -= read_barcode_length;
		if (read_res != 4 || read_barcode_length != 4 || read_name_length == 0) {
			valid = 0;
			break;
		}
		temp_name = (char*)malloc(read_name_length * sizeof(char));
		if (!temp_name) {
			valid = 0;
			break;
		}
		strncpy(temp_name, product_name_buffer, read_name_length);
		products[i].barcode = create_barcode(barcode_buffer[0], barcode_buffer[1], barcode_buffer[2], barcode_buffer[3]);
		products[i].name = temp_name;
		products[i].price = product_price;
		products[i].discount = product_discount;
	}

	if (!valid) {
		while (i > 0) {
			i--;
			free(products[i].name);
		}
		free(products);
		products = NULL;
	}

	fclose(db_file);

	return products;
}