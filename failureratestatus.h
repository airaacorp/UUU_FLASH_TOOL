#ifndef FAILURERATESTATUS_H
#define FAILURERATESTATUS_H

#include <QObject>

class FailureRateStatus : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double failureRate READ failureRate NOTIFY failureRateChanged)
    Q_PROPERTY(int successOperations READ successOperations WRITE setSuccessOperations NOTIFY successOperationsChanged)
    Q_PROPERTY(int failureOperations READ failureOperations WRITE setFailureOperations NOTIFY failureOperationsChanged)

public:
    explicit FailureRateStatus(QObject *parent = nullptr);
    double failureRate() const;
    int successOperations() const;
    void setSuccessOperations(int successOperations);

    int failureOperations() const;
    void setFailureOperations(int failureOperations);

signals:
    void failureRateChanged();
    void successOperationsChanged();
    void failureOperationsChanged();

public slots:
    void setOperations(int failureOperations, int successOperations);
    void updateFailureRate(int failureOperations, int successOperations);

private:
    double m_failureRate;
    int m_successOperations;
    int m_failureOperations;

};

#endif // FAILURERATESTATUS_H
