#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE_BARCODE 5
#define SIZE_NAME 30

struct Models
{
	char name[SIZE_NAME]; // Model name
	char barcode[SIZE_BARCODE]; // Model barcode
	int price; // Model price $
	int quantity;
	int discount;
	float total; // Discounted price $
	
};

void main()
{	
	system("color F0");
	char user_code[SIZE_BARCODE];
	char stop[SIZE_BARCODE] = "stop";
	char list[SIZE_BARCODE] = "list";
	int i;
	char trash;
	int sum = 0; // Total without discount
	float total = 0;
	float total_discount;

	//-----
	struct Models gaz_24_01;
	strcpy(gaz_24_01.name, "Volga 24-01 1:43");
	strcpy(gaz_24_01.barcode, "2401");
	gaz_24_01.price = 100;
	gaz_24_01.quantity = 0;
	gaz_24_01.discount = 10;
	gaz_24_01.total = gaz_24_01.price * (1 - gaz_24_01.discount / 100.0);
	//-----

	//-----
	struct Models gaz_24_02;
	strcpy(gaz_24_02.name, "Volga 24-02 1:43");
	strcpy(gaz_24_02.barcode, "2402");
	gaz_24_02.price = 90;
	gaz_24_02.quantity = 0;
	gaz_24_02.discount = 15;
	gaz_24_02.total = gaz_24_02.price * (1 - gaz_24_02.discount / 100.0);
	//-----

	//-----
	struct Models vaz_2101;
	strcpy(vaz_2101.name, "Lada VAZ-2101 1:43");
	strcpy(vaz_2101.barcode, "2101");
	vaz_2101.price = 70;
	vaz_2101.quantity = 0;
	vaz_2101.discount = 5;
	vaz_2101.total = vaz_2101.price * (1 - vaz_2101.discount / 100.0);
	//-----

	//-----
	struct Models vaz_2102;
	strcpy(vaz_2102.name, "Lada VAZ-2102 1:43");
	strcpy(vaz_2102.barcode, "2102");
	vaz_2102.price = 75;
	vaz_2102.quantity = 0;
	vaz_2102.discount = 40;
	vaz_2102.total = vaz_2102.price * (1 - vaz_2102.discount / 100.0);
	//-----
	
	//-----
	struct Models kamaz_6560;
	strcpy(kamaz_6560.name, "Kamaz AA-13-60 (6560) 1:43");
	strcpy(kamaz_6560.barcode, "6560");
	kamaz_6560.price = 150;
	kamaz_6560.quantity = 0;
	kamaz_6560.discount = 20;
	kamaz_6560.total = kamaz_6560.price * (1 - kamaz_6560.discount / 100.0);
	//-----

	//-----
	struct Models paz_3205;
	strcpy(paz_3205.name, "PAZ-3205 1:43");
	strcpy(paz_3205.barcode, "3205");
	paz_3205.price = 115;
	paz_3205.quantity = 0;
	paz_3205.discount = 20;
	paz_3205.total = paz_3205.price * (1 - paz_3205.discount / 100.0);
	//-----

	//-----
	struct Models zil_131;
	strcpy(zil_131.name, "ZIL-131 1:43");
	strcpy(zil_131.barcode, "1311");
	zil_131.price = 150;
	zil_131.quantity = 0;
	zil_131.discount = 15;
	zil_131.total = zil_131.price * (1 - zil_131.discount / 100.0);
	//-----

	//-----
	struct Models zil_130;
	strcpy(zil_130.name, "ZIL-130 1:43");
	strcpy(zil_130.barcode, "1301");
	zil_130.price = 140;
	zil_130.quantity = 0;
	zil_130.discount = 10;
	zil_130.total = zil_130.price * (1 - zil_130.discount / 100.0);
	//-----

	//-----
	struct Models uaz_452;
	strcpy(uaz_452.name, "UAZ-452 1:43");
	strcpy(uaz_452.barcode, "4523");
	uaz_452.price = 50;
	uaz_452.quantity = 0;
	uaz_452.discount = 5;
	uaz_452.total = uaz_452.price * (1 - uaz_452.discount / 100.0);
	//-----

	//-----
	struct Models uaz_469;
	strcpy(uaz_469.name, "UAZ-469 1:43");
	strcpy(uaz_469.barcode, "4695");
	uaz_469.price = 60;
	uaz_469.quantity = 0;
	uaz_469.discount = 25;
	uaz_469.total = uaz_469.price * (1 - uaz_469.discount / 100.0);
	//-----

	printf("Welcome to cash register!\nYou can use these keywords:\n\t\'list\' - the program will show you all the barcodes;\n\t\'stop\' - the program will finish scanning the barcodes.\nThe allowed barcode length is 4 characters.\n");
	printf("------------------------------------------------------------------------------\n\n");
	do
	{	
		printf("--> ");
		fgets(user_code, SIZE_BARCODE, stdin);
		scanf("%c", &trash);

		for (i = 0; i < SIZE_BARCODE; i++)
			user_code[i] = tolower(user_code[i]);

		if (strcmp(user_code, list) == 0)
		{
			printf("Barcode\t\t\tModel\n\n\n");
			printf("%s\t\t\t%s\n", gaz_24_01.barcode, gaz_24_01.name);
			printf("%s\t\t\t%s\n", gaz_24_02.barcode, gaz_24_02.name);
			printf("%s\t\t\t%s\n", vaz_2101.barcode, vaz_2101.name);
			printf("%s\t\t\t%s\n", vaz_2102.barcode, vaz_2102.name);
			printf("%s\t\t\t%s\n", kamaz_6560.barcode, kamaz_6560.name);
			printf("%s\t\t\t%s\n", paz_3205.barcode, paz_3205.name);
			printf("%s\t\t\t%s\n", zil_131.barcode, zil_131.name);
			printf("%s\t\t\t%s\n", zil_130.barcode, zil_130.name);
			printf("%s\t\t\t%s\n", uaz_452.barcode, uaz_452.name);
			printf("%s\t\t\t%s\n", uaz_469.barcode, uaz_469.name);
		}
		else if (strcmp(user_code, gaz_24_01.barcode) == 0)
		{
			total += gaz_24_01.total;
			sum += gaz_24_01.price;
			gaz_24_01.quantity++;
			printf("Name: %s\nPrice: $%d\nQuantity: %d\n", gaz_24_01.name, gaz_24_01.price, gaz_24_01.quantity);
		}
		else if (strcmp(user_code, gaz_24_02.barcode) == 0)
		{
			total += gaz_24_02.total;
			sum += gaz_24_02.price;
			gaz_24_02.quantity++;
			printf("Name: %s\nPrice: $%d\nQuantity: %d\n", gaz_24_02.name, gaz_24_02.price, gaz_24_02.quantity);
		}
		else if (strcmp(user_code, vaz_2101.barcode) == 0)
		{
			total += vaz_2101.total;
			sum += vaz_2101.price;
			vaz_2101.quantity++;
			printf("Name: %s\nPrice: $%d\nQuantity: %d\n", vaz_2101.name, vaz_2101.price, vaz_2101.quantity);
		}
		else if (strcmp(user_code, vaz_2102.barcode) == 0)
		{
			total += vaz_2102.total;
			sum += vaz_2102.price;
			vaz_2102.quantity++;
			printf("Name: %s\nPrice: $%d\nQuantity: %d\n", vaz_2102.name, vaz_2102.price, vaz_2102.quantity);
		}
		else if (strcmp(user_code, kamaz_6560.barcode) == 0)
		{
			total += kamaz_6560.total;
			sum += kamaz_6560.price;
			kamaz_6560.quantity++;
			printf("Name: %s\nPrice: $%d\nQuantity: %d\n", kamaz_6560.name, kamaz_6560.price, kamaz_6560.quantity);
		}
		else if (strcmp(user_code, paz_3205.barcode) == 0)
		{
			total += paz_3205.total;
			sum += paz_3205.price;
			paz_3205.quantity++;
			printf("Name: %s\nPrice: $%d\nQuantity: %d\n", paz_3205.name, paz_3205.price, paz_3205.quantity);
		}
		else if (strcmp(user_code, zil_131.barcode) == 0)
		{
			total += zil_131.total;
			sum += zil_131.price;
			zil_131.quantity++;
			printf("Name: %s\nPrice: $%d\nQuantity: %d\n", zil_131.name, zil_131.price, zil_131.quantity);
		}
		else if (strcmp(user_code, zil_130.barcode) == 0)
		{
			total += zil_130.total;
			sum += zil_130.price;
			zil_130.quantity++;
			printf("Name: %s\nPrice: $%d\nQuantity: %d\n", zil_130.name, zil_130.price, zil_130.quantity);
		}
		else if (strcmp(user_code, uaz_452.barcode) == 0)
		{
			total += uaz_452.total;
			sum += uaz_452.price;
			uaz_452.quantity++;
			printf("Name: %s\nPrice: $%d\nQuantity: %d\n", uaz_452.name, uaz_452.price, uaz_452.quantity);
		}
		else if (strcmp(user_code, uaz_469.barcode) == 0)
		{
			total += uaz_469.total;
			sum += uaz_469.price;
			uaz_469.quantity++;
			printf("Name: %s\nPrice: $%d\nQuantity: %d\n", uaz_469.name, uaz_469.price, uaz_469.quantity);
		}
		else
			printf("No such barcode.\n");
		printf("\n");
	} while (strcmp(user_code, stop) != 0 );

	if (sum == 0)
	{
		printf("No products.\n");
		system("pause");
		return;
	}
	total_discount = 100 * ( 1 - total / sum);
	system("cls");
	printf("\t\t\t-----LEVONYCHEV CO.-----\n\n");
	printf("------------------------------------------------------------------------------");
	printf("\nPrice\t\tDiscounted Price\t\tQuantity\t\tResult\n");
	if (gaz_24_01.quantity > 0)
	if (gaz_24_01.quantity > 0)
	{	
		printf("\n%s\n", gaz_24_01.name);
		printf("$%d\t\t$%g(-%d%%)\t\t\t%d\t\t\t$%g\n", gaz_24_01.price, gaz_24_01.total,gaz_24_01.discount, gaz_24_01.quantity, gaz_24_01.total * gaz_24_01.quantity);
	}
	if (gaz_24_02.quantity > 0)
	{
		printf("\n%s\n", gaz_24_02.name);
		printf("$%d\t\t$%g(-%d%%)\t\t\t%d\t\t\t$%g\n", gaz_24_02.price, gaz_24_02.total, gaz_24_02.discount, gaz_24_02.quantity, gaz_24_02.total * gaz_24_02.quantity);
	}
	if (vaz_2101.quantity > 0)
	{
		printf("\n%s\n", vaz_2101.name);
		printf("$%d\t\t$%g(-%d%%)\t\t\t%d\t\t\t$%g\n", vaz_2101.price, vaz_2101.total, vaz_2101.discount, vaz_2101.quantity, vaz_2101.total * vaz_2101.quantity);
	}
	if (vaz_2102.quantity > 0)
	{
		printf("\n%s\n", vaz_2102.name);
		printf("$%d\t\t$%g(-%d%%)\t\t\t%d\t\t\t$%g\n", vaz_2102.price, vaz_2102.total, vaz_2102.discount, vaz_2102.quantity, vaz_2102.total * vaz_2102.quantity);
	}
	if (kamaz_6560.quantity > 0)
	{
		printf("\n%s\n", kamaz_6560.name);
		printf("$%d\t\t$%g(-%d%%)\t\t\t%d\t\t\t$%g\n", kamaz_6560.price, kamaz_6560.total, kamaz_6560.discount, kamaz_6560.quantity, kamaz_6560.total * kamaz_6560.quantity);
	}
	if (paz_3205.quantity > 0)
	{
		printf("\n%s\n", paz_3205.name);
		printf("$%d\t\t$%g(-%d%%)\t\t\t%d\t\t\t$%g\n", paz_3205.price, paz_3205.total, paz_3205.discount, paz_3205.quantity, paz_3205.total * paz_3205.quantity);
	}
	if (zil_131.quantity > 0)
	{
		printf("\n%s\n", zil_131.name);
		printf("$%d\t\t$%g(-%d%%)\t\t\t%d\t\t\t$%g\n", zil_131.price, zil_131.total, zil_131.discount, zil_131.quantity, zil_131.total * zil_131.quantity);
	}
	if (zil_130.quantity > 0)
	{
		printf("\n%s\n", zil_130.name);
		printf("$%d\t\t$%g(-%d%%)\t\t\t%d\t\t\t$%g\n", zil_130.price, zil_130.total, zil_130.discount, zil_130.quantity, zil_130.total * zil_130.quantity);
	}
	if (uaz_452.quantity > 0)
	{
		printf("\n%s\n", uaz_452.name);
		printf("$%d\t\t$%g(-%d%%)\t\t\t%d\t\t\t$%g\n", uaz_452.price, uaz_452.total, uaz_452.discount, uaz_452.quantity, uaz_452.total * uaz_452.quantity);
	}
	if (uaz_469.quantity > 0)
	{
		printf("\n%s\n", uaz_469.name);
		printf("$%d\t\t$%g(-%d%%)\t\t\t%d\t\t\t$%g\n", uaz_469.price, uaz_469.total, uaz_469.discount, uaz_469.quantity, uaz_469.total * uaz_469.quantity);
	}
	printf("------------------------------------------------------------------------------");
	printf("\nTOTAL: $%d", sum);
	printf("\nTOTAL with a discount(-%%%0.1f): $%g\n", total_discount, total);
	printf("------------------------------------------------------------------------------\n");
	system("pause");
	return;
}