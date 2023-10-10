#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void mode_1() {
	int n = (rand() % 999) + 1; // zagadannoe chislo [1, 999]
	//printf_s("%i\n", n);
	int inp = 0, count = 0;
	printf_s("Try to guess my number. Note: it's between 0 and 1000\n");


	while (inp != n) {
		count += 1;
		scanf_s("%i", &inp);
		while (getchar() != '\n') {}
		if (inp > n) { printf_s("no, my number is smaller\n"); }
		if (inp < n) { printf_s("no, my number is bigger\n"); }
	}
	printf_s("Congratulations, it's %i\n", n);
	printf_s("It took you %i attempts \n", count);
}

int mode_2() {
	int user_num = 0;
	printf_s("Note: '<' stands for 'less', '>' stands for 'more', '=' stands for 'equal \n");
	printf_s("Please, enter your number from 1 to 999: ");
	scanf_s("%i", &user_num);
	printf_s("\n");

	int v_gr = 1000, n_gr = 0; // (0;1000) == [1, 999]
	int our_num = 0;
	int guessed = 0;
	int counter = 0;
	char inp = "1";


	while (guessed == 0)
	{
		our_num = (v_gr + n_gr) / 2;

		printf_s("Your number is %i?\n", our_num);
		scanf_s("\n%c", &inp);


		if (inp == '>')
		{
			n_gr = our_num;
			counter += 1;
		}
		else
		{
			if (inp == '<') 
			{
				v_gr = our_num;
				counter += 1;
			}
			else 
			{
				if ((inp == '=') && (our_num == user_num)) { guessed = 1; counter += 1; }
				else { guessed = -1; }
			}
		}


		if ((v_gr - n_gr < 2) || (guessed == -1)) 
		{ 
			printf_s("Error, please restart..\n"); 
			return -1;
		}
	}

	printf_s("Your number is %i and it was guessed in %i attempts \n", our_num, counter);

	return 0;
}



void main() {

	srand(time(NULL));
	printf_s("Hello, what mode do you want to play?\n");
	char inp = ' ';
	int res = 0;


	while (inp != 'l')
	{
		scanf_s("\n%c", &inp);
		while (getchar() != '\n') {}

		if (inp == 'l') { continue; }

		if (inp == '1') 
		{ 
			printf_s("Starting mode_1\n");
			mode_1();
		}
		else 
		{
			if (inp == '2')
			{
				printf_s("Starting mode_2\n");
				mode_2();
			}
			else 
			{
				printf_s("This mode isn't available now\n");
				continue;
			}
		}
		printf_s("Enter 'l' if you want to leave and '1' or '2' if you want to play again\n");
	}

	printf_s("This is the end of user-friendly programm \n");
	system("pause");


}