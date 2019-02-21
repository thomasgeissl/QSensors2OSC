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
    signal qmlSignal(string msg)
    signal exportSignal(string msg)
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
                    CheckBox {
                        text: qsTr("Holster Sensor")
                        checked: false
                    }
                    CheckBox {
                        text: qsTr("Humidity Sensor")
                        checked: false
                    }
                    CheckBox {
                        text: qsTr("IR Proximity Sensor")
                        checked: false
                    }
                    CheckBox {
                        text: qsTr("Lid Sensor")
                        checked: false
                    }
                    CheckBox {
                        text: qsTr("Light Sensor")
                        checked: false
                    }
                    CheckBox {
                        text: qsTr("Magnetometer")
                        checked: false
                    }
                    CheckBox {
                        text: qsTr("Orientation Sensor")
                        checked: false
                    }
                    CheckBox {
                        text: qsTr("Pressure Sensor")
                        checked: false
                    }
                    CheckBox {
                        text: qsTr("Proximity Sensor")
                        checked: false
                    }
                    CheckBox {
                        text: qsTr("Rotation Sensor")
                        checked: false
                    }
                    CheckBox {
                        text: qsTr("Tap Sensor")
                        checked: false
                    }
                    CheckBox {
                        text: qsTr("Tilt Sensor")
                        checked: false
                    }
                }

            }

        }

        Page {
            id: outputPage
            signal oscChanged(bool active, string host, int port)
            signal wsChanged(bool active, string host, int port)
            signal mqttChanged(bool active, string host, int port)
            GridLayout {
                id: grid
                anchors.fill: parent
                columns: 5

                CheckBox {
                    id: oscCheckBox
                    text: qsTr("OSC")
                    checked: true
                    onCheckedChanged: {
                        outputPage.oscChanged(oscCheckBox.checked, oscHost.text, oscPort.text)
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
                        outputPage.oscChanged(oscCheckBox.checked, oscHost.text, oscPort.text)
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
                        outputPage.oscChanged(oscCheckBox.checked, oscHost.text, oscPort.text)
                    }
                }


                CheckBox {
                    id: wsCheckBox
                    text: qsTr("websocket")
                    checked: false
                    onCheckedChanged: {
                        outputPage.wsChanged(wsCheckBox.checked, wsHost.text, wsPort.text)
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
                        outputPage.wsChanged(wsCheckBox.checked, wsHost.text, wsPort.text)
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
                        outputPage.wsChanged(wsCheckBox.checked, wsHost.text, wsPort.text)
                    }
                }


                CheckBox {
                    id: mqttCheckBox
                    text: qsTr("mqtt")
                    checked: false
                    onCheckedChanged: {
                        outputPage.mqttChanged(mqttCheckBox.checked, mqttHost.text, mqttPort.text)
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
                        outputPage.mqttChanged(mqttCheckBox.checked, mqttHost.text, mqttPort.text)
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
                        outputPage.mqttChanged(mqttCheckBox.checked, mqttHost.text, mqttPort.text)
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
