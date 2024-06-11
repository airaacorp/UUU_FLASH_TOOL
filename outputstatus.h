#ifndef OUTPUTSTATUS_H
#define OUTPUTSTATUS_H

#include <QObject>

class OutputStatus : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int success READ success WRITE setSuccess NOTIFY successChanged )
    Q_PROPERTY(int fail READ fail WRITE setFail NOTIFY failChanged )
public:
    explicit OutputStatus(QObject *parent = nullptr);
    int success() const;
    int fail() const;

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

#endif // OUTPUTSTATUS_H
