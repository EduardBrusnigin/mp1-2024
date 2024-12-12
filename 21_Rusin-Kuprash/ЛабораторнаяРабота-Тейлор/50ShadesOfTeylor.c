#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int state = 0;


typedef double (*Start)(double x);
typedef double (*Step)(double x, int n);


double cosStart(double x) {
	return 1;
}


double cosStep(double x, int n) {
	return -x * x / (2 * (double)n * (2 * (double)n - 1));
}


// ������� �� �������� accur (��� �� n-���)
double TeylorAccuracy(int n, double accur, Start first, Step next, double x) {
	int i = 1;
	double res = first(x);
	double step = res * next(x, i);
	res += step;
	while ((i++ < n) && (accur < fabs(step))) {
		step = step * next(x, i);
		res += step;
	}
	return res;
}


// state = 0
void Interface() {
	int ans = 0;
	printf("�������� �����:\n");
	printf("1) ��������� �����.\n");
	printf("2) �������� ����� �����.\n\n");
	printf("3) �����.");

	scanf_s("%d", &ans);

	switch (ans) {
	case(1): state = 1; break;
	case(2): state = 1; break;
	case(3): state = 255; break;
	}
}


// ��������� n 
int AskNum(char* string) {
	int ans;
	printf(string);
	scanf_s("%d", &ans);
	return ans;
}


double AskDouble(char* string) {
	double ans;
	printf(string);
	scanf_s("%lf", &ans);
	return ans;
}


// state = 1
void NormalMode() {
	double found;
	double find;
	int ans = -1;
	double accurf;

	int n = AskNum("������� ����� ����������? (0 < n < 61)");
	if (n < 1) {
		n = 0;
	}
	else if (n > 60) {
		n = 60;
	}
	accurf = 1 / pow(10, (double)AskNum("������� �������� ( 10 ^ (-n) )"));
	printf("%lf\n", accurf);
	printf("�������� �������:\n");
	printf("1) �������\n");
	//printf("2) �������� ����� �����.\n\n");
	//printf("3) �����.");
	while ((ans < 1) || (ans > 2)) {
		scanf_s("%d", &ans);
	}
	
	find = AskDouble("����� �������� ������ �����?\n");

	switch (ans) {
	case(1): found = TeylorAccuracy(n, accurf, cosStart, cosStep, find);
		printf("���������� ���� - %lf\n�� ������� - %lf\n������� (����������) - %e", cos(find), found, fabs(cos(find) - found));
		break;
		//case(2): state = 1; break;
		//case(3): state = 255; break;
	}
	state = 0;
}


// state = 2
void SerialMode() {
	AskNum("�������� �����.");
}


int main() {
	setlocale(LC_ALL, "Russian");
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