#include "barcode.h"

Barcode create_barcode(char a, char b, char c, char d) {
	Barcode barcode;
	barcode.values[0] = a;
	barcode.values[1] = b;
	barcode.values[2] = c;
	barcode.values[3] = d;

	return barcode;
}

int barcodes_equal(Barcode a, Barcode b) {
	int i;

	for (i = 0; i < 4; i++) {
		if (a.values[i] != b.values[i]) {
			return 0;
		}
	}
	
	return 1;
}
