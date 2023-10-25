#include <stdio.h>
#include <malloc.h>
#include "product.h"

ProductDatabase load_product_database()
{
	const int products_amount = 1;
	Product* productArray = (Product*)malloc(products_amount * sizeof(Product));
	productArray[0].barcode = create_barcode('0','0','0','1');
	productArray[0].name = "Сок J7 Апельсин с мякотью";
	productArray[0].price = 165;
	productArray[0].discount = 10;
	
	ProductDatabase database = {
		.products = productArray,
		.products_amount = products_amount
	};

	return database;
}

void free_product_database(ProductDatabase database)
{
	free(database.products);
}

void print_product_info(const Product* product)
{
	printf("Наименование: %s\n\
Цена: %d\n\
Скидка: %d%%", product->name, product->price, product->discount);
}

Product* get_product_by_barcode(ProductDatabase database, Barcode barcode)
{
	int i;
	int amount = database.products_amount;
	Product* products = database.products;

	for (i = 0; i < amount; i++) {
		if (barcodes_equal(products[i].barcode, barcode)) {
			return &products[i];
		}
	}

	return NULL;
}
