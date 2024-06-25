#ifndef USBMONITOR_H
#define USBMONITOR_H

#include <QObject>
#include <QStringList>
#include <QSocketNotifier>
#include "ExceptionHandler.h"
#include "log.h"

class USBMonitor : public QObject
{
    Q_OBJECT
public:
    explicit USBMonitor(QObject *parent = nullptr);

signals:
    // Signals emitted when USB events occur
    void usbDeviceConnected(const QString &devicePath);
    void usbDeviceDisconnected(const QString &devicePath);
    void usbPortConnected(const QString &portDetails,const QString &portNumber,const QString &hubNumber);
    void usbPortDisconnected(const QString &portDetails,const QString &portNumber,const QString &hubNumber);

private slots:
    // Slot to process incoming Netlink data
    void processNetlinkData();

private:
    int m_socket; // Netlink socket descriptor
    QSocketNotifier *m_notifier; // Notifier for Netlink socket events
};

#endif // USBMONITOR_H
