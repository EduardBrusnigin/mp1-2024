#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int state = 0;


typedef double (*Funk)(double x, int n);




// ������� n - ���
double TeylorNum(int n, Funk next, double x) {

}


// ������� �� �������� accur (��� �� n-���)
double TeylorAccuracy(int n, double accur, Funk next, double x) {

}


// state = 0
void Interface() {
	int ans = 0;
	printf("�������� �����:\n");
	printf("1) ��������� �����.\n");
	printf("2) �������� ����� �����.\n\n");
	printf("3) �����.");

	scanf_s("%d", ans);

	switch (ans) {
	case(1): state = 1; break;
	case(2): state = 2; break;
	case(3): state = 255; break;
	}
}


// ��������� n 
int AskNum(char* string) {
	printf(string);
	return 1;
}


// state = 1
void NormalMode() {
	AskNum("������� ����� ����������?");
}


// state = 2
void SerialMode() {
	AskNum("�������� �����.");
}


int main() {
	setlocale(LC_ALL, "Russian");
	AskNum("FFF");
	while (state != 255) {
		printf("\n=================================\n");
		if (state > 2) {
			state = 0;
		}
		switch (state) {
		case(0): Interface(); break;
		case(1): NormalMode(); break;
		case(2): SerialMode(); break;
		}
	}
	printf("����");
	return 1;
}