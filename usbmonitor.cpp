#include "usbmonitor.h"
#include <QDebug>
#include <QGuiApplication>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <cstring>
#include "log.h"
#include "ExceptionHandler.h"

// Constructor initializes the USBMonitor object
USBMonitor::USBMonitor(QObject *parent) : QObject(parent), m_socket(-1), m_notifier(nullptr)
{
    try {
        qDebug() << "Initializing USBMonitor";
        logActivity("Initializing USBMonitor");

        // Create a Netlink socket
        m_socket = socket(AF_NETLINK, SOCK_RAW, NETLINK_KOBJECT_UEVENT);
        if (m_socket == -1) {
            throw CustomException("Failed to create Netlink socket", ERROR_FAILURE);
        }
        qDebug() << "Netlink socket created successfully";
        logActivity("Netlink socket created successfully");

        // Bind the Netlink socket
        struct sockaddr_nl addr;
        memset(&addr, 0, sizeof(addr));
        addr.nl_family = AF_NETLINK;
        addr.nl_pid = getpid();
        addr.nl_groups = 1; // Subscribe to multicast group 1 (kernel events)
        if (bind(m_socket, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
            throw CustomException("Failed to bind Netlink socket", ERROR_FAILURE);
        }
        qDebug() << "Netlink socket bound successfully";
        logActivity("Netlink socket bound successfully");

        // Connect a cleanup function to application exit
        connect(QGuiApplication::instance(), &QGuiApplication::aboutToQuit, [this]() {
            qDebug() << "Application is about to quit, closing Netlink socket";
            logActivity("Application is about to quit, closing Netlink socket");
            close(m_socket);
        });

        // Setup QSocketNotifier for Netlink socket
        m_notifier = new QSocketNotifier(m_socket, QSocketNotifier::Read, this);
        connect(m_notifier, &QSocketNotifier::activated, this, &USBMonitor::processNetlinkData);

        qDebug() << "USBMonitor initialization complete";
        logActivity("USBMonitor initialization complete");

    } catch (const CustomException &e) {
        // Handle custom exceptions
        ExceptionHandler::handleException(e);
        throw;  // Re-throw exception after handling to ensure the program is aware of initialization failure
    } catch (const std::exception &e) {
        // Handle unexpected std exceptions
        logActivity("Unexpected error during initialization: " + std::string(e.what()));
        throw;  // Rethrow unexpected exceptions
    }
}

// Slot to process incoming Netlink data
void USBMonitor::processNetlinkData()
{
    try {
        qDebug() << "Processing Netlink data";
        logActivity("Processing Netlink data");

        // Buffer to store incoming data
        QByteArray buffer(4096, Qt::Uninitialized);

        // Setup structures for receiving message
        struct iovec iov = { buffer.data(), static_cast<size_t>(buffer.size()) };
        struct sockaddr_nl sa;
        struct msghdr msg = { &sa, sizeof(sa), &iov, 1, nullptr, 0, 0 };

        // Receive message from Netlink socket
        ssize_t len = recvmsg(m_socket, &msg, 0);
        if (len == -1) {
            throw CustomException("Error receiving message from Netlink socket", ERROR_FAILURE);
        }
        qDebug() << "Message received from Netlink socket, length:" << len;
        logActivity("Message received from Netlink socket, length: " + std::to_string(len));

        // Convert received data to QString
        QString event = QString::fromUtf8(buffer.constData(), len);
        qDebug() << "Event received:" << event;
        logActivity("Event received: " + event.toStdString());

        // Split event data into lines
        QStringList lines = event.split('\0');
        QString devicePath;
        QString portDetails;
        QString portNumber;
        QString hubNumber;

        // Extract port details (port and hub number)
        for (const QString &line : lines) {
            if (line.startsWith("DEVNAME=bus")) {
                portDetails = line.mid(8);
                QStringList bus = portDetails.split("/");
                portNumber = bus.last();
                hubNumber = bus.at(bus.count() - 2);
                break;
            }
        }

        // Extract device path
        for (const QString &line : lines) {
            if (line.startsWith("DEVNAME=")) {
                devicePath = "/dev/" + line.mid(8);
                break;
            }
        }

        // Emit signals based on received events
        if (event.contains("usb") && event.contains("add") && !portDetails.isEmpty()) {
            emit usbPortConnected(portDetails, portNumber, hubNumber);
        } else if (event.contains("usb") && event.contains("remove") && !portDetails.isEmpty()) {
            emit usbPortDisconnected(portDetails, portNumber, hubNumber);
        }

        if (event.contains("usb") && event.contains("add") && !devicePath.isEmpty()) {
            emit usbDeviceConnected(devicePath);
        } else if (event.contains("usb") && event.contains("remove") && !devicePath.isEmpty()) {
            emit usbDeviceDisconnected(devicePath);
        }

    } catch (const CustomException &e) {
        // Handle custom exceptions during Netlink data processing
        ExceptionHandler::handleException(e);
    } catch (const std::exception &e) {
        // Handle unexpected std exceptions during Netlink data processing
        logActivity("Unexpected error during Netlink data processing: " + std::string(e.what()));
    }
}
