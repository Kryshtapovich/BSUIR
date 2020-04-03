#include <iostream>
#include "Task1.cpp"
#include "Task2.cpp"
using namespace std;

void task1();

void task2();

int main() {
	task1();
	task2();
}

void task1() {
	const int length = 1024 * 1024;

	for (int i = 4; i <= 32; i *= 2) mutexCounter(length, i, false);
	cout << endl;

	for (int i = 4; i <= 32; i *= 2) mutexCounter(length, i, true);
	cout << endl;

	for (int i = 4; i <= 32; i *= 2) atomicCounter(length, i, false);
	cout << endl;

	for (int i = 4; i <= 32; i *= 2) atomicCounter(length, i, true);
	cout << endl;
}

void task2() {
	cout << "Dynamic queue" << endl;
	DynamicQueue dynamicQueue;
	for (int i = 1; i <= 4; i *= 2)
		for (int j = 1; j <= 4; j *= 2)
			testQueue(dynamicQueue, i, j);


	const int queueSizes[] = { 1, 4, 16 };

	cout << endl << "Static queue" << endl;
	for (auto queueSize : queueSizes) {
		cout << "Size: " << queueSize << endl;
		StaticQueue staticQueue(queueSize);
		for (int i = 1; i <= 4; i *= 2)
			for (int j = 1; j <= 4; j *= 2)
				testQueue(staticQueue, i, j);
	}
}
