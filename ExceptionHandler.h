#ifndef EXCEPTIONHANDLER_H
#define EXCEPTIONHANDLER_H

#include <exception>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>

class CustomException : public std::exception {
public:
    explicit CustomException(const std::string& message, int errorCode) : message_(message), errorCode_(errorCode) {}
    virtual const char* what() const noexcept override {
        return message_.c_str();
    }
    int errorCode() const {
        return errorCode_;
    }
private:
    std::string message_;
    int errorCode_;
};

// Error codes for exceptions and errors
const int ERROR_FLASH_SUCCESS = 200;
const int ERROR_FLASH_FAILURE = 201;
const int ERROR_PROGRESSBAR_INITIATED = 202;
const int ERROR_PROGRESSBAR_INPROGRESS = 203;
const int ERROR_PROGRESSBAR_COMPLETED = 204;
const int ERROR_SUCCESS = 0;
const int ERROR_FAILURE = 1;
const int ERROR_BAD_CONNECTION = 400;
const int ERROR_FAILURERATE_CODE = 205;

// Error messages corresponding to the error codes
const std::string ERROR_MESSAGE_FLASHING_SUCCESS = "Flashing Successfully Completed";
const std::string ERROR_MESSAGE_FLASHING_FAILURE = "Flashing Failed";
const std::string ERROR_MESSAGE_BAD_CONNECTION = "Bad Connection, Check The Cable Properly";
const std::string ERROR_FAILURE_RATE = "Failure Rate Updated";
const std::string ERROR_PROGRESSBAR_INITIATED_SUCCESS = "ProgressBar Initiated Successfully";
const std::string ERROR_PROGRESSBAR_INPROGRESS_MSG = "Flashing In Progress";
const std::string ERROR_PROGRESSBAR_COMPLETED_MSG = "Flashing Successful, ProgressBar Updated Successfully";
const std::string ERROR_FAILURE_MSG = "Transfer Failed";

const std::string ERROR_LOG_FILE = "error_log.txt";

class ExceptionHandler {
public:
    static void handleException(const CustomException& e);
    static void logError(const std::string& errorMessage, int errorCode);
};

#endif // EXCEPTIONHANDLER_H
