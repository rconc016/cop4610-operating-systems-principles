#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_VALUES 20

void createThreads(int threadCount);
void* simpleThread(void* arg);

int sharedVariable = 0;

int main(int argc, char* argv[])
{
    srand(time(NULL));

    createThreads(4);

    return 0;
}

void createThreads(int threadCount)
{
    pthread_t threads[threadCount];
    long index = 0;

    for (index = 0; index < threadCount; index++)
    {
        pthread_create(&threads[index], NULL, simpleThread, (void*) index);
    }

    for (index = 0; index < threadCount; index++)
    {
        pthread_join(threads[index], NULL);
    }
}

void* simpleThread(void* arg)
{
    long which = (long) arg;
    int num, val;

    for (num = 0; num < NUM_VALUES; num++)
    {
        if (rand() > RAND_MAX / 2)
        {
            usleep(500);
        }

        val = sharedVariable;

        //printf("*** thread %ld sees value %d\n", which, val);

        sharedVariable = val + 1;
    }

    val = sharedVariable;
    printf("Thread %ld sees final value %d\n", which, val);
}
