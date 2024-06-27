#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "transferprogress.h"
#include "usbmonitor.h"
#include "ExceptionHandler.h"
#include "log.h"

int main(int argc, char *argv[]) {

    initializeLogging(); // Initialize logging

    try {
        QGuiApplication app(argc, argv);
        USBMonitor usbMonitor; //creating instance for USBMonitor
        TransferProgress transferProgress;//Creating instance for TransferProgress


#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif


        QQmlApplicationEngine engine;

        // Declaring setcontext property to access in qml
        engine.rootContext()->setContextProperty("usbMonitor", &usbMonitor);
        engine.rootContext()->setContextProperty("transferProgress", &transferProgress);


        const QUrl url(QStringLiteral("qrc:/main.qml"));
        QObject::connect(
            &engine,
            &QQmlApplicationEngine::objectCreated,
            &app,
            [url](QObject *obj, const QUrl &objUrl) {
                if (!obj && url == objUrl)
                    QCoreApplication::exit(-1);
            },
            Qt::QueuedConnection);

        engine.load(url);

        logActivity("Application started"); // Log application start

        return app.exec();
    } catch (const CustomException& e) {
        ExceptionHandler::handleException(e);
        logActivity("CustomException caught: " + std::string(e.what())); // Log exception
        return -1;
    } catch (const std::exception& e) {
        ExceptionHandler::handleException(CustomException(e.what(), ERROR_FAILURE));
        logActivity("std::exception caught: " + std::string(e.what())); // Log exception
        return -1;
    } catch (...) {
        ExceptionHandler::handleException(CustomException("Unknown exception caught", ERROR_FAILURE));
        logActivity("Unknown exception caught"); // Log exception
        return -1;
    }
}
