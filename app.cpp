#include "app.h"
#include "QDebug"

App::App(QObject *parent) : QObject(parent),
    _oscSender(new QOSCSender(this)),
    _accelerometer(new QAccelerometer(this)),
    _altimeter(new QAltimeter(this)),
    _ambientLightSensor(new QAmbientLightSensor(this)),
    _ambientTemperatureSensor(new QAmbientTemperatureSensor(this)),
    _compass(new QCompass(this)),
    _distanceSensor(new QDistanceSensor(this)),
    _gyroscope(new QGyroscope(this)),
    _holsterSensor(new QHolsterSensor(this)),
    _humiditySensor(new QHumiditySensor(this)),
    _irProximitySensor(new QIRProximitySensor(this)),
    _lidSensor(new QLidSensor(this)),
    _lightSensor(new QLightSensor(this)),
    _magnetometer(new QMagnetometer(this)),
    _orientationSensor(new QOrientationSensor(this)),
    _pressureSensor(new QPressureSensor(this)),
    _proximitySensor(new QProximitySensor(this)),
    _rotationSensor(new QRotationSensor(this)),
    _tapSensor(new QTapSensor(this)),
    _tiltSensor(new QTiltSensor(this))
{
    _accelerometer->setAccelerationMode(QAccelerometer::User);

    _sensors["accelerometer"] = _accelerometer;
    _sensors["altimeter"] = _altimeter;
    _sensors["ambientLightSensor"] = _ambientLightSensor;
    _sensors["ambientTemperatureSensor"] = _ambientTemperatureSensor;
    _sensors["compass"] = _compass;
    _sensors["distanceSensor"] = _distanceSensor;
    _sensors["gyroscope"] = _gyroscope;
    _sensors["holsterSensor"] = _holsterSensor;
    _sensors["humiditySensor"] = _humiditySensor;
    _sensors["irProximitySensro"] = _irProximitySensor;
    _sensors["lidSensor"] = _lidSensor;
    _sensors["lightSensor"] = _lightSensor;
    _sensors["magnetoMeter"] = _magnetometer;
    _sensors["orientationSensor"] = _orientationSensor;
    _sensors["pressureSensor"] = _pressureSensor;
    _sensors["proximitySensor"] = _proximitySensor;
    _sensors["rotationSensor"] = _rotationSensor;
    _sensors["tapSensor"] = _tapSensor;
    _sensors["tiltSensor"] = _tiltSensor;

    _oscActive = true;
    _wsActive = false;
    _mqttActive = false;

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000/60);
}

void App::update()
{
    if(_accelerometer->isActive()){
        auto x = _accelerometer->reading()->x();
        auto y = _accelerometer->reading()->y();
        auto z = _accelerometer->reading()->z();
        if(_oscActive){
            auto message = new QOSCMessage("/QSensorsStream/accelerometer");
            message->addFloat(x);
            message->addFloat(y);
            message->addFloat(z);
            _oscSender->send(message);
        }
    }
    if(_altimeter->isActive()){
        auto value = _altimeter->reading()->altitude();
        if(_oscActive){
            auto message = new QOSCMessage("/QSensorsStream/altimeter");
            message->addFloat(value);
            _oscSender->send(message);
        }
    }
    if(_ambientLightSensor->isActive()){
        auto value = _ambientLightSensor->reading()->lightLevel();
        if(_oscActive){
            auto message = new QOSCMessage("/QSensorsStream/ambientLightSensor");
            message->addInt(value);
            _oscSender->send(message);
        }
    }
    if(_ambientTemperatureSensor->isActive()){
        auto value = _ambientTemperatureSensor->reading()->temperature();
        if(_oscActive){
            auto message = new QOSCMessage("/QSensorsStream/ambientTemperatureSensor");
            message->addFloat(value);
            _oscSender->send(message);
        }
    }
    if(_compass->isActive()){
        auto azimuth = _compass->reading()->azimuth();
        auto calibrationLevel = _compass->reading()->calibrationLevel();
        if(_oscActive){
            auto message = new QOSCMessage("/QSensorsStream/compass");
            message->addFloat(azimuth);
            message->addFloat(calibrationLevel);
            _oscSender->send(message);
        }
    }
    if(_distanceSensor->isActive()){
        auto value = _distanceSensor->reading()->distance();
        if(_oscActive){
            auto message = new QOSCMessage("/QSensorsStream/distanceSensor");
            message->addFloat(value);
            _oscSender->send(message);
        }
    }
    if(_gyroscope->isActive()){
        auto x = _gyroscope->reading()->x();
        auto y = _gyroscope->reading()->y();
        auto z = _gyroscope->reading()->z();
        if(_oscActive){
            auto message = new QOSCMessage("/QSensorsStream/gyroscope");
            message->addFloat(x);
            message->addFloat(y);
            message->addFloat(z);
            _oscSender->send(message);
        }
    }

}

bool App::isSensorAvailable(QString key)
{
//    _sensors[key]->
    return false;
}
void App::setSensorActive(QString key, bool value){
    if(!_sensors.contains(key)){
        qDebug() << key << "not found";
        return;
    }
    if(value){
        _sensors[key]->start();
    }else{
        _sensors[key]->stop();
    }
}

void App::oscChanged(bool active, QString host, int port){
    _oscSender->setup(host, port);
    _oscActive = active;
}
void App::wsChanged(bool active, QString host, int port){
//    _oscSender->setup(host, port);
    _wsActive = active;
}
void App::mqttChanged(bool active, QString host, int port){
//    _oscSender->setup(host, port);
    _mqttActive = active;
}
void App::sensorChanged(QString id, bool active){
    setSensorActive(id, active);
}
