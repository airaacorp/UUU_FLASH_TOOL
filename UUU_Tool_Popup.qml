import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import USBMonitor 1.0
import Transfer 1.0


Popup {
    id: mfgPopup
    closePolicy: Popup.NoAutoClose
    modal: true

    property var connectedDevices: []
    property bool stoped: false
    signal startClicked
    signal stopClicked

    property real scalefactor: 1.0 // Define scalefactor here


    TransferProgress {
        id: transferProgress

        onTransferStarted: {
            statusLabel.text = "  In Progress  "
        }
        onTransferCompleted: {
            statusLabel.text = "   Done  "
        }

    }

    background: Rectangle {
        color: "green"
        border.color: "skyblue"
        border.width: 1
        radius: 10
    }

    contentItem: Rectangle {
        anchors.fill: parent
        color: "green"

        ColumnLayout {
            anchors.fill: parent
            spacing: 0

            Rectangle {
                id: bottomRectangle
                Layout.fillHeight: true
                Layout.fillWidth: true
                color: "#f0f0f0"

                RowLayout {
                    anchors.fill: parent
                    spacing: 0

                    Rectangle {
                        id: unAssignedRectangle
                        Layout.preferredWidth: parent.width / 2
                        Layout.fillHeight: true
                        color: "transparent"

                        Rectangle {
                            id: unAssignedInnerRectangle
                            height: parent.height - 8
                            width: parent.width - 8
                            color: "transparent"
                            anchors {
                                bottom: parent.bottom
                                horizontalCenter: parent.horizontalCenter
                            }
                            border.color: "#e5e5e5"
                            border.width: 1.5
                            radius: 6

                            ColumnLayout {
                                anchors.fill: parent

                                Rectangle {
                                    id: drivesAndConnectionId
                                    color: "transparent"
                                    height: 100
                                    width: parent.width - 4
                                    Layout.alignment: Qt.AlignHCenter

                                    ColumnLayout {
                                        anchors.fill: parent

                                        Row {
                                            Layout.alignment: Qt.AlignTop
                                            Layout.topMargin: 30

                                            Text {
                                                id: driveText
                                                text: qsTr("Drive(s):  ")
                                                font.family: "Calibri Light"
                                                leftPadding: 5
                                            }

                                            TextField {
                                                id: driveTextField
                                                height: 35
                                                width: 80
                                                font.family: "C059"
                                                anchors.verticalCenter: driveText.verticalCenter
                                                readOnly: true
                                            }
                                        }

                                        Rectangle {
                                            id: lableRectangle
                                            Layout.preferredHeight: 40
                                            Layout.preferredWidth: parent.width-6
                                            Layout.alignment: Qt.AlignHCenter |Qt.AlignTop
                                            Layout.topMargin: 25
                                            border.width: 1.5
                                            border.color: "#c0c0c0"
                                            color: "transparent"
                                            radius: 4
                                            Rectangle{
                                                width: parent.width
                                                height: 2
                                                color: "gray"
                                                radius: 10
                                            }

                                            Label {
                                                id: statusLabel
                                                text: "  No device is connected"
                                                width: parent.width
                                                anchors.centerIn: parent
                                                anchors.left: parent.left
                                                anchors.leftMargin: 10

                                                font.family: "Calibri Light"
                                                background: Rectangle {
                                                    color: "transparent"
                                                }
                                            }
                                        }
                                    }
                                }

                                Rectangle {
                                    id: pragressBarRect
                                    Layout.preferredHeight: 100
                                    Layout.preferredWidth: parent.width - 4
                                    Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
                                    Layout.bottomMargin: 25
                                    color: "transparent"

                                    ColumnLayout {
                                        anchors.fill: parent

                                        ProgressBar {
                                            id: progressBar
                                            implicitWidth: parent.width - 10
                                            implicitHeight: 32
                                            Layout.alignment: Qt.AlignHCenter
                                            // Do not allow the user to start and show progressbar1 also without connecting the device min 1 device.
                                            value: transferProgress.progress && connectedDevices.length > 0 ? transferProgress.progress : 0

                                            contentItem: Rectangle {
                                                border.color: "#e5e5e5"
                                                border.width: 2
                                                clip: true
                                                color: "#f0f0f0"

                                                Rectangle {
                                                    id:p1id
                                                    anchors.top: parent.top
                                                    anchors.left: parent.left

                                                    implicitWidth: parent.width * parent.parent.value
                                                    implicitHeight: parent.height
                                                    color: (mfgPopup.stoped===true)?"red":(progressBar.value===1)?"green":"#096ACC"
                                                }
                                            }
                                        }

                                        ProgressBar {
                                            id: progressBar2
                                            implicitWidth: parent.width - 10
                                            implicitHeight: 43
                                            Layout.alignment: Qt.AlignBottom | Qt.AlignHCenter
                                             // Do not allow the user to start and show progressbar2 also without connecting the device min 1 device
                                            value: transferProgress.overallProgress && connectedDevices.length > 0 ? transferProgress.overallProgress : 0
                                            contentItem: Rectangle {
                                                border.color: "#e5e5e5"
                                                clip: true
                                                color: "#f0f0f0"
                                                border.width: 2

                                                Rectangle {
                                                    id:singleFileprogressId
                                                    anchors.top: parent.top
                                                    anchors.left: parent.left
                                                    implicitWidth: parent.width * parent.parent.value
                                                    implicitHeight: parent.height
                                                    color: (mfgPopup.stoped===true)?"red":(parent.width === implicitWidth) ? "green":"#096ACC"
                                                }
                                            }
                                        }

                                    }
                                }
                            }
                        }

                        Label {
                            id: labelId
                            Text {
                                id:portNo
                                text: "Unassigned"
                                color: "#7d9ae4"
                                height: 16
                                font.family: "Calibri Light"
                                font.pixelSize: 16
                            }
                            background: Rectangle {
                                color: "#f0f0f0"
                            }
                            anchors {
                                left: parent.left
                                leftMargin: 12
                                top: parent.top
                                topMargin: 1
                            }
                        }
                    }

                    Rectangle {
                        id: statusInformationRect
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        color: "transparent"

                        Rectangle {
                            id: statusInformationRectRectangle
                            height: parent.height - 2
                            width: parent.width - 6
                            color: "transparent"

                            ColumnLayout {
                                id: txtids
                                anchors.fill: parent
                                spacing: 10

                                Rectangle {
                                    id: statusinid
                                    Layout.preferredHeight: 120
                                    Layout.preferredWidth: parent.width
                                    Layout.alignment: Qt.TopEdge
                                    Layout.topMargin: 8
                                    color: "transparent"
                                    border.color: "#e5e5e5"
                                    border.width: 2
                                    radius: 6

                                    Text {
                                        id: sucessopid
                                        text: qsTr("Successful Operations :")
                                        anchors.top: parent.top
                                        anchors.topMargin: 25
                                        font.family: "Calibri Light"
                                        font.pixelSize: 14
                                        anchors.left: parent.left
                                        anchors.leftMargin: 15
                                    }

                                    Text {
                                        id: susscessnumid
                                        text: transferProgress.success
                                        anchors.top: parent.top
                                        anchors.topMargin: 25
                                        font.family: "Calibri Light"
                                        font.pixelSize: 14
                                        anchors.right: parent.right
                                        anchors.rightMargin: 15
                                    }

                                    Text {
                                        id: failureopid
                                        text: qsTr("Failed Operations :")
                                        anchors.top: parent.top
                                        anchors.topMargin: 56
                                        font.family: "Calibri Light"
                                        font.pixelSize: 14
                                        anchors.left: parent.left
                                        anchors.leftMargin: 15
                                    }

                                    Text {
                                        id: failurenumid
                                        text: transferProgress.fail
                                        anchors.top: parent.top
                                        anchors.topMargin: 56
                                        font.family: "Calibri Light"
                                        font.pixelSize: 14
                                        anchors.right: parent.right
                                        anchors.rightMargin: 15
                                    }

                                    Text {
                                        id: faliedopid
                                        text: qsTr("Failure Rate :")
                                        anchors.top: parent.top
                                        anchors.topMargin: 92
                                        font.family: "Calibri Light"
                                        font.pixelSize: 14
                                        anchors.left: parent.left
                                        anchors.leftMargin: 15
                                    }

                                    Text {
                                        id: failednumid
                                        text:"0.0%"
                                        anchors.top: parent.top
                                        anchors.topMargin: 92
                                        font.family: "Calibri Light"
                                        font.pixelSize: 14
                                        anchors.right: parent.right
                                        anchors.rightMargin: 13
                                    }
                                }

                                Rectangle {
                                    id: buttonid
                                    Layout.preferredHeight: 150
                                    Layout.preferredWidth: parent.width
                                    Layout.alignment: Qt.TopEdge
                                    Layout.topMargin: 35
                                    color: "transparent"

                                    RowLayout {
                                        anchors.left: parent.left
                                        anchors.leftMargin: 50
                                        spacing: 60

                                        Button {
                                            id: startButton
                                            Layout.preferredWidth: 100
                                            Layout.preferredHeight: 80
                                            text: "Start"
                                            font.family: "Calibri Light"
                                            font.pixelSize: 14
                                            //Without connecting the target device this wont allow to start minimum 1 device Connection should required.
                                            enabled: connectedDevices.length > 0 && transferProgress.overallProgress < 1.0
                                            hoverEnabled: true
                                            background: Rectangle {
                                                color: "#e5e5e5"
                                                border.color: startButton.hovered ? "skyblue" : "gray"
                                                border.width: 2
                                                radius: 8
                                            }
                                            onClicked: {
                                                transferProgress.startTransfer()
                                                if (text === "Start") {
                                                    mfgPopup.startClicked()
                                                    mfgPopup.stoped=false
                                                    text = "Stop"
                                                } else if (text === "Stop") {
                                                    transferProgress.stopTransfer()
                                                    mfgPopup.stopClicked()
                                                    mfgPopup.stoped=true
                                                    text = "Start"
                                                }
                                            }
                                        }

                                        Button {
                                            id: exitButton
                                            Layout.preferredWidth: 100
                                            Layout.preferredHeight: 80
                                            text: "Exit"
                                            font.pixelSize: 14
                                            font.family: "Calibri Light"
                                            enabled: true
                                            background: Rectangle {
                                                color: "#e5e5e5"
                                                border.color: exitButton.hovered ? "skyblue" : "gray"
                                                border.width: 2
                                                radius: 8
                                            }
                                            onClicked: {
                                                console.log("Exit signal is working...")
                                                // Qt.quit()
                                                confirmDialog.open();

                                            }
                                        }
                                    }
                                }
                            }
                        }

                        Label {
                            id: statustext
                            height: 16
                            Text {
                                text: qsTr("Status Information")
                                font.family: "Calibri Light"
                                color: "#7d9ae4"
                                font.pixelSize: 16
                            }
                            background: Rectangle {
                                color: "#f0f0f0"
                            }
                            anchors.top: parent.top
                            anchors.topMargin: 1
                            anchors.left: parent.left
                            anchors.leftMargin: 10
                        }
                    }
                }
            }
        }
    }

    USBMonitor {
        id: usbMonitor
    }

    Connections {
        target: usbMonitor
        function onUsbPortConnected(portDetails,portNumber,hubNumber) {
            console.log("USB port connected: " +portDetails);
            portNo.text = "Hub "+hubNumber+"--Port "+ portNumber;
        }
        function onUsbPortDisconnected(portDetails,portNumber,hubNumber) {
            console.log("USB port disconnected: " +portDetails);
            portNo.text = " Unassigned";
        }
        function onUsbDeviceConnected(devicePath) {
            console.log("USB device connected: " + devicePath);
            statusLabel.text = "  Device connected";

            // Extracting device name from the full path
            var deviceName = devicePath.substring(devicePath.lastIndexOf('/') + 1);

            // Clear the connectedDevices list and add the new device
            connectedDevices = [deviceName];

            // Update the driveTextField with the current list of connected devices
            updateDriveTextField();
        }

        function onUsbDeviceDisconnected(devicePath) {
            console.log("USB device disconnected: " + devicePath);
            statusLabel.text = "  Device disconnected";

            // Extracting device name from the full path
            var deviceName = devicePath.substring(devicePath.lastIndexOf('/') + 1);

            // Remove the disconnected device name from the list
            connectedDevices = connectedDevices.filter(function(name) {
                return name !== deviceName;
            });

            // Update the driveTextField with the current list of connected devices
            updateDriveTextField();
        }

        function updateDriveTextField() {
            // Clear the text field
            driveTextField.text = "";

            // Update the driveTextField with the current list of connected devices
            for (var i = 0; i < connectedDevices.length; i++) {
                driveTextField.text += connectedDevices[i] + "\n";
            }
        }
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
