#include "failureratestatus.h"
#include <QDebug>

FailureRateStatus::FailureRateStatus(QObject *parent)
    : QObject{parent},m_failureRate(0.0),m_successOperations(0),m_failureOperations(0)
{

}

double FailureRateStatus::failureRate() const
{
    return m_failureRate;
}

int FailureRateStatus::successOperations() const
{
    return m_successOperations;
}

void FailureRateStatus::setSuccessOperations(int successOperations)
{
    qDebug()<<"set success operation assigned"<<successOperations;
}

int FailureRateStatus::failureOperations() const
{
    return m_failureOperations;
}

void FailureRateStatus::setFailureOperations(int failureOperations)
{
    qDebug()<<"set failure operation assigned"<<failureOperations;
}

void FailureRateStatus::setOperations(int failureOperations, int successOperations)
{
    if (m_successOperations != successOperations) {
        m_successOperations = successOperations;
        emit successOperationsChanged();
    }
    if (m_failureOperations != failureOperations) {
        m_failureOperations = failureOperations;
        emit successOperationsChanged();
    }
    updateFailureRate(m_failureOperations, m_successOperations);
}

void FailureRateStatus::updateFailureRate(int failureOperations, int successOperations)
{
    int totalTransfers = failureOperations + successOperations;
    if(totalTransfers == 0){
        m_failureRate = 0.0;
    } else {
        m_failureRate = (double(failureOperations) / totalTransfers) * 100.0;
    }
    emit failureRateChanged();
}
