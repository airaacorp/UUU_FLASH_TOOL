import QtQuick 2.15
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.15
import USBMonitor 1.0

Popup {
    id:mfgPopup
    closePolicy: Popup.NoAutoClose
    modal: true

    property var connectedDevices: []
    signal startClicked
    signal stopClicked

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
                                                height: 30
                                                width: 100
                                                font.family: "C059"
                                                anchors.verticalCenter: driveText.verticalCenter
                                                readOnly: true
                                            }
                                        }

                                        Rectangle {
                                            id: lableRectangle
                                            Layout.preferredHeight: 40
                                            Layout.fillWidth: true
                                            Layout.alignment: Qt.AlignHCenter
                                            border.width: 1
                                            border.color: "#e5e5e5"
                                            color: "transparent"

                                            Label {
                                                id: statusLabel
                                                text: "  No device is connected"
                                                width: parent.width
                                                anchors.centerIn: parent
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
                                            implicitHeight: 36
                                            Layout.alignment: Qt.AlignHCenter
                                            value: 0.5

                                            contentItem: Rectangle {
                                                border.color: "#e5e5e5"
                                                border.width: 2
                                                clip: true
                                                color: "#f0f0f0"

                                                Rectangle {
                                                    anchors.top: parent.top
                                                    anchors.left: parent.left
                                                    implicitWidth: parent.width * (1 - parent.parent.value)
                                                    implicitHeight: parent.height
                                                    color: "#086ACC"
                                                }
                                            }
                                        }

                                        ProgressBar {
                                            id: progressBar2
                                            implicitWidth: parent.width - 10
                                            implicitHeight: 40
                                            Layout.alignment: Qt.AlignBottom | Qt.AlignHCenter
                                            value: 0.5

                                            contentItem: Rectangle {
                                                border.color: "#e5e5e5"
                                                clip: true
                                                color: "#f0f0f0"
                                                border.width: 2

                                                Rectangle {
                                                    anchors.top: parent.top
                                                    anchors.left: parent.left
                                                    implicitWidth: parent.width * (1 - parent.parent.value)
                                                    implicitHeight: parent.height
                                                    color: "#096ACC"
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
                                text: "Hub 6--Port 3"
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
                                        text: qsTr(" 0 ")
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
                                        text: qsTr(" 0 ")
                                        anchors.top: parent.top
                                        anchors.topMargin: 56
                                        font.family: "Calibri Light"
                                        font.pixelSize: 14
                                        anchors.right: parent.right
                                        anchors.rightMargin: 15
                                    }

                                    Text {
                                        id: faliedopid
                                        text: qsTr("Failed Operations :")
                                        anchors.top: parent.top
                                        anchors.topMargin: 92
                                        font.family: "Calibri Light"
                                        font.pixelSize: 14
                                        anchors.left: parent.left
                                        anchors.leftMargin: 15
                                    }

                                    Text {
                                        id: failednumid
                                        text: qsTr(" 0.0 % ")
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
                                    Layout.topMargin: 5
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
                                            enabled: true
                                            hoverEnabled: true
                                            background: Rectangle {
                                                color: "#e5e5e5"
                                                border.color: startButton.hovered ? "skyblue" : "transparent"
                                                border.width: 2
                                            }
                                            onClicked: {
                                                console.log("Run signal is working...")
                                                if(text==="Start"){
                                                    mfgPopup.startClicked()
                                                    text="Stop"
                                                    console.log("66666666666666stop")
                                                }
                                                else if(text==="Stop"){
                                                    mfgPopup.stopClicked()
                                                    console.log("66666666666666start")
                                                    text="Start"
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
                                                border.color: exitButton.hovered ? "skyblue" : "transparent"
                                                border.width: 2
                                            }
                                            onClicked: {
                                                console.log("Exit signal is working...")
                                                Qt.quit()
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

        function onUsbDeviceConnected(devicePath) {
            console.log("USB device connected: " + devicePath);
            statusLabel.text = "Device connected";

            // Extracting device name from the full path
            var deviceName = devicePath.substring(devicePath.lastIndexOf('/') + 1);

            // Check if the device is HID or ttyUSB and not already in the list
            if ((devicePath.startsWith("/dev/hidraw") || devicePath.startsWith("/dev/ttyUSB")) &&
                !connectedDevices.includes(deviceName)) {
                // Add the new device name to the list
                connectedDevices.push(deviceName);
            }

            // Update the driveTextField with the current list of connected devices
            updateDriveTextField();
        }

        function onUsbDeviceDisconnected(devicePath) {
            console.log("USB device disconnected: " + devicePath);
            statusLabel.text = "Device disconnected";

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
}
