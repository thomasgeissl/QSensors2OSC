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

	return app.exec();
}
