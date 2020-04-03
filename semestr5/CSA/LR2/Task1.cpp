#include <iostream>
#include <mutex>
using namespace std;
using namespace chrono;

typedef unsigned char byte;

bool isSuccess(byte* bytes, int length) {
	for (int i = 0; i < length; i++) {
		if (bytes[i] != 1) return false;
	}

	return true;
}

void mutexCounter(int numTasks, int numThreads, bool canSleep) {
	byte* bytes = new byte[numTasks]{ 0 };
	for (int i = 0; i < numTasks; i++) bytes[i] = 0;

	thread* threads = new thread[numThreads];

	mutex mutex;
	int taskIndex = 0;
	auto start = high_resolution_clock::now();

	for (int i = 0; i < numThreads; i++) {
		threads[i] = thread([&] {
			while (true) {
				mutex.lock();
				if (taskIndex == numTasks) {
					mutex.unlock();
					return;
				}
				int tmp = taskIndex;
				taskIndex++;
				mutex.unlock();
				bytes[tmp]++;
				if (canSleep) this_thread::sleep_for(nanoseconds(10));
			}
		});
	}

	for (int i = 0; i < numThreads; i++) threads[i].join();

	auto finish = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(finish - start);
	auto withSleep = canSleep ? " with sleep" : "";
	auto result = isSuccess(bytes, numTasks) ? " success" : " failed";

	cout << "Mutex counter" << withSleep << " threads: " << numThreads << " duration: "
		<< duration.count() << "ms " << result << endl;
}

void atomicCounter(int numTasks, int numThreads, bool canSleep) {
	byte* bytes = new byte[numTasks]{ 0 };
	for (int i = 0; i < numTasks; i++) bytes[i] = 0;

	thread* threads = new thread[numThreads];

	atomic<int> taskIndex = 0;
	auto start = high_resolution_clock::now();

	for (int i = 0; i < numThreads; i++) {
		threads[i] = thread([&] {
			while (taskIndex < numTasks) {
				bytes[taskIndex++]++;
				if (canSleep) this_thread::sleep_for(nanoseconds(10));
			}
		});
	}

	for (int i = 0; i < numThreads; i++) threads[i].join();

	auto finish = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(finish - start);
	auto withSleep = canSleep ? " with sleep" : "";
	auto result = isSuccess(bytes, numTasks) ? " success" : " failed";

	cout << "Atomic counter" << withSleep << " threads: " << numThreads << " duration: "
		<< duration.count() << "ms " << result << endl;
}
