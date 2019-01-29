/**
 * @file pthreadsproject.h
 * @author Ronald Concepcion (rconc016@fiu.edu)
 * @brief Executes a given number of threads in synchronization.
 * @version 0.1
 * @date 2019-01-27
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#include "../libs/logging/logging.h"

#define TRUE 1        ///< Value mapped to the boolean value true.
#define FALSE 0       ///< Value mapped to the boolean value false.
#define SUCCESS 0     ///< Successful program execution.
#define ERROR 1       ///< Unsuccessful program execution.
#define ARG_COUNT 1   ///< The number of arguments passed to the program.
#define LOG_SIZE 100  ///< The size of the string buffer when writing to the logger.
#define BASE 10       ///< The base to use when parsing an integer from a string.
#define NUM_VALUES 20 ///< The number of times each thread will increase the shared variable.
#define PTHREAD_SYNC  ///< Flag to synchronize threads.

/**
 * @brief Creates and executes the threads.
 * 
 * @param threadCount The number of threads to create.
 */
void createThreads(int threadCount);

/**
 * @brief Validates the command-line arguments passed to the program.
 * 
 * @param argc The number of command-line arguments.
 * @param argv The list of arguments to validate.
 * @param threadCount[out] Stores the number of threads to execute.
 * @return int 1 if the arguments are valid, 0 otherwise.
 */
int validate(int argc, char* argv[], int* threadCount);

/**
 * @brief Increases the shared variable and displays the final result.
 * 
 * @param threadId The ID of the thread being executed.
 * @return void* The pthread library requires the function to be of the generic pointer type.
 */
void* simpleThread(void* threadId);

struct thread_data
{
    int threadId;
    int threadCount;
};