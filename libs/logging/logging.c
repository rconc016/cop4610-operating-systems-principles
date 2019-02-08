#include "logging.h"

void logMessage(char* tag, char* message)
{
    printf("*** %s: %s\n", tag, message);
}

void logDebug(char* message)
{
    logMessage(LOG_LEVEL_DEBUG, message);
}

void logInformation(char* message)
{
    logMessage(LOG_LEVEL_INFO, message);
}

void logWarning(char* message)
{
    logMessage(LOG_LEVEL_WARN, message);
}

void logError(char* message)
{
    logMessage(LOG_LEVEL_ERROR, message);
}

void logFatal(char* message)
{
    logMessage(LOG_LEVEL_FATAL, message);
}