#include "usbmonitor.h"
#include <QDebug>
#include <QGuiApplication>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/netlink.h>

USBMonitor::USBMonitor(QObject *parent) : QObject(parent), m_socket(-1), m_notifier(nullptr)
{
    m_socket = socket(AF_NETLINK, SOCK_RAW, NETLINK_KOBJECT_UEVENT);
    if (m_socket == -1) {
        qWarning() << "Failed to create Netlink socket:" << strerror(errno);
        return;
    }

    struct sockaddr_nl addr;
    memset(&addr, 0, sizeof(addr));
    addr.nl_family = AF_NETLINK;
    addr.nl_pid = getpid();
    addr.nl_groups = 1; // Subscribe to multicast group 1 (kernel events)
    if (bind(m_socket, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        qWarning() << "Failed to bind Netlink socket:" << strerror(errno);
        close(m_socket);
        return;
    }

    connect(QGuiApplication::instance(), &QGuiApplication::aboutToQuit, [this]() {
        close(m_socket);
    });

    m_notifier = new QSocketNotifier(m_socket, QSocketNotifier::Read, this);
    connect(m_notifier, &QSocketNotifier::activated, this, &USBMonitor::processNetlinkData);
}

//Processing_NetLinkData and Storing in buffer

void USBMonitor::processNetlinkData()
{
    QByteArray buffer(4096, Qt::Uninitialized);
    struct iovec iov = { buffer.data(), static_cast<size_t>(buffer.size()) };
    struct sockaddr_nl sa;
    struct msghdr msg = { &sa, sizeof(sa), &iov, 1, nullptr, 0, 0 };

    ssize_t len = recvmsg(m_socket, &msg, 0);
    if (len == -1) {
        qWarning() << "Error receiving message from Netlink socket:" << strerror(errno);
        return;
    }

    QString event = QString::fromUtf8(buffer.constData(), len);
    QStringList lines = event.split('\0');
    QString devicePath;
    for (const QString &line : lines) {
        if (line.startsWith("DEVNAME=")) {
            devicePath = "/dev/" + line.mid(8);

            break;
        }
    }

    if (event.contains("usb") && event.contains("add") && !devicePath.isEmpty()) {
        emit usbDeviceConnected(devicePath);
    } else if (event.contains("usb") && event.contains("remove") && !devicePath.isEmpty()) {
        emit usbDeviceDisconnected(devicePath);
    }
}
