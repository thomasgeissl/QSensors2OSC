import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.0


ApplicationWindow {
    id: gui
    visible: true
    width: 640
    height: 480
    title: qsTr("QSensorsStream")
    signal qmlSignal(string msg)
    signal exportSignal(string msg)
    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex
        Page {
            id: inputPage
            Column {
                CheckBox {
                    text: qsTr("Accelerometer")
                    checked: true
                }
                CheckBox {
                    text: qsTr("Altimeter")
                    checked: false
                }
                CheckBox {
                    text: qsTr("Ambient Light Sensor")
                    checked: false
                }
                CheckBox {
                    text: qsTr("Ambient Temperature Sensor")
                    checked: false
                }
                CheckBox {
                    text: qsTr("Compass")
                    checked: true
                }
                CheckBox {
                    text: qsTr("Distance Sensor")
                    checked: false
                }
                CheckBox {
                    text: qsTr("Gyroscope")
                    checked: false
                }
        //        QHolsterSensor *_holsterSensor;
        //        QHumiditySensor *_humiditySensor;
        //        QIRProximitySensor *_irProximitySensor;
        //        QLidSensor *_lidSensor;
        //        QLightSensor *_lightSensor;
        //        QMagnetometer *_magnetometer;
        //        QOrientationSensor *_orientationSensor;
        //        QPressureSensor *_pressureSensor;
        //        QProximitySensor *_proximitySensor;
        //        QRotationSensor *_rotationSensor;
        //        QTapSensor *_tapSensor;
        //        QTiltSensor *_tiltSensor;
            }
        }

        Page {
            id: outputPage
            Column {
                CheckBox {
                    text: qsTr("OSC")
                    checked: true
                }
                CheckBox {
                    text: qsTr("websocket")
                    checked: false
                }
                CheckBox {
                    text: qsTr("mqtt")
                    checked: false
                }
            }
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("input")
        }
        TabButton {
            text: qsTr("output")
        }
    }


}
