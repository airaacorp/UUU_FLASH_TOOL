#include "log.h"
#include <fstream>
#include <ctime>
#include <iostream>
#include <QDateTime>
#include <QDir>

// Global variables
/**
 * @brief Global variable declaration for filePath
 * Mutex to ensure thread-safe logging
 */
std::string logFilePath;
std::mutex logMutex;

/**
 * @brief Generates a log file name based on the current date and time.
 * @return A string containing the generated log file name (e.g., "UUU_Logs_year-month-date_hr_min_sec.txt").
 */
std::string generateLogFileName() {
    std::time_t now = std::time(nullptr);
    char buf[80];
    std::strftime(buf, sizeof(buf), "UUU_Logs_%Y%m%d_%H%M%S.txt", std::localtime(&now));
    return buf;
}

/**
 * @brief Initializes the logging system, setting up the log file path and message handler.
 * Directory where log files will be stored
 * Create the directory if it does not exist
 * Generate new logfile name if logFilePath is empty
 * Install custom message handler for Qt logging
 */
void initializeLogging() {

    QString logDirPath = QDir::homePath() + "/Downloads/UUU-Tool-Logs";

    QDir logDir(logDirPath);
    if (!logDir.exists() && !logDir.mkpath(".")) {
        std::cerr << "Error creating log directory: " << logDirPath.toStdString() << std::endl;
        return;
    }

    if (logFilePath.empty()) {
        logFilePath = logDirPath.toStdString() + "/" + generateLogFileName();
        qDebug() << "logFilePath: " + QString::fromStdString(logFilePath);
        logActivity("Log file path set to: " + logFilePath);
    }

    //Function call
    qInstallMessageHandler(customMessageHandler);
}

/* @brief
    * This function is designed to log activities into a file (logFilePath)
    * while ensuring thread safety using a mutex (logMutex).
    * It handles potential file opening errors by outputting an error message to std::cerr.
*/
/** Ensures thread safety with a mutex to prevent simultaneous access.
 * Opens the log file in append mode to add new entries.
 * Retrieves the current time using std::time and formats it as YYYY-MM-DD HH:MM:SS.
 * Writes the formatted timestamp along with the activity to the log file.
 * Closes the log file after writing the entry.
 *
 * If the log file fails to open, outputs an error message to std::cerr.
 *
 * @param activity The activity string to be logged.
 */

void logActivity(const std::string& activity) {
    std::lock_guard<std::mutex> guard(logMutex);
    std::ofstream logFile(logFilePath, std::ios_base::app);
    if (logFile.is_open()) {
        std::time_t now = std::time(nullptr);
        struct tm timeinfo;
        localtime_r(&now, &timeinfo);

        char timeBuf[100];
        std::strftime(timeBuf, sizeof(timeBuf), "%Y-%m-%d %H:%M:%S", &timeinfo);

        logFile << timeBuf << " - " << activity << std::endl;
        logFile.close();
    } else {
        std::cerr << "Error opening log file: " << logFilePath << std::endl;
    }
}


/**
 * @brief Custom message handler for Qt logging, writes log messages to the log file (logFilePath).
 *
 * @param type The type of the log message (debug, info, warning, etc.).
 * @param context The context information about the log message.
 * @param msg The log message content.
 */
void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    std::lock_guard<std::mutex> guard(logMutex);
    std::ofstream logFile(logFilePath, std::ios_base::app);
    if (logFile.is_open()) {
        QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
        switch (type) {
        case QtDebugMsg:
            logFile << timestamp.toStdString() << " [DEBUG] " << msg.toStdString() << std::endl;
            break;
        case QtInfoMsg:
            logFile << timestamp.toStdString() << " [INFO] " << msg.toStdString() << std::endl;
            break;
        case QtWarningMsg:
            logFile << timestamp.toStdString() << " [WARNING] " << msg.toStdString() << std::endl;
            break;
        case QtCriticalMsg:
            logFile << timestamp.toStdString() << " [CRITICAL] " << msg.toStdString() << std::endl;
            break;
        case QtFatalMsg:
            logFile << timestamp.toStdString() << " [FATAL] " << msg.toStdString() << std::endl;
            break;
        }
        logFile.close();
    } else {
        std::cerr << "Error opening log file: " << logFilePath << std::endl;
    }
}
