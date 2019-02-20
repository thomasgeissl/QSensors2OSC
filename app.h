#ifndef APP_H
#define APP_H

#include <QObject>
#include "qoscsender.h"

#include <QAccelerometer>
#include <QAltimeter>
#include <QAmbientLightSensor>
#include <QAmbientTemperatureSensor>
#include <QCompass>
#include <QDistanceSensor>
#include <QGyroscope>
#include <QHolsterSensor>
#include <QHumiditySensor>
#include <QIRProximitySensor>
#include <QLidSensor>
#include <QLightSensor>
#include <QMagnetometer>
#include <QOrientationSensor>
#include <QPressureSensor>
#include <QProximitySensor>
#include <QRotationSensor>
#include <QTapSensor>
#include <QTiltSensor>

#include <QTimer>

#include <QtWebSockets/QtWebSockets>
//#include <QtMqtt/QtMqtt>


class App : public QObject
{
		Q_OBJECT
	public:
        explicit App(QObject *parent = nullptr);
	private:
        QOSCSender *_oscSender;
        QMap<QString, QSensor*> _sensors;
        QAccelerometer *_accelerometer;
        QAltimeter *_altimeter;
        QAmbientLightSensor *_ambientLightSensor;
        QAmbientTemperatureSensor *_ambientTemperatureSensor;
        QCompass *_compass;
        QDistanceSensor *_distanceSensor;
        QGyroscope *_gyroscope;
        QHolsterSensor *_holsterSensor;
        QHumiditySensor *_humiditySensor;
        QIRProximitySensor *_irProximitySensor;
        QLidSensor *_lidSensor;
        QLightSensor *_lightSensor;
        QMagnetometer *_magnetometer;
        QOrientationSensor *_orientationSensor;
        QPressureSensor *_pressureSensor;
        QProximitySensor *_proximitySensor;
        QRotationSensor *_rotationSensor;
        QTapSensor *_tapSensor;
        QTiltSensor *_tiltSensor;

        bool _oscActive;
        bool _wsActive;
        bool _mqttActive;

	signals:

public slots:
        void update();
        bool isSensorAvailable(QString key);
        void setSensorActive(QString key, bool value);
};

#endif // APP_H
