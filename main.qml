import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window {
    id:root
    property real scalefactor: 1.0 // Define scalefactor here

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

    Component.onCompleted: {
        root.closing.connect(onWindowClosing)
    }

    function onWindowClosing(event) {
        event.accepted = false // Prevent the window from closing immediately
        confirmDialog.open()
    }

    Dialog {
        id: confirmDialog
        // title: "Confirmation"
        height: Math.round(120 * scalefactor)
        width: Math.round(320 * scalefactor)
        modal: true
        background: Rectangle {
            color: "#e5e5e5"
            radius: 8
        }
        visible: false
        x: (root.width - width) / 2
        y: (root.height - height) / 2

        Column {
            spacing: 15
            anchors.left: parent.left
            // anchors.top: parent.top
            anchors.margins: 16


            // Row {
            //     Label {
            //         text: "Confirmation"
            //         font.pointSize: 15 /*Screen.height * 0.014*/
            //         font.family: "Calibri Light"
            //         verticalAlignment: Label.AlignVCenter
            //     }
            // }

            Row {
                spacing: 10
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenterOffset: 50 // Move the row downwards
                Image {
                    id: questmark1id
                    source: "qrc:/Image/QuestionMark.png"
                    height: Math.round(35 * scalefactor)
                    width: Math.round(35 * scalefactor)

                    anchors.verticalCenter: parent.verticalCenter // Center vertically

                    // Move the image upwards by adjusting the vertical center offset
                    anchors.verticalCenterOffset: -5
                }

                Label {
                    text: "Do you want to Exit..?"
                    font.pointSize: 15 /*Screen.height * 0.014*/
                    font.family: "Calibri Light"
                    verticalAlignment: Label.AlignVCenter
                }
            }

            Row {
                spacing: 18
                anchors.horizontalCenter: parent.horizontalCenter // Center the row horizontally within the parent
                Button {
                    id: yesButton
                    text: "Yes"
                    width: Math.round(80 * scalefactor)
                    height: Math.round(40 * scalefactor)
                    background: Rectangle {
                        color: "#e5e5e5"
                        border.color: yesButton.hovered ? "skyblue" : "gray"
                        border.width: 2
                        radius: 8
                    }
                    onClicked: {
                        confirmDialog.onAccepted()
                    }
                    focus: true
                }

                Button {
                    id: noButton
                    text: "No"
                    width: Math.round(80 * scalefactor)
                    height: Math.round(40 * scalefactor)
                    background: Rectangle {
                        color: "#e5e5e5"
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
