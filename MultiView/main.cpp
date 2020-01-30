#include "view.h"
#include "viewprovider.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    View *view = new View;

    QQmlApplicationEngine engine;
    engine.addImageProvider(QLatin1String("MultiView"), view->multiView());
    engine.addImageProvider(QLatin1String("MultiSource"), view->multiSource());
    engine.rootContext()->setContextProperty("view", view);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
