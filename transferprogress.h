
#ifndef TRANSFERPROGRESS_H
#define TRANSFERPROGRESS_H

#include <QObject>
#include <QTimer>

class TransferProgress : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double progress READ progress WRITE setProgress NOTIFY progressChanged)
    Q_PROPERTY(double overallProgress READ overallProgress WRITE setOverallProgress NOTIFY overallProgressChanged)

public:
    explicit TransferProgress(QObject *parent = nullptr);

    double progress() const;
    void setProgress(double progress);

    double overallProgress() const;
    void setOverallProgress(double overallProgress);

signals:
    void progressChanged(double progress);
    void overallProgressChanged(double overallProgress);
    void transferStarted();
    void transferCompleted();
    void progressStopped();

public slots:
    void startTransfer();
    void stopTransfer();

private slots:
    void updateProgress();

private:
    double m_progress;
    double m_overallProgress;
    QTimer *m_timer;
    bool m_running;
};

#endif // TRANSFERPROGRESS_H
