#include <iostream>
#include <omp.h>

using namespace std;

template <typename T>
void generate_array(T* arr, int len) {
	for (int i = 0; i < len; i++) {
		arr[i] = rand() % 1000 + 1;
	}
}

void sum_square_with_no_mp(int* arr, int len, long long* result) {
	for (int i = 0; i < len; i++) {
		int sum = 0;
		for (int j = 0; j < arr[i]; j++) {
			sum += j * j;
		}
		result[i] = sum;
	}
}

void sum_square_with_mp(int* arr, int len, long long* result) {
	for (int i = 0; i < len; i++) {
		int sum = 0;
#pragma omp parallel for reduction(+:sum)
		for (int j = 0; j < arr[i]; j++) {
			sum += j * j;
		}
		result[i] = sum;
	}
}

template <typename T>
void print_execution_time(const T& func, int tests) {
	double min_diff = 99999999;
	double sum = 0;
	for (int i = 0; i < tests; i++) {
		double start, finish;
		start = omp_get_wtime();
		func();
		finish = omp_get_wtime();
		double diff = finish - start;
	
		sum += diff;
		if (min_diff > diff) {
			min_diff = diff;
		}
	}
	
	printf("Minimal time: %fs\n", min_diff);
	printf("Average time: %fs\n", sum / tests);
}


int main() {
	srand(time(0));

	const int size = 10000000;
	int* arr = new int[size];
	generate_array(arr, size);

	long long* result = new long long[size];

	int tests = 5;
	
	cout << "Parallel" << endl;
	print_execution_time([arr, size, result]() {
		sum_square_with_mp(arr, size, result);
	}, tests);
	
	cout << "\nSerial:" << endl;
	print_execution_time([arr, size, result]() {
		sum_square_with_no_mp(arr, size, result);
	}, tests);
}
