#include "stdio.h"
#include "stdlib.h"
#include "time.h"


int is_sorted(int Sorted[], int len){  // проверка на отсортированность
	int result = 1;
	
	int i;

	for (i = 0; i < len-1; i++)
		if (Sorted[i] > Sorted[i+1]){
			result = 0;
			break;
		}
	
	return result;
}


int is_empty(int Array[]){  // проверка: пуст ли массив
	int i;
	char flag = 0;

	for (i=0; i < 10000; i++)
		if (Array[i] != 0){
			flag = 1;
			break;
		}
	
	if (flag == 1)
		return 0;

	else
		return 1;
			
}


char get_status(int Sorted[], int len) {  // 0 - массив пуст, 1 - неотсортирован, 2 - отсортирован
	if (len == 0)
		return 0;

	else{
		if ((is_empty(Sorted) == 1) || ((is_empty(Sorted) == 0) && (is_sorted(Sorted, len) == 0)))
			return 1;

		else
			return 2;
	}
}


void array_elem_swap(int Array[], int i, int j) {  // замена элементов в массиве
	int tmp;

	tmp = Array[i];

	Array[i] = Array[j];
	Array[j] = tmp;
}


void copy_array(int Array[], int Copied[], int len) {  // скопировать массив
	int i;

	for (i = 0; i < len; i++) {
		Copied[i] = Array[i];
	}
}


void bubble_sort(int Array[], int Sorted[], int len, int swaps[]){  // сортировка пузырьком
	copy_array(Array, Sorted, len);

	int swaps_counter = 0;

	int f;
	
	int i, j;
	
	for (i=0; i<len; i++)
		for (j=0; j < len-i-1; j++)
			if (Sorted[j] > Sorted[j+1]) {
				f = Sorted[j];
				Sorted[j] = Sorted[j+1];
				Sorted[j+1] = f;

				swaps_counter++;
			}
	
	swaps[0] = swaps_counter;
}


void modified_bubble_sort(int Array[], int Sorted[], int len, int swaps[]){  // модифицированная сортировка пузырьком
	copy_array(Array, Sorted, len);

	int swaps_counter = 0;

	int left = 0;
	int right = len - 1;

	while (left <= right) {
		for (int i = right; i > left; --i) 
			if (Sorted[i-1] > Sorted[i])
				array_elem_swap(Sorted, i-1, i);
				swaps_counter++;
		++left;
		for (int i = left; i < right; ++i)
			if (Sorted[i] > Sorted[i+1])
				array_elem_swap(Sorted, i, i+1);
				swaps_counter++;
		--right;
	}
	swaps[1] = swaps_counter;
}


void insertion_sort(int Array[], int Sorted[], int len, int swaps[]){  // сортировка вставками
	copy_array(Array, Sorted, len);

	int swaps_counter = 0;

	for (int i = 1; i < len; ++i){
		int x = Sorted[i];
		int j = i;

		while ((j > 0) && (Sorted[j - 1] > x)){
			Sorted[j] = Sorted[j-1];
			--j;
			swaps_counter++;
		}
		Sorted[j] = x;
	}

	swaps[2] = swaps_counter;
}


void selection_sort(int Array[], int Sorted[], int len, int swaps[]){  // сортировка выбором
	copy_array(Array, Sorted, len);

	int swaps_counter = 0;

	for (int i = 0; i < len - 1; i++) {
		int min_id = i;
		for (int j = i + 1; j < len; j++)
			if (Sorted[j] < Sorted[min_id])
				min_id = j;
				swaps_counter++;

		array_elem_swap(Sorted, min_id, i);
	}

	swaps[3] = swaps_counter;
}


void linear_search(int Array[], int len){
	int el;

	printf("Enter element: ");
	scanf("%d", &el);

	int flag = 0;

	for (int i = 0; i < len; i++)
		if (Array[i] == el){
			flag = 1;
			printf("Index: %d\n\n", i);
			break;
		}

	if (flag == 0)
		printf("Element is not found\n\n");
}


void binary_search(int Sorted[], int len){
	int el;

	printf("Enter element: ");
	scanf("%d", &el);

	int low, high, middle;

	low = 0;
	high = len - 1;

	int flag = 0;

	while (low <= high) {
		middle = (low + high) / 2;

		if (el < Sorted[middle])
			high = middle - 1;

		else if (el > Sorted[middle])
			low = middle + 1;

		else{
			flag = 1;
			printf("Index: %d\n\n", middle);
			break;
		}
	}

	
	if (flag == 0)
		printf("Element is not found\n\n");
}


void generate_array(int Array[], int Sorted[], int* len, int swaps[]){  // сгенерировать массив
	for (int i = 0; i < 4; i++)
		swaps[i] = 0;

	int k;
	for (k=0; k<*len; k++)
		Sorted[k] = 0;


	int min, max;

	do {
		printf("Enter the number of array elements (> 1): ");
		scanf("%d", &(*len));
	}
	while (*len <= 1);

	printf("Enter lower border: ");
	scanf("%d", &min);

	do {
		printf("Enter upper border: ");
		scanf("%d", &max);
	}
	while (max <= min);

	printf("\n");

	int i;

	for (i = 0; i < *len; i++){
		Array[i] = min + rand()%(max - min);
	}

	printf("Done!\n\n");
}


void input_array(int Array[], int Sorted[], int* len, int swaps[]){  // ввод массива
	for (int i = 0; i < 4; i++)
		swaps[i] = 0;

	int k;
	for (k=0; k<*len; k++)
		Sorted[k] = 0;

	do {
		printf("Enter the number of array elements (> 1): ");
		scanf("%d", &(*len));
	}
	while (*len <= 1);
	
	printf("\n");

	int i;

	for (i = 0; i < *len; i++) {
		printf("Element (%d/%d): ", i+1, *len);
		scanf("%d", &Array[i]);
	}
	printf("Done!\n\n");
}


