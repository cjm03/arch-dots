#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define max 10
pthread_mutex_t pop_mutex;
pthread_mutex_t push_mutex;
int stack[max];
int top = -1;

void* push(void* args)
{
    int val;
    pthread_mutex_lock(&push_mutex);
    pthread_mutex_lock(&pop_mutex);
    printf("Enter val to push: ");
    scanf("%d", &val);
    top++;
    stack[top] = val;
    pthread_mutex_unlock(&pop_mutex);
    pthread_mutex_unlock(&push_mutex);
    printf("%d pushed to stack\n", val);
    return NULL;
}
void* pop(void* args)
{
    int k;
    pthread_mutex_lock(&push_mutex);
    pthread_mutex_lock(&pop_mutex);
    k = stack[top];
    top--;
    printf("Popped %d from the stack\n", k);
    pthread_mutex_unlock(&pop_mutex);
    pthread_mutex_unlock(&push_mutex);
    return NULL;
}

int main(void)
{
    pthread_t tid1, tid2;
    // if (pthread_mutex_init(&pop_mutex, NULL) != 0 || pthread_mutex_init(&push_mutex, NULL) != 0) printf("\n mutex init failure\n");
    pthread_create(&tid1, NULL, &push, NULL);
    pthread_create(&tid2, NULL, &pop, NULL);
    printf("Both threads created\n");
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    // pthread_mutex_destroy(&pop_mutex);
    // pthread_mutex_destroy(&push_mutex);
    return 0;
}
