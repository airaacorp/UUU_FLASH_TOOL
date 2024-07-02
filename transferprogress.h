#ifndef TRANSFERPROGRESS_H
#define TRANSFERPROGRESS_H

#include <QObject>
#include <QTimer>

/**
 * @brief The TransferProgress class handles the progress and status of a transfer operation.
 * This class provides properties and methods to manage the progress of a transfer operation,
 * including overall progress, success,failure status,failureRate and signals for transfer events.
 */
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
     * @brief Constructs a TransferProgress object.
     *
     * @param parent Optional parent object.
     */
    explicit TransferProgress(QObject *parent = nullptr);

    /**
     * @brief Constructs a TransferProgress object.
     *
     * @param parent Optional parent object.
     */
    double progress() const;

    /**
     * @brief Sets the progress of the transfer operation.
     *
     * @param progress New progress value.
     */
    void setProgress(double progress);

    /**
     * @brief Sets the overall progress of the transfer operation.
     *
     * @param overallProgress New overall progress value.
     */
    double overallProgress() const;

    /**
     * @brief Returns the success status of the transfer operation.
     *
     * @return Success status (1 if successful, 0 otherwise).
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
     * @brief Signals that the progress of the transfer operation has changed.
     *
     * @param progress Current progress value.
     */
    void progressChanged(double progress);

    /**
     * @brief Signals that the overall progress of the transfer operation has changed.
     *
     * @param overallProgress Current overall progress value.
     */
    void overallProgressChanged(double overallProgress);

    /**
     * @brief Signals that the transfer operation has started.
     */
    void transferStarted();

    /**
     * @brief Signals that the failure status of the transfer operation has changed.
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
     * @brief Starts the transfer operation.
     */
    void startTransfer();

    /**
     * @brief Stops the transfer operation.
     */
    void stopTransfer();
    // Slots for setting success and fail status
    void successStatus(int success);
    void failStatus(int fail);

private slots:

    /**
     * @brief Updates the progress of the transfer operation.
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

#endif // TRANSFERPROGRESS_H
