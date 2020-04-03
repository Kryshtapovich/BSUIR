#include <iostream>
#include <queue>
#include <mutex>
using namespace std;
using namespace chrono;

typedef unsigned char byte;

class Queue {
protected:
	mutex mutex;
public:
	virtual void push(byte item) = 0;
	virtual bool pop(byte& item) = 0;
};

class DynamicQueue : public Queue {
private:
	queue<byte> queue;
public:
	void push(byte item) override {
		mutex.lock();
		queue.push(item);
		mutex.unlock();
	}

	bool pop(byte& item) override {
		mutex.lock();
		if (queue.empty()) {
			mutex.unlock();
			this_thread::sleep_for(milliseconds(1));
			mutex.lock();
			if (queue.empty()) {
				mutex.unlock();
				return false;
			}
			else {
				item = queue.front();
				queue.pop();
				mutex.unlock();
				return true;
			}
		}
		else {
			item = queue.front();
			queue.pop();
			mutex.unlock();
			return true;
		}
	}
};

class StaticQueue : public Queue {
private:
	int size;
	byte* queue;
	atomic<int> tail, amount;
	condition_variable condition;
public:
	StaticQueue(int size) {
		this->size = size;
		queue = new byte[size];
		for (int i = 0; i < size; i++) queue[i] = 0;
		tail = 0;
		amount = 0;
	}

	~StaticQueue() {
		delete queue;
	}

	void push(byte item) override {
		unique_lock<std::mutex> lock(mutex);
		condition.wait(lock, [&] { return amount < size; });
		queue[tail % size] = item;
		tail++;
		amount++;
		condition.notify_all();
	}

	bool pop(byte& item) override {
		unique_lock<std::mutex> lock(mutex);
		if (amount == 0) {
			condition.wait_for(lock, milliseconds(1), [&] {return amount > 0; });
			if (amount == 0) {
				return false;
			}
			else {
				item = queue[0];
				for (int i = 0; i < tail % size; i++) queue[i] = queue[i + 1];
				tail--;
				queue[tail % size] = 0;
				amount--;
				condition.notify_all();
				return true;
			}
		}
		else {
			item = queue[0];
			for (int i = 0; i < tail % size; i++) queue[i] = queue[i + 1];
			tail--;
			queue[tail % size] = 0;
			amount--;
			condition.notify_all();
			return true;
		}
	}
};

void testQueue(Queue& queue, int producerNum, int consumerNum) {
	const int taskNum = 4 * 1024 * 1024;
	atomic<int> sum = 0;
	thread* producerThreads = new thread[producerNum];
	thread* consumerThreads = new thread[consumerNum];

	auto start = high_resolution_clock::now();

	for (int i = 0; i < producerNum; i++) {
		producerThreads[i] = thread([&queue, taskNum] {
			for (int j = 0; j < taskNum; j++) queue.push(1);
		});
	}

	for (int i = 0; i < consumerNum; i++) {
		consumerThreads[i] = thread([&queue, &sum, taskNum, producerNum] {
			byte item = 0;
			while (sum < taskNum * producerNum) {
				if (queue.pop(item)) sum += item;
			}
		});
	}

	for (int i = 0; i < producerNum; i++) producerThreads[i].join();
	for (int i = 0; i < consumerNum; i++) consumerThreads[i].join();

	auto finish = high_resolution_clock::now();
	auto duration = chrono::duration<float>(finish - start).count();

	cout << "ProducerNum: " << producerNum << " ConsumerNum: " << consumerNum << endl;
	cout << "Sum: " << sum << " Expected sum: " << taskNum * producerNum << endl;
	cout << "Duration: " << duration << "s" << endl << endl;
}
