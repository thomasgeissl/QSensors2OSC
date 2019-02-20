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

}
