#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>

#define MIN_HEIGHT 180.0f
#define MAX_HEIGHT 220.0f
#define MIN_WIDTH 80.0f
#define MAX_WIDTH 120.0f
#define MIN_DEPTH 50.0f
#define MAX_DEPTH 90.0f
#define CHIPBOARD_THICKNESS 1.5f
#define CHIPBOARD_DENSITY 0.75f
#define FIBERBOARD_THICKNESS 0.5f
#define FIBERBOARD_DENSITY 0.83f
#define WOOD_THICKNESS 1.0f
#define WOOD_DENSITY 0.65f
#define SHELF_DISTANCE 40.0f
#define GRAM_TO_KG 0.001f

float read_value(char* question, float minValue, float maxValue);

void main() {
	float h, w, d;
	float back_volume;
	float back_mass;
	float side_volume;
	float sides_mass;
	float top_volume;
	float top_down_mass;
	float doors_volume;
	float doors_mass;
	float shelf_volume;
	int shelf_amount;
	float shelves_mass;
	float mass;
	
	setlocale(LC_ALL, "rus");
	h = read_value("Введите высоту шкафа h в сантиметрах (180 <= h <= 220): ", MIN_HEIGHT, MAX_HEIGHT);
	w = read_value("Введите ширину шкафа w в сантиметрах (80 <= w <= 120): ", MIN_WIDTH, MAX_WIDTH);
	d = read_value("Введите глубину шкафа d в сантиметрах (50 <= d <= 90): ", MIN_DEPTH, MAX_DEPTH);

	back_volume = w * h * FIBERBOARD_THICKNESS;
	back_mass = FIBERBOARD_DENSITY * back_volume;

	side_volume = h * d * CHIPBOARD_THICKNESS;
	sides_mass = 2 * CHIPBOARD_DENSITY * side_volume;

	top_volume = w * d * CHIPBOARD_THICKNESS;
	top_down_mass = 2 * CHIPBOARD_DENSITY * top_volume;

	doors_volume = h * w * WOOD_THICKNESS;
	doors_mass = WOOD_DENSITY * doors_volume;

	shelf_volume = (w - 2 * CHIPBOARD_THICKNESS) * d * CHIPBOARD_THICKNESS;
	shelf_amount = (int)(h / (SHELF_DISTANCE + CHIPBOARD_THICKNESS));
	shelves_mass = shelf_amount * CHIPBOARD_DENSITY * shelf_volume;

	mass = (back_mass + sides_mass + top_down_mass + doors_mass + shelves_mass) * GRAM_TO_KG;

	printf("\nШкаф\nВысота: %f\nШирина: %f\nГлубина: %f\nМасса: %f\n", h, w, d, mass);
	
	system("pause");
}

float read_value(char* const question, float minValue, float maxValue) {
	int read_arguments;
	float value;

	while (1) {
		printf(question);
		read_arguments = scanf("%f", &value);
		while (getchar() != '\n');
		if (read_arguments == 1 && value >= minValue && value <= maxValue) {
			break;
		}
	}

	return value;
}