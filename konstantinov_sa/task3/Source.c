#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<time.h>
#include<math.h>

#define Test

//random in range
int rir(int l, int r) {
	return round(rand() * ((double)(r - l) / RAND_MAX) + l);
}

void gennum( int n, int places[5], int digits[10]) {
	places[0] = rir(1, 9);
	digits[places[0]]=1;
	for (int i = 1; i < n; i++) {

		while (1) {
			int uniq = 1;
			int e = rir(0, 9);
			for (int k = 0; k < i; k++) {
				//printf("try %d to [%d] check [%d] = %d\n", e, i, k, a[k]);
				if ((places[k] == e)) {  // || ((i == 0) && (e == 0))
					uniq = 0;
					break;
				}
			}
			if (uniq)
			{
				places[i] = e;
				digits[e] = 1;
				break;
			}

		}
	}

#ifdef Test
	for (int i = 0; i < n; i++) {
		printf("%d", places[i]);
	}
	printf("\n");
	for (int i = 0; i < 10; i++) {
		printf("%d", i);
	}
	printf("\n");
	for (int i = 0; i < 10; i++) {
		printf("%d", digits[i]);
	}
#endif
}


int main() {
	setlocale(LC_ALL, "");
	srand(time(NULL));

	int n = 3;
	int num[5] = { -1,-1,-1,-1,-1 };
	int digits[10] = { 0 };
	
	gennum(n, num, digits);
	printf("\n");
	
	
	int vp = 0;
	while(vp != n) {
		vp = 0;
		int g, vd = 0;
		scanf("%d", &g);
		for (int i = n-1; i >= 0; i--) {
			int c = g % 10;
			g /= 10;
			printf("c %d d%d n%d \n", c, digits[c], num[i]);
			if (digits[c])
				vd++;
			if (num[i] == c)
				vp++;
		}
		printf("digits %d  positions %d\n", vd, vp);

	}


	//for (int i = 0; i < 10000;i++) {
	//	int e = rir(0, 9);
	//	//printf("%d", e);
	//	if (e == 10) {
	//		printf("\n!!!!\n");
	//	}
	//}
	system("pause");
}