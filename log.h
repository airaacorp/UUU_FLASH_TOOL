#ifndef LOG_H
#define LOG_H

#include <string>
#include <mutex>
#include <QDebug>

// Global variable to store the log file path
extern std::string logFilePath;

// Mutex to ensure thread-safe logging
extern std::mutex logMutex;

/**
 * @brief Generates a log file name based on the current date and time.
 * @return A string containing the generated log file name.
 */
std::string generateLogFileName();

/**
 * @brief Logs an activity message to the log file.
 * @param activity The activity message to log.
 */
void logActivity(const std::string& activity);

/**
 * @brief Initializes the logging system, setting up the log file path and message handler.
 */
void initializeLogging();

/**
 * @brief Custom message handler for Qt's logging system.
 * @param type The type of the message (e.g., debug, warning, critical).
 * @param context The context in which the message was logged.
 * @param msg The message to log.
 */
void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

#endif // LOG_H
