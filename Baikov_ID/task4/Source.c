#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Структура для представления товара
struct Product {
    char bar_code[5]; // Штрихкод
    char name[100];   // Наименование
    int price;        // Стоимость за единицу
    int discount;     // Скидка
};

// Массив товаров
struct Product products[10] = {
    { "1234", "Eggs", 100 },
    { "1111", "Bread", 40 },
    { "2222", "Chocolate", 50 },
    { "3333", "Milk", 89 },
    { "4444", "Oat Milk", 89 },
    { "5555", "Meat", 400 },
    { "6666", "Butter", 150 },
    { "7777", "Beans", 200 },
    { "8888", "Coffee", 200 },
    { "9999", "Fish", 350 }
};

// Функция для сканирования
void scanProduct(struct Product* product) {
    printf("Enter the barcode from the existing ones (1234, 1111, 2222, 3333, 4444, 5555, 6666, 7777, 8888, 9999): ");
    scanf("%s", product->bar_code);

    // Проверяем валидность штрих-кода
    int isValidBarcode = 0;
    for (int i = 0; i < sizeof(products) / sizeof(struct Product); ++i) {
        if (strcmp(products[i].bar_code, product->bar_code) == 0) {
            isValidBarcode = 1;
            break;
        }
    }

    if (!isValidBarcode) {
        printf("Invalid barcode.\n");
        memset(product, 0, sizeof(struct Product)); // Сброс структуры товара
        return;
    }

    // Генерируем случайную скидку от 5% до 50% с шагом 5%
    product->discount = rand() % 10 * 5 + 5;

    // Находим соответствующий товар в массиве
    for (int i = 0; i < sizeof(products) / sizeof(struct Product); ++i) {
        if (strcmp(products[i].bar_code, product->bar_code) == 0) { //strcmp возвращает 0, если строки идентичны.
            // Заполняем структуру данными из массива товаров
            strcpy(product->name, products[i].name); // позволяет структуре product хранить информацию о товаре
            product->price = products[i].price; //Присваивает цену товара из массива products структуре product
            break;
        }
    }
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
            printf("Name: %s\nPrice for a single one: %d rub\nAmount of products: %d\nTotal price: %d rub\n", product.name, product.price, aItems, aCost);
            break;
        case 5:
            printf("Total price: %d rubles\n", aCost);
            printf("Total discount: %d rubles\n", aDiscount);
            break;
        case 0:
            return 0;
        default:
            printf("Incorrect choice.\n");
            break;
        }
    }

    return 0;
}