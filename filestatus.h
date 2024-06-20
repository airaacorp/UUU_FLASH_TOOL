#ifndef FILESTATUS_H
#define FILESTATUS_H

#include <QObject>

class FileStatus : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int success READ success WRITE setSuccess NOTIFY successChanged FINAL)
    Q_PROPERTY(int fail READ fail WRITE setFail NOTIFY failChanged FINAL)
public:
    explicit FileStatus(QObject *parent = nullptr);
    int success() const;
    void setSuccess(int success);
    int fail() const;
    void setFail(int fail);

signals:
    void successChanged();
    void failChanged();
public slots:
     void successStatus(int success);
     void failStatus(int fail);
private:
     int m_success = 0;
     int m_fail = 0;
};

#endif // FILESTATUS_H
