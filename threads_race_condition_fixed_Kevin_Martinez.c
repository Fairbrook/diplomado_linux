#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int counter = 0;
// Mutex for excluding thread increments
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

void *thread_func(void *args) {
  int i;
  for (i = 0; i < 10000000; i++) {
    // Lock for locking the mutex
    // Note: This makes the threads much slower than secuential
    pthread_mutex_lock(&counter_mutex);
    counter++;
    // Free the lock for the other thread to make the lock
    pthread_mutex_unlock(&counter_mutex);
  }
  return NULL;
}

int main() {
  pthread_t thread_id[2];

  printf("I will create two threads\n");
  printf("Point 1 >> X is: %d\n", counter);
  pthread_create(&thread_id[0], NULL, &thread_func, NULL);
  pthread_create(&thread_id[1], NULL, &thread_func, NULL);
  printf("The threads has been created\n");
  pthread_join(thread_id[0], NULL);
  pthread_join(thread_id[1], NULL);
  printf("The threads have exited\n");
  printf("Point 2 >> X is: %d\n", counter);
  pthread_exit(NULL);
  return 0;
}
