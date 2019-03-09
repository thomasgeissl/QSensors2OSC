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
    auto avaiableSensors = QSensor::sensorTypes();
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
        auto address = "/QSensorsStream/accelerometer";
        if(_oscActive){
            auto message = new QOSCMessage(address);
            message->addFloat(x);
            message->addFloat(y);
            message->addFloat(z);
            _oscSender->send(message);
        }
        if(_wsActive){
            json payload;
            payload["type"] = address;
            payload["x"] = x;
            payload["y"] = y;
            payload["z"] = z;
            std::string text = payload.dump();
            _wsClient->sendTextMessage(QString::fromStdString(text));
        }
    }else if(id == "altimeter"){
        QString address = "/"; address += QCoreApplication::applicationName(); address += id;
        auto value = _altimeter->reading()->altitude();
        if(_oscActive){
            auto message = new QOSCMessage(address);
            message->addFloat(value);
            _oscSender->send(message);
        }
        if(_wsActive){
            json payload;
            payload["type"] = address.toStdString();
            payload["value"] = value;
            std::string text = payload.dump();
            _wsClient->sendTextMessage(QString::fromStdString(text));
        }
    }else if(id == "ambientLightSensor"){
        QString address = "/"; address += QCoreApplication::applicationName(); address += id;
        auto value = _ambientLightSensor->reading()->lightLevel();
        if(_oscActive){
            auto message = new QOSCMessage(address);
            message->addInt(value);
            _oscSender->send(message);
        }
        if(_wsActive){
            json payload;
            payload["type"] = address.toStdString();
            payload["value"] = value;
            std::string text = payload.dump();
            _wsClient->sendTextMessage(QString::fromStdString(text));
        }
    }else if(id == "ambientTemperatureSensor"){
        QString address = "/"; address += QCoreApplication::applicationName(); address += id;
        auto value = _ambientTemperatureSensor->reading()->temperature();
        if(_oscActive){
            auto message = new QOSCMessage(address);
            message->addFloat(value);
            _oscSender->send(message);
        }
        if(_wsActive){
            json payload;
            payload["type"] = address.toStdString();
            payload["value"] = value;
            std::string text = payload.dump();
            _wsClient->sendTextMessage(QString::fromStdString(text));
        }
    }else if(id == "compass"){
        QString address = "/"; address += QCoreApplication::applicationName(); address += id;
        auto azimuth = _compass->reading()->azimuth();
        auto calibrationLevel = _compass->reading()->calibrationLevel();
        if(_oscActive){
            auto message = new QOSCMessage(address);
            message->addFloat(azimuth);
            message->addFloat(calibrationLevel);
            _oscSender->send(message);
        }
        if(_wsActive){
            json payload;
            payload["type"] = address.toStdString();
            payload["azimuth"] = azimuth;
            payload["calibrationLevel"] = calibrationLevel;
            std::string text = payload.dump();
            _wsClient->sendTextMessage(QString::fromStdString(text));
        }
    }else if(id == "distanceSensor"){
        QString address = "/"; address += QCoreApplication::applicationName(); address += id;
        auto value = _distanceSensor->reading()->distance();
        if(_oscActive){
            auto message = new QOSCMessage(address);
            message->addFloat(value);
            _oscSender->send(message);
        }
        if(_wsActive){
            json payload;
            payload["type"] = address.toStdString();
            payload["value"] = value;
            std::string text = payload.dump();
            _wsClient->sendTextMessage(QString::fromStdString(text));
        }
    }else if(id == "gyroscope"){
        QString address = "/"; address += QCoreApplication::applicationName(); address += id;
        auto x = _gyroscope->reading()->x();
        auto y = _gyroscope->reading()->y();
        auto z = _gyroscope->reading()->z();
        if(_oscActive){
            auto message = new QOSCMessage(address);
            message->addFloat(x);
            message->addFloat(y);
            message->addFloat(z);
            _oscSender->send(message);
        }
        if(_wsActive){
            json payload;
            payload["type"] = address.toStdString();
            payload["x"] = x;
            payload["y"] = y;
            payload["z"] = z;
            std::string text = payload.dump();
            _wsClient->sendTextMessage(QString::fromStdString(text));
        }
    }else if(id == "holsterSensor"){
        QString address = "/"; address += QCoreApplication::applicationName(); address += id;
        auto value = _holsterSensor->reading()->holstered();
        if(_oscActive){
            auto message = new QOSCMessage(address);
            message->addBool(value);
            _oscSender->send(message);
        }
        if(_wsActive){
            json payload;
            payload["type"] = address.toStdString();
            payload["value"] = value;
            std::string text = payload.dump();
            _wsClient->sendTextMessage(QString::fromStdString(text));
        }
    }else if(id == "humiditySensor"){
        QString address = "/"; address += QCoreApplication::applicationName(); address += id;
        auto abs = _humiditySensor->reading()->absoluteHumidity();
        auto rel = _humiditySensor->reading()->relativeHumidity();
        if(_oscActive){
            auto message = new QOSCMessage(address);
            message->addFloat(abs);
            message->addFloat(rel);
            _oscSender->send(message);
        }
        if(_wsActive){
            json payload;
            payload["type"] = address.toStdString();
            payload["abs"] = abs;
            payload["rel"] = rel;
            std::string text = payload.dump();
            _wsClient->sendTextMessage(QString::fromStdString(text));
        }
    }else if(id == "irProximitySensor"){
        QString address = "/"; address += QCoreApplication::applicationName(); address += id;
        auto value = _irProximitySensor->reading()->reflectance();
        if(_oscActive){
            auto message = new QOSCMessage(address);
            message->addFloat(value);
            _oscSender->send(message);
        }
        if(_wsActive){
            json payload;
            payload["type"] = address.toStdString();
            payload["value"] = value;
            std::string text = payload.dump();
            _wsClient->sendTextMessage(QString::fromStdString(text));
        }
    }else if(id == "lidSensor"){
        QString address = "/"; address += QCoreApplication::applicationName(); address += id;
        auto back = _lidSensor->reading()->backLidClosed();
        auto front = _lidSensor->reading()->frontLidClosed();
        if(_oscActive){
            auto message = new QOSCMessage(address);
            message->addBool(back);
            message->addBool(front);
            _oscSender->send(message);
        }
        if(_wsActive){
            json payload;
            payload["type"] = address.toStdString();
            payload["back"] = back;
            payload["front"] = front;
            std::string text = payload.dump();
            _wsClient->sendTextMessage(QString::fromStdString(text));
        }
    }else if(id == "lightSensor"){
        QString address = "/"; address += QCoreApplication::applicationName(); address += id;
        auto value = _lightSensor->reading()->lux();
        if(_oscActive){
            auto message = new QOSCMessage(address);
            message->addFloat(value);
            _oscSender->send(message);
        }
        if(_wsActive){
            json payload;
            payload["type"] = address.toStdString();
            payload["value"] = value;
            std::string text = payload.dump();
            _wsClient->sendTextMessage(QString::fromStdString(text));
        }
    }else if(id == "magnetometer"){
        QString address = "/"; address += QCoreApplication::applicationName(); address += id;
        auto x = _magnetometer->reading()->x();
        auto y = _magnetometer->reading()->y();
        auto z = _magnetometer->reading()->z();
        if(_oscActive){
            auto message = new QOSCMessage(address);
            message->addFloat(x);
            message->addFloat(y);
            message->addFloat(z);
            _oscSender->send(message);
        }
        if(_wsActive){
            json payload;
            payload["type"] = address.toStdString();
            payload["x"] = x;
            payload["y"] = y;
            payload["z"] = z;
            std::string text = payload.dump();
            _wsClient->sendTextMessage(QString::fromStdString(text));
        }
    }else if(id == "orientationSensor"){
        QString address = "/"; address += QCoreApplication::applicationName(); address += id;
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
            auto message = new QOSCMessage(address);
            message->addString(value);
            _oscSender->send(message);
        }
        if(_wsActive){
            json payload;
            payload["type"] = address.toStdString();
            payload["value"] = value.toStdString();
            std::string text = payload.dump();
            _wsClient->sendTextMessage(QString::fromStdString(text));
        }
    }else if(id == "pressureSensor"){
        QString address = "/"; address += QCoreApplication::applicationName(); address += id;
        auto value = _pressureSensor->reading()->pressure();
        if(_oscActive){
            auto message = new QOSCMessage(address);
            message->addFloat(value);
            _oscSender->send(message);
        }
        if(_wsActive){
            json payload;
            payload["type"] = address.toStdString();
            payload["value"] = value;
            std::string text = payload.dump();
            _wsClient->sendTextMessage(QString::fromStdString(text));
        }
    }else if(id == "proximitySensor"){
        QString address = "/"; address += QCoreApplication::applicationName(); address += id;
        auto value = _proximitySensor->reading()->close();
        if(_oscActive){
            auto message = new QOSCMessage(address);
            message->addBool(value);
            _oscSender->send(message);
        }
        if(_wsActive){
            json payload;
            payload["type"] = address.toStdString();
            payload["value"] = value;
            std::string text = payload.dump();
            _wsClient->sendTextMessage(QString::fromStdString(text));
        }
    }else if(id == "rotationSensor"){
        QString address = "/"; address += QCoreApplication::applicationName(); address += id;
        auto x = _rotationSensor->reading()->x();
        auto y = _rotationSensor->reading()->y();
        auto z = _rotationSensor->reading()->z();
        if(_oscActive){
            auto message = new QOSCMessage(address);
            message->addFloat(x);
            message->addFloat(y);
            message->addFloat(z);
            _oscSender->send(message);
        }
        if(_wsActive){
            json payload;
            payload["type"] = address.toStdString();
            payload["x"] = x;
            payload["y"] = y;
            payload["z"] = z;
            std::string text = payload.dump();
            _wsClient->sendTextMessage(QString::fromStdString(text));
        }
    }else if(id == "tapSensor"){
        QString address = "/"; address += QCoreApplication::applicationName(); address += id;
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
            auto message = new QOSCMessage(address);
            message->addString(value);
            message->addBool(doubleTap);
            _oscSender->send(message);
        }
        if(_wsActive){
            json payload;
            payload["type"] = address.toStdString();
            payload["value"] = value.toStdString();
            payload["doubleTap"] = doubleTap;
            std::string text = payload.dump();
            _wsClient->sendTextMessage(QString::fromStdString(text));
        }
    }else if(id == "tiltSensor"){
        QString address = "/"; address += QCoreApplication::applicationName(); address += id;
        auto x = _tiltSensor->reading()->xRotation();
        auto y = _tiltSensor->reading()->yRotation();
        if(_oscActive){
            auto message = new QOSCMessage(address);
            message->addFloat(x);
            message->addFloat(y);
            _oscSender->send(message);
        }
        if(_wsActive){
            json payload;
            payload["type"] = address.toStdString();
            payload["x"] = x;
            payload["y"] = y;
            std::string text = payload.dump();
            _wsClient->sendTextMessage(QString::fromStdString(text));
        }
    }
}
