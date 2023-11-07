#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

// Структура для представления товара
struct Product {
    char bar_code[5]; // Штрихкод
    char name[100];  // Наименование
    int price;       // Стоимость за единицу
    int discount;    // Скидка
};

// Функция для сканирования
void scanProduct(struct Product* product) {
    printf("Enter bar code(4 numbers): ");
    scanf("%s", product->bar_code);
    printf("Enter the name of product: ");
    scanf(" %[^\n]s", product->name);
    printf("Enter the price in rubles: ");
    scanf("%d", &product->price);
    printf("Enter the dicount: ");
    scanf("%d", &product->discount);
}

// Функция для расчета общей стоимости товара
double calc(int quantity, int price, int discount) {
    
    double discountedPrice = price * (1 - discount / 100.0);
    return quantity * discountedPrice;

}

int main() {

    int aCost = 0;
    int aDiscount = 0;
    int aItems = 0;
    
    struct Product product;

    while (1) {
        
        int choice;

        printf("\nChoose an operation:\n");
        printf("1. Scan the product\n");
        printf("2. Output the product description\n");
        printf("3. Add the product to the cheque\n");
        printf("4. Create the cheque\n");
        printf("5. Calculate total price\n");
        printf("0. Exit\n");
        printf("Your choice: ");

        scanf("%d", &choice);

        printf("\n");

        switch (choice) {
        
        case 1:

            scanProduct(&product);
            break;

        case 2:

            printf("Bar code: %s\n", product.bar_code);
            printf("Name: %s\n", product.name);
            printf("Price: %d rub\n", product.price);
            printf("Discount: %d%%\n", product.discount);
            break;

        case 3: {
            
            int amount;
            printf("Enter the amount of products: ");
            scanf("%d", &amount);

            if (amount <= 0) {
                printf("Invalid quantity.\n");
                break;
            }

            int itemCost = calc(amount, product.price, product.discount);
            aCost += itemCost;
            aDiscount += (amount * product.price - itemCost);
            aItems += amount;

            printf("Product is added\n");
            break;
        }
        case 4:
            
            printf("Cheque:\n");
            printf("Name: %s \nPrice for a single one: %d \nAmount of products: %d \nTotal price: %d \n", product.name, product.price, aItems, aCost);
            break;
        
        case 5:
            
            printf("Total price: %d rubles\n", aCost);
            printf("Total discount: %d rubles\n", aDiscount);
            break;

        case 0:   

            return 0;

        default:
            printf("Incorrect choice :) \n");
            break;
        }
    }

    return 0;
}