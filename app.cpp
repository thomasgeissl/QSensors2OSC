#include "app.h"
#include "QDebug"

App::App(QObject *parent) : QObject(parent),
    _oscSender(new QOSCSender(this)),
    _accelerometer(new QAccelerometer(this)),
    _altimeter(new QAltimeter(this))
{
    _accelerometer->setAccelerationMode(QAccelerometer::User);
    _sensors["accelerometer"] = _accelerometer;


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
    }

}

bool App::isSensorAvailable(QString key)
{
//    _sensors[key]->
    return false;
}
void App::setSensorActive(QString key, bool value){
    if(!_sensors.contains(key)){
        return;
    }
    if(value){
        _sensors[key]->start();
    }else{
        _sensors[key]->stop();
    }
}
