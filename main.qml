import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    height: 300
    width:700
    visible: true
    title: qsTr("MFG Tool Application")

        maximumWidth: 700 // Prevents resizing wider than 400
        maximumHeight: 300 // Prevents resizing taller than 300
        minimumHeight: 300
        minimumWidth: 700
    UUU_Tool_Popup {
        height: 300
        width:700
        visible: true
        anchors.centerIn: parent
        onStartClicked: {

        }
        onStopClicked: {

        }
    }
}
