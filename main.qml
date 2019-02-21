import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Dialogs 1.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12



ApplicationWindow {
    id: gui
    visible: true
    width: 640
    height: 480
    title: qsTr("QSensorsStream")
    signal oscChanged(bool active, string host, int port)
    signal wsChanged(bool active, string host, int port)
    signal mqttChanged(bool active, string host, int port)
    signal sensorChanged(string id, bool active)
    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex
        Page {
            id: inputPage
            ScrollView {
                clip: true
                anchors.fill: parent
                Column {
                    CheckBox {
                        id: accelerometerCheckBox
                        text: qsTr("Accelerometer")
                        checked: false
                        onCheckedChanged: {
                            gui.sensorChanged("accelerometer", accelerometerCheckBox.checked)
                        }
                    }
                    CheckBox {
                        id: altimeterCheckBox
                        text: qsTr("Altimeter")
                        checked: false
                        onCheckedChanged: {
                            gui.sensorChanged("altimeter", altimeterCheckBox.checked)
                        }
                    }
                    CheckBox {
                        id: ambientLightSensorCheckBox
                        text: qsTr("Ambient Light Sensor")
                        checked: false
                        onCheckedChanged: {
                            gui.sensorChanged("ambientLightSensor", ambientLightSensorCheckBox.checked)
                        }
                    }
                    CheckBox {
                        id: ambientTemperatureSensorCheckBox
                        text: qsTr("Ambient Temperature Sensor")
                        checked: false
                        onCheckedChanged: {
                            gui.sensorChanged("ambientTemperatureSensor", ambientTemperatureSensorCheckBox.checked)
                        }
                    }
                    CheckBox {
                        id: compassCheckBox
                        text: qsTr("Compass")
                        checked: false
                        onCheckedChanged: {
                            gui.sensorChanged("compass", compassCheckBox.checked)
                        }
                    }
                    CheckBox {
                        id: distanceSensorCheckBox
                        text: qsTr("Distance Sensor")
                        checked: false
                        onCheckedChanged: {
                            gui.sensorChanged("distanceSensor", distanceSensorCheckBox.checked)
                        }
                    }
                    CheckBox {
                        id: gyroscopeCheckBox
                        text: qsTr("Gyroscope")
                        checked: false
                        onCheckedChanged: {
                            gui.sensorChanged("gyroscope", gyroscopeCheckBox.checked)
                        }
                    }
                    CheckBox {
                        id: holsterSensorCheckBox
                        text: qsTr("Holster Sensor")
                        checked: false
                        onCheckedChanged: {
                            gui.sensorChanged("holsterSensor", holsterSensorCheckBox.checked)
                        }
                    }
                    CheckBox {
                        id: humiditySensorCheckBox
                        text: qsTr("Humidity Sensor")
                        checked: false
                        onCheckedChanged: {
                            gui.sensorChanged("humiditySensor", humiditySensor.checked)
                        }
                    }
                    CheckBox {
                        id: irProximitySensorCheckBox
                        text: qsTr("IR Proximity Sensor")
                        checked: false
                        onCheckedChanged: {
                            gui.sensorChanged("irProximitySensor", irProximitySensorCheckBox.checked)
                        }
                    }
                    CheckBox {
                        id: lidSensorCheckBox
                        text: qsTr("Lid Sensor")
                        checked: false
                        onCheckedChanged: {
                            gui.sensorChanged("lidSensor", lidSensorCheckBox.checked)
                        }
                    }
                    CheckBox {
                        id: lightSensorCheckBox
                        text: qsTr("Light Sensor")
                        checked: false
                        onCheckedChanged: {
                            gui.sensorChanged("lightSensor", lightSensorCheckBox.checked)
                        }
                    }
                    CheckBox {
                        id: magnetoMeterCheckBox
                        text: qsTr("Magnetometer")
                        checked: false
                        onCheckedChanged: {
                            gui.sensorChanged("magnetoMeter", magnetoMeterCheckBox.checked)
                        }
                    }
                    CheckBox {
                        id: orientationSensorCheckBox
                        text: qsTr("Orientation Sensor")
                        checked: false
                        onCheckedChanged: {
                            gui.sensorChanged("orientationSensor", orientationSensorCheckBox.checked)
                        }
                    }
                    CheckBox {
                        id: pressureSensorCheckBox
                        text: qsTr("Pressure Sensor")
                        checked: false
                        onCheckedChanged: {
                            gui.sensorChanged("pressureSensor", pressureSensorCheckBox.checked)
                        }
                    }
                    CheckBox {
                        id: proximitySensorCheckBox
                        text: qsTr("Proximity Sensor")
                        checked: false
                        onCheckedChanged: {
                            gui.sensorChanged("proximitySensor", proximitySensorCheckBox.checked)
                        }
                    }
                    CheckBox {
                        id: rotationSensorCheckBox
                        text: qsTr("Rotation Sensor")
                        checked: false
                        onCheckedChanged: {
                            gui.sensorChanged("rotationSensor", rotationSensorCheckBox.checked)
                        }
                    }
                    CheckBox {
                        id: tapSensorCheckBox
                        text: qsTr("Tap Sensor")
                        checked: false
                        onCheckedChanged: {
                            gui.sensorChanged("tapSensor", tapSensorCheckBox.checked)
                        }
                    }
                    CheckBox {
                        id: tiltSensorCheckBox
                        text: qsTr("Tilt Sensor")
                        checked: false
                        onCheckedChanged: {
                            gui.sensorChanged("tiltSensor", tiltSensorCheckBox.checked)
                        }
                    }
                }

            }

        }

        Page {
            id: outputPage
            GridLayout {
                id: grid
                anchors.fill: parent
                columns: 5

                CheckBox {
                    id: oscCheckBox
                    text: qsTr("OSC")
                    checked: true
                    onCheckedChanged: {
                        gui.oscChanged(oscCheckBox.checked, oscHost.text, oscPort.text)
                    }
                }
                Text{
                    text: "Host"
                }
                TextInput {
                    id: oscHost
                    text: "localhost"
                    cursorVisible: false
                    onTextChanged: {
                        gui.oscChanged(oscCheckBox.checked, oscHost.text, oscPort.text)
                    }
                }
                Text{
                    text: "Port"
                }
                TextInput {
                    id: oscPort
                    text: "8000"
                    cursorVisible: false
                    validator: IntValidator{bottom: 1000; top: 56000;}
                    onTextChanged: {
                        gui.oscChanged(oscCheckBox.checked, oscHost.text, oscPort.text)
                    }
                }


                CheckBox {
                    id: wsCheckBox
                    text: qsTr("websocket")
                    checked: false
                    onCheckedChanged: {
                        gui.wsChanged(wsCheckBox.checked, wsHost.text, wsPort.text)
                    }
                }
                Text{
                    text: "Host"
                }
                TextInput {
                    id: wsHost
                    text: "localhost"
                    cursorVisible: false
                    onTextChanged: {
                        gui.wsChanged(wsCheckBox.checked, wsHost.text, wsPort.text)
                    }
                }
                Text{
                    text: "Port"
                }
                TextInput {
                    id: wsPort
                    text: "80"
                    cursorVisible: false
                    validator: IntValidator{bottom: 1000; top: 56000;}
                    onTextChanged: {
                        gui.wsChanged(wsCheckBox.checked, wsHost.text, wsPort.text)
                    }
                }


                CheckBox {
                    id: mqttCheckBox
                    text: qsTr("mqtt")
                    checked: false
                    onCheckedChanged: {
                        gui.mqttChanged(mqttCheckBox.checked, mqttHost.text, mqttPort.text)
                    }
                }
                Text{
                    text: "Host"
                }
                TextInput {
                    id: mqttHost
                    text: "localhost"
                    cursorVisible: false
                    onTextChanged: {
                        gui.mqttChanged(mqttCheckBox.checked, mqttHost.text, mqttPort.text)
                    }
                }
                Text{
                    text: "Port"
                }
                TextInput {
                    id: mqttPort
                    text: "1883"
                    cursorVisible: false
                    validator: IntValidator{bottom: 1000; top: 56000;}
                    onTextChanged: {
                        gui.mqttChanged(mqttCheckBox.checked, mqttHost.text, mqttPort.text)
                    }
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
