#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

// This mutex is for protecting readCount variable
pthread_mutex_t mutex;

// This semaphore controls writer access and blocks readers if a writer is writing
sem_t wrt;

int readCount = 0; // number of readers currently reading

void* reader(void* arg) {
    int f = ((intptr_t)arg); // thread number
    while (true) {
        // Lock mutex before changing readCount
        pthread_mutex_lock(&mutex);
        readCount++;

        // If first reader, lock writer (block writers)
        if (readCount == 1)
            sem_wait(&wrt);

        pthread_mutex_unlock(&mutex);

        // --- Critical Section: Reading ---
        cout << "Reader " << f << " is reading.\n";
        sleep(1);

        // Lock mutex before updating readCount again
        pthread_mutex_lock(&mutex);
        readCount--;

        // If last reader, unlock writer
        if (readCount == 0)
            sem_post(&wrt);

        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}

void* writer(void* arg) {
    int f = ((intptr_t)arg); // thread number
    while (true) {
        // Writer requests access
        sem_wait(&wrt);

        // --- Critical Section: Writing ---
        cout << "Writer " << f << " is writing.\n";
        sleep(1);

        // Release writer lock so readers/writers can proceed
        sem_post(&wrt);
        sleep(1);
    }
}

int main() {
    pthread_t r[5], w[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt, 0, 1); // Initialize wrt to 1

    // Create 3 reader threads
    for (int i = 0; i < 3; i++)
        pthread_create(&r[i], NULL, reader, (void*)(intptr_t)(i+1));

    // Create 2 writer threads
    for (int i = 0; i < 2; i++)
        pthread_create(&w[i], NULL, writer, (void*)(intptr_t)(i+1));

    // Join threads
    for (int i = 0; i < 3; i++)
        pthread_join(r[i], NULL);

    for (int i = 0; i < 2; i++)
        pthread_join(w[i], NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
