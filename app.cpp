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

    for(auto & key : _sensors.keys()){
        connect(_sensors[key], &QSensor::readingChanged, this, [&]{ readSensor(key); });
    }


    _oscActive = true;
    _wsActive = false;
    _mqttActive = false;

    connect(_wsClient, SIGNAL(connected), this, SLOT(wsConnected));
    connect(_wsClient, SIGNAL(closed), this, SLOT(wsClosed));
}

void App::update()
{

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
    auto url = QUrl(host);
    url.setPort(port);
    _wsClient->open(url);
    _wsActive = active;
}
void App::mqttChanged(bool active, QString host, int port){
//    _oscSender->setup(host, port);
    _mqttActive = active;
}
void App::sensorChanged(QString id, bool active){
    setSensorActive(id, active);
}
void App::wsConnected(){
    connect(_wsClient, SIGNAL(textMessageReceived), this, SLOT(wsMessage));
}
void App::wsClosed(){

}
void App::wsMessage(QString message){

}

void App::readSensor(QString id){
    if(id == "accelerometer"){
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
    }else if(id == "altimeter"){
        auto value = _altimeter->reading()->altitude();
        if(_oscActive){
            auto message = new QOSCMessage("/QSensorsStream/altimeter");
            message->addFloat(value);
            _oscSender->send(message);
        }
    }else if(id == "ambientLightSensor"){
        auto value = _ambientLightSensor->reading()->lightLevel();
        if(_oscActive){
            auto message = new QOSCMessage("/QSensorsStream/ambientLightSensor");
            message->addInt(value);
            _oscSender->send(message);
        }
    }else if(id == "ambientTemperatureSensor"){
        auto value = _ambientTemperatureSensor->reading()->temperature();
        if(_oscActive){
            auto message = new QOSCMessage("/QSensorsStream/ambientTemperatureSensor");
            message->addFloat(value);
            _oscSender->send(message);
        }
    }else if(id == "compass"){
        auto azimuth = _compass->reading()->azimuth();
        auto calibrationLevel = _compass->reading()->calibrationLevel();
        if(_oscActive){
            auto message = new QOSCMessage("/QSensorsStream/compass");
            message->addFloat(azimuth);
            message->addFloat(calibrationLevel);
            _oscSender->send(message);
        }
    }else if(id == "distanceSensor"){
        auto value = _distanceSensor->reading()->distance();
        if(_oscActive){
            auto message = new QOSCMessage("/QSensorsStream/distanceSensor");
            message->addFloat(value);
            _oscSender->send(message);
        }
    }else if(id == "gyroscope"){
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
    }else if(id == "holsterSensor"){
        auto value = _holsterSensor->reading()->holstered();
        if(_oscActive){
            auto message = new QOSCMessage("/QSensorsStream/holsterSensor");
            message->addBool(value);
            _oscSender->send(message);
        }
    }else if(id == "humiditySensor"){
        auto abs = _humiditySensor->reading()->absoluteHumidity();
        auto rel = _humiditySensor->reading()->relativeHumidity();
        if(_oscActive){
            auto message = new QOSCMessage("/QSensorsStream/humiditySensor");
            message->addFloat(abs);
            message->addFloat(rel);
            _oscSender->send(message);
        }
    }else if(id == "irProximitySensor"){
        auto value = _irProximitySensor->reading()->reflectance();
        if(_oscActive){
            auto message = new QOSCMessage("/QSensorsStream/irProximitySensor");
            message->addFloat(value);
            _oscSender->send(message);
        }
    }else if(id == "lidSensor"){
        auto back = _lidSensor->reading()->backLidClosed();
        auto front = _lidSensor->reading()->frontLidClosed();
        if(_oscActive){
            auto message = new QOSCMessage("/QSensorsStream/lidSensor");
            message->addBool(back);
            message->addBool(front);
            _oscSender->send(message);
        }
    }else if(id == "lightSensor"){
        auto value = _lightSensor->reading()->lux();
        if(_oscActive){
            auto message = new QOSCMessage("/QSensorsStream/lightSensor");
            message->addFloat(value);
            _oscSender->send(message);
        }
    }else if(id == "magnetometer"){
        auto x = _magnetometer->reading()->x();
        auto y = _magnetometer->reading()->y();
        auto z = _magnetometer->reading()->z();
        if(_oscActive){
            auto message = new QOSCMessage("/QSensorsStream/magnetometer");
            message->addFloat(x);
            message->addFloat(y);
            message->addFloat(z);
            _oscSender->send(message);
        }
    }else if(id == "orientationSensor"){
        auto orientation = _orientationSensor->reading()->orientation();
        QString value = "undefined";
        if(orientation == _orientationSensor->reading()->TopUp){
            value = "TOPUP";
        }else if(orientation == _orientationSensor->reading()->FaceUp){
            value = "FACEUP";
        }else if(orientation == _orientationSensor->reading()->RightUp){
            value = "RIGHTUP";
        }else if(orientation == _orientationSensor->reading()->TopDown){
            value = "TOPDOWN";
        }else if(orientation == _orientationSensor->reading()->FaceDown){
            value = "FACEDOWN";
        }

        if(_oscActive){
            auto message = new QOSCMessage("/QSensorsStream/orientationSensor");
            message->addString(value);
            _oscSender->send(message);
        }
    }else if(id == "pressureSensor"){
        auto value = _pressureSensor->reading()->pressure();
        if(_oscActive){
            auto message = new QOSCMessage("/QSensorsStream/pressureSensor");
            message->addFloat(value);
            _oscSender->send(message);
        }
    }else if(id == "proximitySensor"){
        auto value = _proximitySensor->reading()->close();
        if(_oscActive){
            auto message = new QOSCMessage("/QSensorsStream/proximitySensor");
            message->addBool(value);
            _oscSender->send(message);
        }
    }else if(id == "rotationSensor"){
        auto x = _rotationSensor->reading()->x();
        auto y = _rotationSensor->reading()->y();
        auto z = _rotationSensor->reading()->z();
        if(_oscActive){
            auto message = new QOSCMessage("/QSensorsStream/rotationSensor");
            message->addFloat(x);
            message->addFloat(y);
            message->addFloat(z);
            _oscSender->send(message);
        }
    }else if(id == "tapSensor"){
        auto doubleTap = _tapSensor->reading()->isDoubleTap();
        auto dir = _tapSensor->reading()->tapDirection();
        QString value = "undefined";
        if(value == _tapSensor->reading()->X){
            value = "X";
        }else if(value == _tapSensor->reading()->Y){
            value = "Y";
        }else if(value == _tapSensor->reading()->Z){
            value = "Z";
        }else if(value == _tapSensor->reading()->X_Neg){
            value = "NEGX";
        }else if(value == _tapSensor->reading()->Y_Neg){
            value = "NEGY";
        }else if(value == _tapSensor->reading()->Z_Neg){
            value = "NEGZ";
        }
        if(_oscActive){
            auto message = new QOSCMessage("/QSensorsStream/tapSensor");
            message->addString(value);
            message->addBool(doubleTap);
            _oscSender->send(message);
        }
    }else if(id == "tiltSensor"){
        auto x = _tiltSensor->reading()->xRotation();
        auto y = _tiltSensor->reading()->yRotation();
        if(_oscActive){
            auto message = new QOSCMessage("/QSensorsStream/tiltSensor");
            message->addFloat(x);
            message->addFloat(y);
            _oscSender->send(message);
        }
    }
}
