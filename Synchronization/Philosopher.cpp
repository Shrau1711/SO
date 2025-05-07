#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

pthread_mutex_t forks[5]; // 5 forks (mutexes)

void* philosopher(void* num) {
    int i = ((intptr_t)num);
    while (true) {
        cout << "Philosopher " << i << " is thinking.\n";
        sleep(1);

        // Pick up left fork
        pthread_mutex_lock(&forks[i]);

        // Pick up right fork
        pthread_mutex_lock(&forks[(i+1)%5]);

        cout << "Philosopher " << i << " is eating.\n";
        sleep(1);

        // Put down left fork
        pthread_mutex_unlock(&forks[i]);

        // Put down right fork
        pthread_mutex_unlock(&forks[(i+1)%5]);
    }
}

int main() {
    pthread_t ph[5];
    for (int i = 0; i < 5; i++)
        pthread_mutex_init(&forks[i], NULL);

    for (int i = 0; i < 5; i++)
        pthread_create(&ph[i], NULL, philosopher, (void*)(intptr_t)i);

    for (int i = 0; i < 5; i++)
        pthread_join(ph[i], NULL);

    for (int i = 0; i < 5; i++)
        pthread_mutex_destroy(&forks[i]);

    return 0;
}
