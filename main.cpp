#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QtQml>

#include "tagmodel.h"
#include "tcpserverthread.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    tcpServerThread *tcpThread = new tcpServerThread;
    qmlRegisterSingletonInstance("TagModel",1,0,"TagModel",tagModel::getInstance(tcpThread));

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    tcpThread->start();

    return app.exec();
}
