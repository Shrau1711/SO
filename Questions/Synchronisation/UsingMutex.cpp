//producer-consumer
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

std::vector<int> buffer;
const int BUFFER_SIZE = 5;
std::mutex mtx; // Mutex to protect buffer

void producer(int id) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Simulate production time
        
        int item = rand() % 100; // Generate an item
        
        mtx.lock(); // Acquire the mutex to access the buffer
        if (buffer.size() < BUFFER_SIZE) {
            buffer.push_back(item); // Add item to buffer
            std::cout << "Producer " << id << " produced: " << item << std::endl;
        }
        mtx.unlock(); // Release the mutex
        
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // To slow down production
    }
}

void consumer(int id) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Simulate consumption time
        
        mtx.lock(); // Acquire the mutex to access the buffer
        if (!buffer.empty()) {
            int item = buffer.back();
            buffer.pop_back(); // Remove item from buffer
            std::cout << "Consumer " << id << " consumed: " << item << std::endl;
        }
        mtx.unlock(); // Release the mutex
        
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // To slow down consumption
    }
}

int main() {
    std::thread prod1(producer, 1);
    std::thread prod2(producer, 2);
    std::thread cons1(consumer, 1);
    std::thread cons2(consumer, 2);

    prod1.join();
    prod2.join();
    cons1.join();
    cons2.join();

    return 0;
}


//reader-writer
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex mtx; // Mutex for resource
std::mutex readCountMutex; // Mutex to protect readCount variable
int readCount = 0; // Number of active readers

void reader(int id) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Simulate reading time

        readCountMutex.lock();
        readCount++;
        if (readCount == 1) {
            mtx.lock(); // First reader locks the resource
        }
        readCountMutex.unlock();

        std::cout << "Reader " << id << " is reading." << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Simulate reading time

        readCountMutex.lock();
        readCount--;
        if (readCount == 0) {
            mtx.unlock(); // Last reader releases the resource
        }
        readCountMutex.unlock();
    }
}

void writer(int id) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Simulate writing time

        mtx.lock(); // Writer locks the resource

        std::cout << "Writer " << id << " is writing." << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Simulate writing time

        mtx.unlock(); // Writer releases the resource
    }
}

int main() {
    std::thread reader1(reader, 1);
    std::thread reader2(reader, 2);
    std::thread writer1(writer, 1);
    std::thread writer2(writer, 2);

    reader1.join();
    reader2.join();
    writer1.join();
    writer2.join();

    return 0;
}


//dining-philosopher
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

const int NUM_PHILOSOPHERS = 5;

std::mutex forks[NUM_PHILOSOPHERS]; // Mutex for each fork

void philosopher(int id) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Think
        
        std::cout << "Philosopher " << id << " is thinking." << std::endl;

        // Pick up forks (lock both forks)
        std::lock(forks[id], forks[(id + 1) % NUM_PHILOSOPHERS]); // Lock both forks
        std::lock_guard<std::mutex> leftFork(forks[id], std::adopt_lock);
        std::lock_guard<std::mutex> rightFork(forks[(id + 1) % NUM_PHILOSOPHERS], std::adopt_lock);
        
        std::cout << "Philosopher " << id << " is eating." << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Eat

        // No need to explicitly unlock, as lock_guard will do it automatically
    }
}

int main() {
    std::vector<std::thread> philosophersThreads;

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosophersThreads.push_back(std::thread(philosopher, i));
    }

    // Join all philosopher threads
    for (auto& t : philosophersThreads) {
        t.join();
    }

    return 0;
}
