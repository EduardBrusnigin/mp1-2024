#include "locale.h"
#include "windows.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>


int state;


float genRand() {
	return (float)rand() - 16383;
}


void fillRandList(float list[5000], int n) {
	for (int i = 0; i < n; i++) list[i] = genRand(); /*list[i] = 4;*/
}


int check(float a, float b, int *h) {
	(*h)++;
	return (a > b);
}


void swap(float *a, float *b, int *h) {
	float c;
	c = *a;
	*a = *b;
	*b = c;
	(*h)++;
}


int checkListSorted(float* list, int n) {
	int i = 0;
	int ch = 1;
	while ((i < n) || ch == 1) ch = list[i] < list[++i];
	return ch;
}


void DoubleBubble(float* list, int n, int* checks, int* swaps) {
	int l = 0, r = 0;
	int dlt = 0;
	for (int i = 0; (i < n) || (l + r) < n; i++) {
		//����� ������.
		if (i % 2) {
			dlt = 1;
			for (int j = l; j + r - 1 < n; j++) {
				//printf("%d ", j);
				if (check(list[j], list[j + 1], checks)) {
					swap(&list[j], &list[j + 1], swaps);
					dlt = 1;
				}
				else dlt++;
			}
			r += dlt;
		}
		//����� �����.
		else {
			dlt = 1;
			for (int j = n - r - 1; j > l; j--) {
				//printf("%d ", j);
				if (check(list[j - 1], list[j], checks)) {
					swap(&list[j - 1], &list[j], swaps);
					dlt = 1;
				}
				else dlt++;
			}
			l += dlt;
		}
	}
}


void listPrint(float list[5000], int n) {
	int np;
	//����� 10<= ��-�� �������.
	np = min(n, 10);
	printf("%.2f", list[0]);
	for (int i = 1; i < np; i++) {
		printf(" %.2f", list[i]);
	}
	if (n > 10) {
		printf("...");
	}
}


//state = 0: ���� - ��������� �������
void showBaseScreen(float list[5000], int n) {
	int input;
	listPrint(list, n);

	//������ ������.
	printf("\n1) ��������� ������ (������ ��� n < 11).\n");
	printf("2) �������� ��������� ������.\n");
	printf("3) �������� ������ �������.\n");
	printf("\n4) ������������� ������.\n");
	printf("\n25) �����.\n");

	input = 0;
	scanf_s("%d", &input);
	switch (input) {
	case(1): state = 1; break;
	case(2): fillRandList(list, n); printf("������ �������� ������������;)\n"); break;
	case(3): state = 2; break;
	case(4): state = 3; break;
	case(25): state = 255; break;
	}
}


//state = 1: ��������������� ����� �������.
void manualFillScreen(float list[10], int n) {
	if (n > 10) {
		printf("\n������ ������� �������: ������� �������� ������ �������.\n");
	}
	else {
		printf("\n�� ������ ������� �������� �������.\n");
		for (int i = 0; i < n; i++) scanf_s("%f", &list[i]);
	}
	state = 0;
}


//state = 2: ��������� ������� �������.
void listSizeChangeScreen(float list[5000], int *n) {
	int input = 0;
	printf("\n������ ������� ��������� �� 2 - 5000 ���������,\n �� ������ ������ ������ ������� - %d\n", *n);
	scanf_s("%d", &input);
	while ((input < 2) || (input > 5000)) {
		printf("������������ ������ �������.\n");
		scanf_s("%d", &input);
	}
	if (input > *n) {
		for (int i = *n; i < input; i++) list[i] = genRand();
	}
	*n = input;
	state = 0;
}

//state = 3: ����������
void sortScreen(float list[5000], int n, LARGE_INTEGER freq) {
	int input;
	LARGE_INTEGER start, finish;
	int checks = 0, swaps = 0;
	float* sr_list = (float*)malloc(sizeof(float) * n);
	state = 0;
	
	if (sr_list == NULL) printf("\n��� ������((.\n");
	else {
		listPrint(list, n);
		printf("\n������ = %d\n", sizeof(float) * n);
		memcpy(sr_list, list, sizeof(float) * n);

		printf("\n1) ��������������� ������.\n");
		printf("2) �������� ��������� ������.\n");
		printf("3) �������� ������ �������.\n");
		printf("\n4) ������������� ������.\n");
		scanf_s("%d", &input);

		
		QueryPerformanceCounter(&start);
		switch (input) {
		case(1):
			DoubleBubble(sr_list, n, &checks, &swaps);break;
		}
		QueryPerformanceCounter(&finish);
		printf("����� ����������: %lf\n", (double)(finish.QuadPart - start.QuadPart) / (double)freq.QuadPart);
		listPrint(sr_list, n);
		printf("\n%d\n", checkListSorted(sr_list, n));
		free(sr_list);
	}
	
}



int main() {
	LARGE_INTEGER freq;
	float list[5000];
	int n = 10;
	//printf("%d\n", RAND_MAX);
	//��� �������:
	QueryPerformanceFrequency(&freq);
	//��� �����:
	setlocale(LC_ALL, "Russian");
	//������ + ��������� ����:
	srand(time(NULL));
	fillRandList(list, n);

	while (state != 255) {
		if (state > 3) {
			state = 0;
		}
		switch (state) {
		case(0): showBaseScreen(list, n); break;
		case(1): manualFillScreen(list, n); break;
		case(2): listSizeChangeScreen(list, &n); break;
		case(3): sortScreen(list, n, freq); break;
		}
	}
}