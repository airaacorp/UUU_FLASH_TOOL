#ifndef USBMONITOR_H
#define USBMONITOR_H

#include <QObject>
#include <QStringList>
#include <QSocketNotifier>

class USBMonitor : public QObject
{
    Q_OBJECT
public:
    explicit USBMonitor(QObject *parent = nullptr);

signals:
    void usbDeviceConnected(const QString &devicePath);
    void usbDeviceDisconnected(const QString &devicePath);
    void usbPortConnected(const QString &portDetails,const QString &portNumber,const QString &hubNumber);
    void usbPortDisconnected(const QString &portDetails,const QString &portNumber,const QString &hubNumber);

private slots:
    void processNetlinkData();

private:
    int m_socket;
    QSocketNotifier *m_notifier;
};

#endif // USBMONITOR_H
