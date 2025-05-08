//Implement the solutions for following synchronization problems using semaphore:
//i. Producer Consumer
//ii. Reader Writer 
//iii. Dining Philosopher

#include <iostream>
#include <thread>
#include <semaphore.h>
#include <vector>
#include <chrono>
#include <mutex>

std::vector<int> buffer; // Shared buffer
const int BUFFER_SIZE = 5; // Size of the buffer

// Semaphores to track available space and items
std::sem_t emptySlots; // Count of empty slots in the buffer
std::sem_t filledSlots; // Count of filled slots in the buffer
std::mutex mtx; // Mutex to protect access to shared buffer

void producer(int id) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Simulate production time
        
        int item = rand() % 100; // Generate an item
        std::sem_wait(&emptySlots); // Wait for an empty slot
        mtx.lock();
        if (buffer.size() < BUFFER_SIZE) {
            buffer.push_back(item); // Add item to buffer
            std::cout << "Producer " << id << " produced: " << item << std::endl;
        }
        mtx.unlock();
        std::sem_post(&filledSlots); // Signal that there's a new item
    }
}

void consumer(int id) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Simulate consumption time
        
        std::sem_wait(&filledSlots); // Wait for an item to consume
        mtx.lock();
        if (!buffer.empty()) {
            int item = buffer.back();
            buffer.pop_back(); // Remove item from buffer
            std::cout << "Consumer " << id << " consumed: " << item << std::endl;
        }
        mtx.unlock();
        std::sem_post(&emptySlots); // Signal that there's an empty slot
    }
}

int main() {
    std::sem_init(&emptySlots, 0, BUFFER_SIZE); // Initially all slots are empty
    std::sem_init(&filledSlots, 0, 0); // Initially no items are in the buffer

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


#include <iostream>
#include <thread>
#include <semaphore.h>
#include <chrono>
#include <mutex>

std::mutex mtx; // Mutex to protect access to shared data
std::sem_t rwMutex; // Semaphore for writer's exclusive access
std::sem_t mutex; // Semaphore for reader's mutual exclusion
int readCount = 0; // Number of readers currently reading

void reader(int id) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Simulate reading time
        
        std::sem_wait(&mutex); // Enter critical section for reader count
        readCount++;
        if (readCount == 1) {
            std::sem_wait(&rwMutex); // First reader locks the writer
        }
        std::sem_post(&mutex); // Exit critical section for reader count

        std::cout << "Reader " << id << " is reading." << std::endl;
        
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Simulate reading time
        
        std::sem_wait(&mutex); // Enter critical section for reader count
        readCount--;
        if (readCount == 0) {
            std::sem_post(&rwMutex); // Last reader releases the writer lock
        }
        std::sem_post(&mutex); // Exit critical section for reader count
    }
}

void writer(int id) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Simulate writing time
        
        std::sem_wait(&rwMutex); // Writer gets exclusive access

        std::cout << "Writer " << id << " is writing." << std::endl;
        
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Simulate writing time
        
        std::sem_post(&rwMutex); // Release the writer's exclusive access
    }
}

int main() {
    std::sem_init(&rwMutex, 0, 1); // Initially one writer is allowed
    std::sem_init(&mutex, 0, 1); // Initially reader count is protected

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


#include <iostream>
#include <thread>
#include <semaphore.h>
#include <chrono>
#include <vector>

const int NUM_PHILOSOPHERS = 5;

std::sem_t forks[NUM_PHILOSOPHERS]; // Semaphore for each fork
std::sem_t mutex; // Mutex to control access to philosophers

void philosopher(int id) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Think

        std::cout << "Philosopher " << id << " is thinking." << std::endl;
        
        // Pick up the forks (lock both forks, one by one)
        std::sem_wait(&forks[id]); // Pick up left fork
        std::sem_wait(&forks[(id + 1) % NUM_PHILOSOPHERS]); // Pick up right fork
        
        std::cout << "Philosopher " << id << " is eating." << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Eat

        // Put down the forks
        std::sem_post(&forks[id]); // Put down left fork
        std::sem_post(&forks[(id + 1) % NUM_PHILOSOPHERS]); // Put down right fork
    }
}

int main() {
    // Initialize semaphores for each fork to 1 (each fork is available)
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        std::sem_init(&forks[i], 0, 1);
    }

    std::vector<std::thread> philosophersThreads;

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosophersThreads.push_back(std::thread(philosopher, i));
    }

    // Join all philosopher threads
    for (auto& t : philosophersThreads) {
        t.join();
    }

    // Cleanup semaphores
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        std::sem_destroy(&forks[i]);
    }

    return 0;
}
