#include <iostream>
#include <omp.h>
#include <string>
using namespace std;

void fillVectors(int* a, int* b, int length);

int linearScalarProduct(int* a, int* b, int length);

int parallelScalarProduct(int* a, int* b, int length);

int parallelWithReduction(int* a, int* b, int length);

int main() {
	const int length = 10e7;
	int* a = new int[length];
	int* b = new int[length];

	fillVectors(a, b, length);

	auto t1 = omp_get_wtime();
	auto linearProduct = linearScalarProduct(a, b, length);
	auto t2 = omp_get_wtime();

	cout << "linear product: " << linearProduct << "\t" << "duration: " << t2 - t1 << endl;

	t1 = omp_get_wtime();
	auto parallelProduct = parallelScalarProduct(a, b, length);
	t2 = omp_get_wtime();

	cout << "parallel product: " << parallelProduct << "\t" << "duration: " << t2 - t1 << endl;

	t1 = omp_get_wtime();
	auto parallelWithReductionProduct = parallelWithReduction(a, b, length);
	t2 = omp_get_wtime();

	cout << "parallel with reduction: " << parallelWithReductionProduct << "\t" << "duration: " << t2 - t1 << endl;

	delete a, b;
	return 0;
}

void fillVectors(int* a, int* b, int length) {
	srand(time(0));

	for (int i = 0; i < length; i++)
	{
		a[i] = rand() % 21 - 10;
		b[i] = rand() % 21 - 10;
	}
}

int linearScalarProduct(int* a, int* b, int length) {
	int sum = 0;

	for (int i = 0; i < length; i++) {
		sum += a[i] * b[i];
	}

	return sum;
}

int parallelScalarProduct(int* a, int* b, int length) {
	int sum = 0;

	#pragma omp parallel 
	{
		int tmp = 0;

		#pragma omp for 
		for (int i = 0; i < length; i++) {
			tmp += a[i] * b[i];
		}

		#pragma omp critical
		sum += tmp;
	}

	return sum;
}

int parallelWithReduction(int* a, int* b, int length) {
	int sum = 0;

	#pragma omp parallel reduction(+: sum)
	{
		#pragma omp for
		for (int i = 0; i < length; i++) {
			sum += a[i] * b[i];
		}
	}

	return sum;
}