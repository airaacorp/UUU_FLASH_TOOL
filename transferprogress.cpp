#include "transferprogress.h"
#include <QDebug>
#include <QException>
#include "log.h"
#include "ExceptionHandler.h"

/**
 * @brief Initializing the TransferProgress object and setting default values.
 * Connecting the timer's timeout signal to the updateProgress slot.
 */
TransferProgress::TransferProgress(QObject *parent)
    : QObject(parent), m_progress(0), m_overallProgress(0), m_timer(new QTimer(this)), m_running(false),m_success(0),m_fail(0),m_failureRate(0)
{
    connect(m_timer, &QTimer::timeout, this, &TransferProgress::updateProgress);
}
/**
 * @brief TransferProgress::progress
 * Represents the progress of the current individual transfer operation.
 * indicating how much of the current task has been completed as a percentage.
 * @return Single progress bar value.
 */
double TransferProgress::progress() const
{
    return m_progress;
}
/**
 * @brief TransferProgress::setProgress
 * Represents the progress of the current individual transfer operation.
 * indicating how much of the current task has been completed as a percentage.
 * Sets the current progress of the individual transfer operation.
 * Emits progressChanged signal if the progress value changes.
 * @return Setting the single progress value.
 */
void TransferProgress::setProgress(double progress)
{
    if (m_progress != progress) {
        m_progress = progress;
        emit progressChanged(m_progress);
    }
}
/**
 * @brief TransferProgress::overallProgress
 * Represents the overall progress of the entire transfer process.
 * aggregating the progress of all individual transfer operations and.
 * indicating the completion percentage of the total task.
 * @return  Overall progress bar value
 */
double TransferProgress::overallProgress() const
{
    return m_overallProgress;
}
/**
 * @brief TransferProgress::setOverallProgress
 * Represents the overall progress of the entire transfer process .
 * aggregating the progress of all individual transfer operations.indicating the completion percentage of the total task.
 * Sets the overall progress of the transfer operation.Emits overallProgressChanged signal if the overall progress value changes.
 * @return Setting the Overall progress value.
 */
void TransferProgress::setOverallProgress(double overallProgress)
{
    if (m_overallProgress != overallProgress) {
        m_overallProgress = overallProgress;
        emit overallProgressChanged(m_overallProgress);

    }
}
// Getter for success count
int TransferProgress::success() const
{
   return m_success;
}
// Setter for success count
void TransferProgress::setSuccess(int success)
{

    qDebug()<< "SetSuccess "<<success ;
}
// Getter for fail count
int TransferProgress::fail() const
{
   return m_fail;
}

// Setter for fail count
void TransferProgress::setFail(int fail)
{
    qDebug() << "setfail: "<< fail;
}

// Getter method for Retrieves current failure rate of transfer operations
double TransferProgress::failureRate() const
{
    return m_failureRate;
}
/**
 * @brief TransferProgress::startTransfer
 *  Initializes and starts the transfer operation by resetting progress values.
 *  starting the progress timer.
 *  @return emitting a signal to indicate the transfer has begin.
 */
void TransferProgress::startTransfer()
{
    if (m_overallProgress >= 1.0) {
        m_progress = 0;
        m_overallProgress = 0;
        emit progressChanged(m_progress);
        emit overallProgressChanged(m_overallProgress);
    }

    m_running = true;
    m_timer->start(100);
    emit transferStarted();
}
/**
 * @brief TransferProgress::stopTransfer
 * Halts the current (single progress bar) transfer operation, stops the progress timer.
 * increments the failure count, logs the failure.
 * @return  emits relevant signals and updates the failure rate to reflect the interruption.
 */
void TransferProgress::stopTransfer()
{
    try{
    m_running = false;
    m_timer->stop();
    emit progressStopped();
    m_fail += 1;
    qDebug() <<"Failure: " << m_fail;
    logActivity("Failure: " + std::to_string(m_fail));
    emit failChanged();
    updateFailureRate(m_fail, m_success);
    }
    catch(std::exception e){
        throw CustomException(ERROR_FAILURE_MSG,ERROR_FAILURE);
    }
}
void TransferProgress::successStatus(int success)
{
    m_success = success; // Set the success status
    emit successChanged(); // Emit signal to notify success status change
}
void TransferProgress::failStatus(int fail)
{
    m_fail = fail; // Set the fail count
    emit failChanged(); // Emit signal to notify fail count change
}
/**
 * @brief TransferProgress::updateProgress
 * Periodically updates the progress values of the current and overall transfer operations based on timer ticks,
 * and handles the completion of the entire transfer process by stopping the timer and logging success.
 * @return updates the progress values of the single and overall transfer operations
 */
void TransferProgress::updateProgress()
{
    try{
    if (!m_running) {
        return;
    }
    if (m_overallProgress >= 1.0) {
        m_running = false;
        m_timer->stop();
        emit transferCompleted();
        m_success = 1;
        qInfo() <<"Success: " << m_success;
        logActivity("Successfully Completed Flashing : " + std::to_string(m_success));
        emit successChanged();
        updateFailureRate(m_fail, m_success);
        return;
    }
    // Update the individual progress bar
    if (m_progress < 1.0) {
        m_progress += 2.10 / 90.0;
        emit progressChanged(m_progress);
    } else {
        // When individual progress completes, reset m_progress and increment overall progress
        m_progress = 0.0;
        m_overallProgress += 1.0 / 9.0;
        emit overallProgressChanged(m_overallProgress);
    }
    }catch(std::exception e){
        CustomException(ERROR_PROGRESSBAR_COMPLETED_MSG,ERROR_SUCCESS);
    }
}
// Slot to Update failureRate based on number of failed and successful operations
void TransferProgress::updateFailureRate(int failureOperations, int successOperations)
{
    // Calculating the total number of operations
    double totalTransfers = failureOperations + successOperations;
    if(totalTransfers == 0){
        m_failureRate = 0.0;  // Set failure rate to 0.0 if there are no operations
    } else {
        m_failureRate = (failureOperations / totalTransfers) * 100; // Calculating failure rate as percentage
    }
    emit failureRateChanged(); // Emit signal to indicate that the failure rate property has changed
}
