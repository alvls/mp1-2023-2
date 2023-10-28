#include <stdio.h>
#include <malloc.h>
#include "product.h"
#include "console_utils.h"

ProductDatabase* product_database_load() {
	const int products_amount = 5;

	ProductDatabase* database;
	Product* products;

	database = malloc(sizeof(ProductDatabase));
	if (database == NULL) {
		return NULL;
	}

	products = (Product*)malloc(products_amount * sizeof(Product));
	if (products != NULL) {
		products[0].barcode = create_barcode('0', '0', '0', '1');
		products[0].name = "Сок J7 Апельсин с мякотью";
		products[0].price = 165;
		products[0].discount = 10;

		products[1].barcode = create_barcode('0', '0', '2', '1');
		products[1].name = "Драже M&M's с арахисом";
		products[1].price = 60;
		products[1].discount = 15;

		products[2].barcode = create_barcode('0', '5', '2', '1');
		products[2].name = "Масло сливочное Экомилк";
		products[2].price = 200;
		products[2].discount = 30;

		products[3].barcode = create_barcode('0', '6', '6', '0');
		products[3].name = "Шоколадный батончик";
		products[3].price = 80;
		products[3].discount = 20;

		products[4].barcode = create_barcode('1', '2', '3', '4');
		products[4].name = "Чеснок";
		products[4].price = 34;
		products[4].discount = 10;
	}
	
	database->products = products;
	database->products_amount = products_amount;

	return database;
}

int product_database_valid(const ProductDatabase* database) {
	return database != NULL && database->products != NULL;
}

void product_database_free(ProductDatabase* database) {
	free(database->products);
	free(database);
}

void product_print_info(const Product* product) {
	text_background(DARKGRAY);
	text_color(WHITE);
	printf("%-40s %-15s %-10s\n", "Название", "Цена/шт(руб.)", "Скидка");
	text_background(BLACK);
	printf("%-40s %-15u %u%%\n", product->name, product->price, product->discount);
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
