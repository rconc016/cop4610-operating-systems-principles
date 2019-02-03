#include "pthreadsproject.h"

int main(int argc, char* argv[])
{
    int threadCount = 0;

    if (validate(argc, argv, &threadCount) == FALSE)
    {
        return ERROR;
    }

    createThreads(threadCount);

    return SUCCESS;
}

void createThreads(int threadCount)
{
    char message[LOG_SIZE];
    sprintf(message, "Executing %d threads...", threadCount);
    logInformation(message);

    pthread_t threads[threadCount];
    struct thread_data data[threadCount];
    int createIndex = 0;
    int joinIndex = 0;

    pthread_barrier_init(&barrier, NULL, threadCount);

    for (createIndex = 0; createIndex < threadCount; createIndex++)
    {
        data[createIndex].threadId = createIndex;
        data[createIndex].threadCount = threadCount;

        pthread_create(&threads[createIndex], NULL, simpleThread, (void*) &data[createIndex]);
    }

    for (joinIndex = 0; joinIndex < threadCount; joinIndex++)
    {
        pthread_join(threads[joinIndex], NULL);
    }
}

int validate(int argc, char *argv[], int *threadCount)
{
    char message[LOG_SIZE];

    if (argc - 1 != ARG_COUNT)
    {
        sprintf(message, "Invalid number of arguments passed. Expected: %d, Received: %d.", ARG_COUNT, argc - 1);
        logFatal(message);

        return FALSE;
    }

    char** ptr;
    *threadCount = strtol(argv[1], ptr, BASE);

    if (*threadCount <= 0)
    {
        sprintf(message, "Invalid argument passed. Use a number greater than 0.");
        logFatal(message);

        return FALSE;
    }

    return TRUE;
}

void* simpleThread(void* arg)
{
    srand(time(NULL));

    struct thread_data *data = (struct thread_data *) arg;
    int num = 0;

#ifdef PTHREAD_SYNC
    pthread_mutex_lock(&mutex);
#endif

    for (num = 0; num < NUM_VALUES; num++)
    {
        if (rand() > RAND_MAX / 2)
        {
            usleep(500);
        }

        char message[LOG_SIZE];
        sprintf(message, "Thread %d sees value %d", data->threadId, sharedVariable);
        logInformation(message);

        sharedVariable++;
    }

#ifdef PTHREAD_SYNC
    pthread_mutex_unlock(&mutex);
    pthread_barrier_wait(&barrier);
#endif

    char message[LOG_SIZE];
    sprintf(message, "Thread %d sees final value %d", data->threadId, sharedVariable);
    logInformation(message);
}
