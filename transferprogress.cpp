#include "transferprogress.h"

TransferProgress::TransferProgress(QObject *parent)
    : QObject(parent), m_progress(0), m_overallProgress(0), m_timer(new QTimer(this)), m_running(false)
{
    connect(m_timer, &QTimer::timeout, this, &TransferProgress::updateProgress);
}

double TransferProgress::progress() const
{
    return m_progress;
}

void TransferProgress::setProgress(double progress)
{
    if (m_progress != progress) {
        m_progress = progress;
        emit progressChanged(m_progress);
    }
}

double TransferProgress::overallProgress() const
{
    return m_overallProgress;
}

void TransferProgress::setOverallProgress(double overallProgress)
{
    if (m_overallProgress != overallProgress) {
        m_overallProgress = overallProgress;
        emit overallProgressChanged(m_overallProgress);
    }
}

int TransferProgress::success() const
{
   return m_success;
}

void TransferProgress::setSuccess(int success)
{

}

int TransferProgress::fail() const
{
   return m_fail;
}

void TransferProgress::setFail(int fail)
{

}

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

void TransferProgress::stopTransfer()
{
    m_running = false;
    m_timer->stop();
    emit progressStopped();
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

void TransferProgress::updateProgress()
{
    if (!m_running) {
        return;
    }

    // Stop the transfer if overall progress reaches 100%
    if (m_overallProgress >= 1.0) {
        m_running = false;
        m_timer->stop();
        emit transferCompleted();
        return; // Exit the function to prevent further updates
    }

    // Update the individual progress bar
    if (m_progress < 1.0) {
        m_progress += 2.10 / 90.0; // Increment m_progress so it completes 1 cycle in 10 ticks
        emit progressChanged(m_progress);
    } else {
        // When individual progress completes, reset m_progress and increment overall progress
        m_progress = 0.0; // Reset m_progress for the next cycle
        m_overallProgress += 1.0 / 9.0; // Increment overall progress so it completes 1 cycle in 9 cycles of m_progress
        emit overallProgressChanged(m_overallProgress);
    }
}
