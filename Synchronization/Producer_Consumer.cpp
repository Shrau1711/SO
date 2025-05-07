#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

sem_t empty, full; // Semaphores for buffer state
pthread_mutex_t mutex;
int buffer; // One-slot buffer

void* producer(void* arg) {
    int i = 1;
    while (true) {
        sem_wait(&empty); // Wait if buffer is full

        pthread_mutex_lock(&mutex);
        buffer = i; // Produce item
        cout << "Produced: " << buffer << endl;
        i++;
        pthread_mutex_unlock(&mutex);

        sem_post(&full); // Signal buffer is full now
        sleep(1);
    }
}

void* consumer(void* arg) {
    while (true) {
        sem_wait(&full); // Wait if buffer is empty

        pthread_mutex_lock(&mutex);
        cout << "Consumed: " << buffer << endl;
        pthread_mutex_unlock(&mutex);

        sem_post(&empty); // Signal buffer is empty now
        sleep(1);
    }
}

int main() {
    pthread_t p, c;
    sem_init(&empty, 0, 1); // Buffer starts empty
    sem_init(&full, 0, 0);  // Not full initially
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
