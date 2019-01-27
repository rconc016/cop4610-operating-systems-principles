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

#define NUM_VALUES 20 ///< The number of times each thread will increase the shared variable.

/**
 * @brief Creates and executes the threads.
 * 
 * @param threadCount The number of threads to create.
 */
void createThreads(int threadCount);

/**
 * @brief Increases the shared variable and displays the final result.
 * 
 * @param threadId The ID of the thread being executed.
 * @return void* The pthread library requires the function to be of the generic pointer type.
 */
void* simpleThread(void* threadId);