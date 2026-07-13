#include <stdio.h> 
#include <pthread.h> 
#include <unistd.h>
#include <semaphore.h>

// Shared stock balance (critical shared resource)
int balance = 2;

// Binary semaphore to protect access to balance
sem_t stock_sem;

// Thread function for customer_0
void* customer_0(void* arg) {
    // Enter critical section (acquire semaphore)
    sem_wait(&stock_sem);

    // Read the current stock value
    int t = balance;

    // Simulate delay to mimic real-world I/O processing
    sleep(0.1);

    // Deduct stock only if available
    if (balance > 0)
        balance = t - 1;

    // Exit critical section (release semaphore)
    sem_post(&stock_sem);

    return NULL;
}

// Thread function for customer_1 (same logic as customer_0)
void* customer_1(void* arg) {
    // Enter critical section (acquire semaphore)
    sem_wait(&stock_sem); // Lock

    // Read the current stock value
    int t = balance;

    // Simulate processing delay
    sleep(0.1);

    // Deduct stock if available
    if (balance > 0)
        balance = t - 1;

    // Exit critical section (release semaphore)
    sem_post(&stock_sem); // Unlock

    return NULL;
}

int main()
{
    int thread0_id = 0, thread1_id = 1;

    // Initialize binary semaphore (1 = unlocked, 0 = locked)
    sem_init(&stock_sem, 0, 1);

    pthread_t t0, t1;

    // Create both customer threads
    pthread_create(&t0, NULL, customer_0, &thread0_id);
    pthread_create(&t1, NULL, customer_1, &thread1_id);

    // Wait for both threads to finish
    pthread_join(t0, NULL);
    pthread_join(t1, NULL);

    // Display the final stock balance after both threads complete
    printf("Final stock balance: %d\n", balance);

    // Destroy the semaphore
    sem_destroy(&stock_sem);

    return 0;
}
