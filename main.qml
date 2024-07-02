import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Window {
    id:root
    property real scalefactor: 1.0 // Define scalefactor here

    height: 300
    width:700
    visible: true
    title: qsTr("MFG Tool Application")


    Colors{
        id:colors
    }

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
        onExistClicked: {
            confirmDialog.open()
        }
    }

    Component.onCompleted: {
        root.closing.connect(onWindowClosing)
    }

    function onWindowClosing(event) {
        event.accepted = false // Prevent the window from closing immediately
        confirmDialog.open()
    }

    Dialog {
        id: confirmDialog
        height: Math.round(140 * scalefactor)
        width: Math.round(300 * scalefactor)
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
                    Layout.preferredHeight: Math.round(35 * scalefactor)
                    Layout.preferredWidth: Math.round(35 * scalefactor)
                }

                Label {
                    text: "Do you want to Exit..?"
                    font.pixelSize: 14
                    font.family: "Calibri Light"
                    verticalAlignment: Label.AlignVCenter
                    Layout.preferredWidth: Math.round(200 * scalefactor)
                }
            }

            RowLayout {
                spacing: 18
                Layout.alignment: Qt.AlignCenter
                Button {
                    id: yesButton
                    text: "Yes"
                    font.pixelSize: 14
                    Layout.preferredWidth: Math.round(80 * scalefactor)
                    Layout.preferredHeight: Math.round(40 * scalefactor)
                    background: Rectangle {
                        color: colors.backgroundcolor
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
                    font.pixelSize: 14
                    Layout.preferredWidth: Math.round(80 * scalefactor)
                    Layout.preferredHeight: Math.round(40 * scalefactor)
                    background: Rectangle {
                        color: colors.backgroundcolor
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
            root.closing.disconnect(onWindowClosing) // Disconnect the closing handler
            root.close() // Close the window if "Yes" is clicked
        }

        onRejected: {
            // Keep the window open if "No" is clicked
            confirmDialog.visible = false
        }
    }

}
