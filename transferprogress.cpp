#include "transferprogress.h"
#include <QDebug>
#include <QException>
#include "log.h"
#include "ExceptionHandler.h"

/**
 * @brief Constructs a TransferProgress object with optional parent.
 * Initializes member variables and connects the update timer.
 * @param parent Optional parent object.
 */
TransferProgress::TransferProgress(QObject *parent)
    : QObject(parent), m_progress(0), m_overallProgress(0), m_timer(new QTimer(this)), m_running(false),m_success(0),m_fail(0),m_failureRate(0)
{
    connect(m_timer, &QTimer::timeout, this, &TransferProgress::updateProgress);
}
/**
 * @brief Returns the current progress of the transfer operation.
 * @return Current progress value.
 */
double TransferProgress::progress() const
{
    return m_progress;
}
/**
 * @brief Sets the progress of the transfer operation.
 * Emits progressChanged signal if the progress value changes.
 * @param progress New progress value.
 */
void TransferProgress::setProgress(double progress)
{
    if (m_progress != progress) {
        m_progress = progress;
        emit progressChanged(m_progress);
    }
}
/**
 * @brief Returns the overall progress of the transfer operation.
 * @return Overall progress value.
 */
double TransferProgress::overallProgress() const
{
    return m_overallProgress;
}
/**
 * @brief Sets the overall progress of the transfer operation.
 * Emits overallProgressChanged signal if the overall progress value changes.
 * @param overallProgress New overall progress value.
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

/**
 * @brief TransferProgress::failureRate
 * indicating current failurerate of file transfer operations
 * @return  failurerate percentage
 */
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
    m_success = success;
    emit successChanged();
}
void TransferProgress::failStatus(int fail)
{
    m_fail = fail;
    emit failChanged();
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
    if (m_progress < 1.0) {
        m_progress += 2.10 / 90.0;
        emit progressChanged(m_progress);
    } else {
        m_progress = 0.0;
        m_overallProgress += 1.0 / 9.0;
        emit overallProgressChanged(m_overallProgress);
    }
    }catch(std::exception e){
        CustomException(ERROR_PROGRESSBAR_COMPLETED_MSG,ERROR_SUCCESS);
    }
}
/**
 * @brief TransferProgress::updateFailureRate
 * Updating the failureRate based on failed and successful operations of filetransfer
 * Calculating failure rate as percentage
 * @return emits relevant signal and updates the failurerate.
 */void TransferProgress::updateFailureRate(int failureOperations, int successOperations)
{
    double totalTransfers = failureOperations + successOperations;
    if(totalTransfers == 0){
        m_failureRate = 0.0;
    } else {
        m_failureRate = (failureOperations / totalTransfers) * 100;
    }
    emit failureRateChanged();
}
