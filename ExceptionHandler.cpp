#include "ExceptionHandler.h"
#include <sys/stat.h> // For mkdir function

void ExceptionHandler::handleException(const CustomException& e) {
    std::cerr << "Exception caught: " << e.what() << " (Error Code: " << e.errorCode() << ")" << std::endl;
    logError(e.what(), e.errorCode());
}

void ExceptionHandler::logError(const std::string& errorMessage, int errorCode) {
    const char* logDir = "/home/test/Downloads/Application_Logs";

    // Check if the directory exists, if not, create it
    struct stat st;
    if (stat(logDir, &st) != 0) {
        if (mkdir(logDir, 0777) != 0) {
            std::cerr << "Error creating directory: " << logDir << std::endl;
            return;
        }
    }

    std::string logFilePath = std::string(logDir) + "/" + ERROR_LOG_FILE;
    std::ofstream logFile(logFilePath, std::ios_base::app);
    if (logFile.is_open()) {
        std::time_t now = std::time(nullptr);
        logFile << std::ctime(&now) << " - Error Code: " << errorCode << " - " << errorMessage << std::endl;
        logFile.close();
    } else {
        std::cerr << "Error opening log file: " << logFilePath << std::endl;
    }
}
