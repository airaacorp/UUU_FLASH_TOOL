#ifndef TRANSFERPROGRESS_H
#define TRANSFERPROGRESS_H

#include <QObject>
#include <QTimer>

class TransferProgress : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double progress READ progress WRITE setProgress NOTIFY progressChanged)
    Q_PROPERTY(double overallProgress READ overallProgress WRITE setOverallProgress NOTIFY overallProgressChanged)
    //Defines property definition for success and fail operations
    Q_PROPERTY(int success READ success WRITE setSuccess NOTIFY successChanged FINAL)
    Q_PROPERTY(int fail READ fail WRITE setFail NOTIFY failChanged FINAL)
    //Property definition for failureRate with getter and change notification
    Q_PROPERTY(double failureRate READ failureRate NOTIFY failureRateChanged)
public:
    /**
     * @brief Constructor for the TransferProgress class.
     * @param The parent QObject, default is nullptr.
     */
    explicit TransferProgress(QObject *parent = nullptr);
    /**
     * @brief Retrieves the current progress of the individual (single progress bar) transfer operation.
     * @return The current progress as a double.
     */
    double progress() const;
    /**
     * @brief Sets the progress of the transfer operation.
     * @param The single progress value as double.
     */
    void setProgress(double progress);
    /**
     * @brief Retrieves the overall progress of the transfer operations.
     * @return The overall progress as a double.
     */
    double overallProgress() const;
    /**
     * @brief Sets the overall progress of the transfer operation.
     * @param overallProgress progress value as double.
     */
    void setOverallProgress(double overallProgress);
    // Getters and setters for success and fail counts
    int success() const;
    void setSuccess(int success);
    int fail() const;
    void setFail(int fail);
    // Getter method for failureRate property
    double failureRate() const;
signals:
    /**
     * @brief Signal emitted when the progress changes.
     * @param progress The new progress value.
     */
    void progressChanged(double progress);
    /**
     * @brief Signal emitted when the overall progress changes.
     * @param overallProgress The new overall progress value.
     */
    void overallProgressChanged(double overallProgress);
    /**
     * @brief Signal emitted when the transfer operation starts.
     */
    void transferStarted();
    /**
     * @brief Signal emitted when the transfer operation completes.
     */
    void transferCompleted();
    void progressStopped();
    // Signals for notifying changes in success and fail counts
    void successChanged();
    void failChanged();
    // Signal emitted when failureRate property changes
    void failureRateChanged();
public slots:
    /**
     * @brief Slot to starts the transfer operation.
     */
    void startTransfer();
    /**
     * @brief Slot to stops the transfer operation.
     */
    void stopTransfer();
    // Slots for setting success and fail status
    void successStatus(int success);
    void failStatus(int fail);
private slots:
    /**
     * @brief Slot to updates the progress of the transfer operation.
     */
    void updateProgress();
    //Slot to Update failureRate based on number of failed and successful operations
    void updateFailureRate(int failureOperations, int successOperations);
private:
    double m_progress;
    double m_overallProgress;
    QTimer *m_timer;
    bool m_running;
    int m_success;  // Success count
    int m_fail;    // Fail count
    double m_failureRate; // Member variable for failureRate
};

#endif
