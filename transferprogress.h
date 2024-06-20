#ifndef TRANSFERPROGRESS_H
#define TRANSFERPROGRESS_H

#include <QObject>
#include <QTimer>

class TransferProgress : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double progress READ progress WRITE setProgress NOTIFY progressChanged)
    Q_PROPERTY(double overallProgress READ overallProgress WRITE setOverallProgress NOTIFY overallProgressChanged)

    Q_PROPERTY(int success READ success WRITE setSuccess NOTIFY successChanged FINAL)
    Q_PROPERTY(int fail READ fail WRITE setFail NOTIFY failChanged FINAL)

public:
    explicit TransferProgress(QObject *parent = nullptr);

    double progress() const;
    void setProgress(double progress);

    double overallProgress() const;
    void setOverallProgress(double overallProgress);

    int success() const;
    void setSuccess(int success);
    int fail() const;
    void setFail(int fail);

signals:
    void progressChanged(double progress);
    void overallProgressChanged(double overallProgress);
    void transferStarted();
    void transferCompleted();
    void progressStopped();

    void successChanged();
    void failChanged();

public slots:
    void startTransfer();
    void stopTransfer();

    void successStatus(int success);
    void failStatus(int fail);

private slots:
    void updateProgress();

private:
    double m_progress;
    double m_overallProgress;
    QTimer *m_timer;
    bool m_running;

    int m_success;
    int m_fail;
};

#endif // TRANSFERPROGRESS_H
