import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Window {
    id:root
    height: 300
    width:700
    visible: true
    title: qsTr("MFG Tool Application")
    // Define a Colors object for managing color themes
    Colors{
        id:colors
    }
    // Prevents resizing wider than 400
    maximumWidth: 700
    // Prevents resizing taller than 300
    maximumHeight: 300
    minimumHeight: 300
    minimumWidth: 700
    //Including a custom popup component
    UUU_Tool_Popup {
        id:mainpopup
        height: 300
        width:700
        visible: true
        anchors.centerIn: parent
        onStartClicked: {

        }
        onStopClicked: {
            mainpopup.exitcontrol=true
        }
        onExistClicked: {
            confirmDialog.open()
        }
    }
    Component.onCompleted: {
        root.closing.connect(onWindowClosing)
    }
    //Handler function for window closing event.
    function onWindowClosing(event) {
        event.accepted = false
        if(mainpopup.exitcontrol===true){
            confirmDialog.open()
        }
    }
    Dialog {
        id: confirmDialog
        height:140
        width: 300
        modal: true
        background: Rectangle {
            color: colors.backgroundcolor
            radius: 8
        }
        visible: false
        anchors.centerIn: parent
        ColumnLayout {
            spacing: 15
            anchors.fill: parent
            anchors.margins: 16
            RowLayout {
                spacing: 10
                Image {
                    id: questmark1id
                    source: "qrc:/Image/QuestionMark.png"
                    Layout.preferredHeight: 40
                    Layout.preferredWidth: 40
                }
                Label {
                    text: "Do you want to Exit..?"
                    font.pixelSize: 16
                    font.family: "Calibri Light"
                    verticalAlignment: Label.AlignVCenter
                    Layout.preferredWidth: 200
                }
            }
            RowLayout {
                spacing: 18
                Layout.alignment: Qt.AlignCenter
                Button {
                    id: yesButton
                    text: "Yes"
                    font.pixelSize: 16
                    Layout.preferredWidth: 80
                    Layout.preferredHeight: 40
                    background: Rectangle {
                        color: colors.bordercolor
                        border.color: yesButton.hovered ? "skyblue" : "gray"
                        border.width: 2
                        radius: 4
                    }
                    onClicked: {
                        confirmDialog.onAccepted()
                    }
                    focus: true
                }
                Button {
                    id: noButton
                    text: "No"
                    font.pixelSize: 16
                    Layout.preferredWidth: 80
                    Layout.preferredHeight: 40
                    background: Rectangle {
                        color: colors.bordercolor
                        border.color: noButton.hovered ? "skyblue" : "gray"
                        border.width: 2
                        radius: 4
                    }
                    onClicked: {
                        confirmDialog.onRejected()
                    }
                }
            }
        }
        onAccepted: {
            // Disconnect the closing handler
            root.closing.disconnect(onWindowClosing)
            root.close()
        }
        onRejected: {
            confirmDialog.visible = false

        }
    }

}
