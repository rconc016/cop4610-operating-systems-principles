#include "logging.h"

void logMessage(char* tag, char* message)
{
    printf("*** %s: %s\n", tag, message);
}

void logDebug(char* message)
{
    logMessage("Debug", message);
}

void logInformation(char* message)
{
    logMessage("Information", message);
}

void logWarning(char* message)
{
    logMessage("Warning", message);
}

void logError(char* message)
{
    logMessage("Error", message);
}

void logFatal(char* message)
{
    logMessage("Fatal", message);
}