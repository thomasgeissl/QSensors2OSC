#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include "app.h"

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QGuiApplication app(argc, argv);

	QQmlApplicationEngine engine;
	engine.load(QUrl(QLatin1String("qrc:/main.qml")));
	auto gui = engine.rootObjects().first();

	App _app;
//    TODO: move signals back to their objects, not to the root object
    QObject::connect(gui, SIGNAL(oscChanged(bool, QString, int)), &_app, SLOT(oscChanged(bool, QString, int)));
    QObject::connect(gui, SIGNAL(wsChanged(bool, QString, int)), &_app, SLOT(wsChanged(bool, QString, int)));
    QObject::connect(gui, SIGNAL(mqttChanged(bool, QString, int)), &_app, SLOT(mqttChanged(bool, QString, int)));
    QObject::connect(gui, SIGNAL(sensorChanged(QString, bool)), &_app, SLOT(sensorChanged(QString, bool)));
    return app.exec();
}