void print_array(int Array[], int len) {  // вывод массива
	printf("{");
	
	int i;

	for (i=0; i < len; i++){
		printf("%d", Array[i]);
		if (i < len - 1)
			printf(", ");
	}

	printf("}");
}


void print_menu(int Array[], int Sorted[], int len, int swaps[]){  // напечатать меню
	printf("====================\n");

	char status = get_status(Sorted, len);

	switch (status) {
		case 1:
			printf("Array: ");
			print_array(Array, len);
			printf("\n\n");
			printf("----------\nStats:\n\n");

			if (swaps[0] != 0)
				printf("Bubble sort: %d iter.\n", swaps[0]);
			else
				printf("Bubble sort: --\n");

			if (swaps[1] != 0)
				printf("Bubble sort (mod.): %d iter.\n", swaps[1]);
			else
				printf("Bubble sort (mod.): --\n");

			if (swaps[2] != 0)
				printf("Insertion sort: %d iter.\n", swaps[2]);
			else
				printf("Insertion sort: --\n");
			
			if (swaps[3] != 0)
				printf("Selection sort: %d iter.", swaps[3]);
			else
				printf("Selection sort: --");

			printf("\n----------\n\n");
			break;

		case 2:
			printf("Array: ");
			print_array(Array, len);
			printf("\nSorted array: ");
			print_array(Sorted, len);
			printf("\n\n");
			printf("----------\nStats:\n\n");

			if (swaps[0] != 0)
				printf("Bubble sort: %d iter.\n", swaps[0]);
			else
				printf("Bubble sort: --\n");

			if (swaps[1] != 0)
				printf("Bubble sort (mod.): %d iter.\n", swaps[1]);
			else
				printf("Bubble sort (mod.): --\n");

			if (swaps[2] != 0)
				printf("Insertion sort: %d iter.\n", swaps[2]);
			else
				printf("Insertion sort: --\n");
			
			if (swaps[3] != 0)
				printf("Selection sort: %d iter.", swaps[3]);
			else
				printf("Selection sort: --");

			printf("\n----------\n\n");
			break;
	}

	printf("Actions: \n");
	
	printf("1. Enter array\n");
	printf("2. Generate array\n");

	switch (status) {
		case 1:
			printf("3. Bubble sort\n");
			printf("4. Modified bubble sort\n");
			printf("5. Insertion sort\n");
			printf("6. Selection sort\n");
			printf("7. Linear search\n");
			break;

		case 2:
			printf("3. Bubble sort\n");
			printf("4. Modified bubble sort\n");
			printf("5. Insertion sort\n");
			printf("6. Selection sort\n");
			printf("7. Linear search\n");
			printf("8. Binary search\n");
			break;

	}

	printf("0. Exit\n");

	printf("====================\n");
}


void do_action(int Array[], int Sorted[], int* len, char* exit_checker, int swaps[]) {  // выполнение действия
	int action;
	
	printf("\nYour action: ");
	
	while (scanf("%d", &action) != 1) {
		scanf("%*[^\r^\n]");
		fflush(stdout);
	} /* Цикл для очистки буфера на линукс */

	printf("\n");

	char status = get_status(Sorted, *len);

	switch (status) {
		case 0:
			switch (action) {
				case 1:
					input_array(Array, Sorted, len, swaps);
					break;

				case 2:
					generate_array(Array, Sorted, len, swaps);
					break;

				case 0:
					*exit_checker = 1;
					break;

				default:
					printf("Undefined action!\n\n");
			}
			break;

		case 1:
			switch (action) {
				case 1:
					input_array(Array, Sorted, len, swaps);
					break;

				case 2:
					generate_array(Array, Sorted, len, swaps);
					break;

				case 3:
					bubble_sort(Array, Sorted, *len, swaps);
					break;

				case 4:
					modified_bubble_sort(Array, Sorted, *len, swaps);
					break;

				case 5:
					insertion_sort(Array, Sorted, *len, swaps);
					break;

				case 6:
					selection_sort(Array, Sorted, *len, swaps);
					break;

				case 7:
					linear_search(Array, *len);
					break;

				case 0:
					*exit_checker = 1;
					break;

				default:
					printf("Undefined action!\n\n");
			}
			break;

		case 2:
			switch (action) {
				case 1:
					input_array(Array, Sorted, len, swaps);
					break;

				case 2:
					generate_array(Array, Sorted, len, swaps);
					break;

				case 3:
					bubble_sort(Array, Sorted, *len, swaps);
					break;

				case 4:
					modified_bubble_sort(Array, Sorted, *len, swaps);
					break;

				case 5:
					insertion_sort(Array, Sorted, *len, swaps);
					break;

				case 6:
					selection_sort(Array, Sorted, *len, swaps);
					break;

				case 7:
					linear_search(Array, *len);
					break;

				case 8:
					binary_search(Sorted, *len);
					break;

				case 0:
					*exit_checker = 1;
					break;

				default:
					printf("Undefined action!\n\n");
			}
			break;

	}
}


int main() {
	int A[10000] = {0};  // массив
	int B[10000] = {0};  // отсортированный массив
	int n = 0;  // кол-во элементов
	
	char is_exit = 0;

	int swaps[4] = {0};  // количество обменов в сортировках


	srand(time(NULL));

	while (is_exit != 1) {
		print_menu(A, B, n, swaps);
		do_action(A, B, &n, &is_exit, swaps);
	}

	printf("Bye!\n");

	return 0;
}
