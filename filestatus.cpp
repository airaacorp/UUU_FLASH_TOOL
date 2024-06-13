#include "filestatus.h"

FileStatus::FileStatus(QObject *parent)
    : QObject{parent}
{}

int FileStatus::success() const
{
   return m_success;
}

void FileStatus::setSuccess(int success)
{

}

int FileStatus::fail() const
{
  return m_fail;
}

void FileStatus::setFail(int fail)
{

}

void FileStatus::successStatus(int success)
{
    m_success = success;
    emit successChanged();
}

void FileStatus::failStatus(int fail)
{
    m_fail = fail;
    emit failChanged();
}
