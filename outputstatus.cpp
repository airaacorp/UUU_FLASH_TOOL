#include "outputstatus.h"

OutputStatus::OutputStatus(QObject *parent)
    : QObject{parent}
{}

int OutputStatus::success() const
{
    return m_success;
}

int OutputStatus::fail() const
{
    return m_fail;
}

void OutputStatus::successStatus(int success)
{
    m_success = success;
    emit successChanged();
}

void OutputStatus::failStatus(int fail)
{
    m_fail = fail;
    emit failChanged();
}
