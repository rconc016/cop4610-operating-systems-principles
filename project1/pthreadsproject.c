#include "pthreadsproject.h"

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
    int num, val;

    for (num = 0; num < NUM_VALUES; num++)
    {
        if (rand() > RAND_MAX / 2)
        {
            usleep(500);
        }

        val = sharedVariable;

        char message[LOG_SIZE];
        sprintf(message, "Thread %ld sees value %d", which, val);
        logInformation(message);

        sharedVariable = val + 1;
    }

    val = sharedVariable;
    
    char message[LOG_SIZE];
    sprintf(message, "Thread %ld sees final value %d", which, val);
    logInformation(message);
}
