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
    explicit TransferProgress(QObject *parent = nullptr);

    double progress() const;
    void setProgress(double progress);

    double overallProgress() const;
    void setOverallProgress(double overallProgress);
    // Getters and setters for success and fail counts
    int success() const;
    void setSuccess(int success);
    int fail() const;
    void setFail(int fail);
    // Getter method for failureRate property
    double failureRate() const;

signals:
    void progressChanged(double progress);
    void overallProgressChanged(double overallProgress);
    void transferStarted();
    void transferCompleted();
    void progressStopped();
    // Signals for notifying changes in success and fail counts
    void successChanged();
    void failChanged();
    // Signal emitted when failureRate property changes
    void failureRateChanged();

public slots:
    void startTransfer();
    void stopTransfer();
    // Slots for setting success and fail status
    void successStatus(int success);
    void failStatus(int fail);

private slots:
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
