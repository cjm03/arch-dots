/*
 *  pthread_join: make the thread wait for the completion of all its spawned threads. if not used, thread will exit upon completion, ignoring states of its spawned threads.
 *      - blocks the calling thread until the thread specified in this function terminates
 *  pthread_mutex_init: initialize the mutex object with specified attributes. 
 *      - initializes in an unlocked state
 *  pthread_mutex_lock: locks specified mutex. if mutex is already locked, the calling thread is suspended and will wait until mutex is unlocked
 *      - returns mutex in locked state. locking thread becomes the mutex owner and remains the owner until it unlocks the mutex
 *  pthread_mutex_unlock: unlocks specified mutex. the thread that invoked the lock function will become unblocked and acquire the mutex, allowing the waiting thread to access and lock the mutex.
 *      - if no threads are waiting for the mutex, it remains unlocked and without an owner
 *  pthread_mutex_destroy: destroys a mutex and frees its allocated resources. 
 *      - mutex must be unlocked
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* runThread(void* arg)
{
    int i;
    printf("Runing Thread \n");
    for (i = 1; i <= 5; i++) printf("%d\n", i);
    return NULL;
}

int main(void)
{
    pthread_t tid;
    printf("In main function\n");
    pthread_create(&tid, NULL, runThread, NULL);
    pthread_join(tid, NULL);    // pthread_join ensures that main does not terminate before the thread completes its task
    printf("Thread over\n");
    return 0;
}
