#pragma once

typedef struct {
	char values[4];
} Barcode;

Barcode create_barcode(char a, char b, char c, char d);
int barcodes_equal(Barcode a, Barcode b);