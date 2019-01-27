/**
 * @file logging.h
 * @author Ronald Concepcion (rconc016@fiu.edu)
 * @brief Provides logging functionality to any project.
 * @version 0.1
 * @date 2019-01-27
 * 
 */
#include <stdio.h>

/**
 * @brief Logs a message with a prefix tag.
 * 
 * @param tag The tag to put before the message.
 * @param message The message to be logged.
 */
void logMessage(char* tag, char* message);

/**
 * @brief Logs a message with a debug level tag.
 * 
 * @param message The message to be logged. 
 */
void logDebug(char* message);

/**
 * @brief Logs a message with an information level tag.
 * 
 * @param message The message to be logged. 
 */
void logInformation(char* message);

/**
 * @brief Logs a message with a warning level tag.
 * 
 * @param message The message to be logged. 
 */
void logWarning(char* message);

/**
 * @brief Logs a message with an error level tag.
 * 
 * @param message The message to be logged. 
 */
void logError(char* message);

/**
 * @brief Logs a message with a fatal level tag.
 * 
 * @param message The message to be logged. 
 */
void logFatal(char* message);