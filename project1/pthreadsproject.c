#include "pthreadsproject.h"

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int sharedVariable = 0;

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
    int createIndex = 0;
    int joinIndex = 0;

    for (createIndex = 0; createIndex < threadCount; createIndex++)
    {
        long threadId = createIndex;
        pthread_create(&threads[createIndex], NULL, simpleThread, (void*) threadId);
    }

    for (joinIndex = 0; joinIndex < threadCount; joinIndex++)
    {
        pthread_join(threads[joinIndex], NULL);
    }
}

int validate(int argc, char* argv[], int* threadCount)
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

    long which = (long) arg;
    int num = 0;

#ifdef PTHREAD_SYNC
    pthread_mutex_lock(&mutex1);
#endif
    for (num = 0; num < NUM_VALUES; num++)
    {
        if (rand() > RAND_MAX / 2)
        {
            usleep(500);
        }

        char message[LOG_SIZE];
        sprintf(message, "Thread %ld sees value %d", which, sharedVariable);
        logInformation(message);

        sharedVariable++;
    }

    char message[LOG_SIZE];
    sprintf(message, "Thread %ld sees final value %d", which, sharedVariable);
    logInformation(message);
#ifdef PTHREAD_SYNC
    pthread_mutex_unlock(&mutex1);
#endif
}
