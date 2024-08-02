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

    property string logMessages: ""
    signal customLogMessagesChanged(string newLogMessages)

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
        id:mfgPopup1
        height: 300
        width:700
        visible: true
        anchors.centerIn: parent
        onStartClicked: {
            logMessages += "Start button clicked\n"
            root.customLogMessagesChanged(logMessages)
        }
        onStopClicked: {
            logMessages += "Stop button clicked\n"
            root.customLogMessagesChanged(logMessages)
        }
        onExitClicked: {
            handleExit()
            logMessages += "Exit button clicked\n"
            root.customLogMessagesChanged(logMessages)
        }
        onLogsClicked: {
        logViewerComponent.visible=true
        }
    }
    Component.onCompleted: {
        root.closing.connect(onWindowClosing)
        logMessages += "                                                                     MFG Tool Application started\n"
        root.customLogMessagesChanged(logMessages)
    }
    //Handler function for window closing event.
    function onWindowClosing(event) {
        event.accepted = false
        handleExit()
        logMessages += "Main window close button clicked\n"
        root.customLogMessagesChanged(logMessages)
    }

    function handleExit() {
        if (mfgPopup1.progressRunning) {
            warningDialog.open()
        } else {
            confirmDialog.open()
        }
    }
    Dialog {
        id: confirmDialog
        height:140
        width: 300
        modal: true
        closePolicy: Popup.NoAutoClose
        background: Rectangle {
            color: colors.backgroundcolor
            radius: 8
            border.color:colors.backgroundcolor
            border.width: 2
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
                    text: "Do you want to Exit ?"
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
                        border.color: yesButton.hovered ? colors.skyblue : colors.gray
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
                        border.color: noButton.hovered ? colors.skyblue : colors.gray
                        border.width: 2
                        radius: 4
                    }
                    onClicked: {
                        confirmDialog.onRejected()
                        logMessages += "No button clicked\n"
                        root.customLogMessagesChanged(logMessages)
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
    Dialog {
        id: warningDialog
        height: 140
        width: 300
        modal: true
        closePolicy: Popup.NoAutoClose
        background: Rectangle {
            color: colors.backgroundcolor
            radius: 8
            border.color: colors.backgroundcolor
            border.width: 2
        }
        visible: false
        anchors.centerIn: parent
        ColumnLayout {
            spacing: 10
            anchors.fill: parent
            anchors.margins: 15
            Label {
                text: "Please stop the process"
                font.pixelSize: 16
                font.family: "Calibri Light"
                verticalAlignment: Label.AlignVCenter
                horizontalAlignment: Label.AlignHCenter
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredWidth: 250
            }
            Label {
                text: "before exit"
                font.pixelSize: 16
                font.family: "Calibri Light"
                verticalAlignment: Label.AlignVCenter
                horizontalAlignment: Label.AlignHCenter
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredWidth: 250
            }
            Button {
                id: okButton
                text: "OK"
                font.pixelSize: 16
                Layout.preferredWidth: 80
                Layout.preferredHeight: 40
                background: Rectangle {
                    color: colors.bordercolor
                    border.color: okButton.hovered ?colors.skyblue : colors.gray
                    border.width: 2
                    radius: 4
                }
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                onClicked: {
                    warningDialog.onAccepted()
                    logMessages += " Ok button clicked\n"
                    root.customLogMessagesChanged(logMessages)
                }
                focus: true
            }
        }
        onAccepted: {
            warningDialog.visible = false
        }
    }

    ApplicationWindow {
        id: logViewerComponent
        visible: false
        maximumWidth: 700
        maximumHeight: 300
        minimumHeight: 300
        minimumWidth: 700
        title: "Log Viewer"
        x: root.x + root.width + 50
        y: root.y

        Rectangle {
            id: logsrect
            visible: true
            height: parent.height
            width: parent.width
            anchors.centerIn: parent
            color: colors.backgroundcolor

            Flickable {
                id: flickable
                width: logsrect.width
                height: logsrect.height
                clip: true
                contentWidth: logTextArea.width
                contentHeight: logTextArea.height

                TextArea {
                    id: logTextArea
                    width: flickable.width
                    height: logTextArea.paintedHeight
                    readOnly: true
                    text: root.logMessages
                    font.pointSize: 12
                    wrapMode: Text.Wrap
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    anchors.right: parent.right
                }

                Connections {
                    target: root
                    function onCustomLogMessagesChanged(newLogMessages) {
                        logTextArea.text = newLogMessages
                    }
                }

                Component.onCompleted: {
                    logTextArea.text = root.logMessages
                }

                ScrollBar.vertical: ScrollBar {
                    policy: ScrollBar.AsNeeded
                    anchors.right: parent.right
                    width: 12

                    // Customize the ScrollBar style
                    contentItem: Rectangle {
                        implicitWidth: 12
                        color: colors.gray
                    }
                }
            }
        }
    }

}
