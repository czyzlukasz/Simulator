import QtQuick 2.0
import QtQuick.Layouts 1.11
import Qt.labs.location 1.0
import QtQuick.Controls 2.15
import QtQuick.Controls.Universal 2.0
import QtQuick.Extras 1.4

Item {

    RowLayout {
        id: rowLayout
        anchors.fill: parent

        GroupBox {
            id: groupBox
            width: 200
            height: 200
            Layout.fillHeight: true
            title: qsTr("Connection")

            GridLayout {
                id: gridLayout1
                anchors.fill: parent
                columns: 2
                transformOrigin: Item.Center

                Label {
                    id: label3
                    text: qsTr("Auto connect")
                    font.pointSize: 12
                }

                Switch {
                    id: switch1
                    width: 51
                    height: 25
                    text: qsTr("")
                    Layout.fillHeight: false
                    Layout.fillWidth: false
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                    display: AbstractButton.TextBesideIcon
                    wheelEnabled: false
                    enabled: true
                }

                Label {
                    id: label1
                    text: qsTr("Connection Status")
                    font.pointSize: 12
                }

                StatusIndicator {
                    id: statusIndicator
                    color: "#00ff00"
                    active: false
                }

                Frame {
                    id: frame
                    width: 200
                    height: 200
                    Layout.fillHeight: true
                    Layout.columnSpan: 2
                    Layout.fillWidth: true
                }



            }
        }

        ColumnLayout {
            id: columnLayout
            width: 100
            height: 100

            TabBar {
                id: tabBar
                anchors.left: stackLayout.left
                anchors.right: stackLayout.right
                anchors.bottom: stackLayout.top
                TabButton {
                    text: "Overview"
                }

                TabButton {
                    text: "Parameters"
                }

                TabButton {
                    text: "Simulation"
                }
            }

            StackLayout {
                id: stackLayout
                width: 100
                height: 100
                currentIndex: tabBar.currentIndex
                Layout.fillHeight: true

                Item {
                }

                Item {
                }

                Item {
                }

            }

            GroupBox {
                id: groupBox1
                width: 200
                height: 200
                Layout.fillHeight: false
                Layout.fillWidth: true
                title: qsTr("Plane Status")

                RowLayout {
                    id: rowLayout1
                    anchors.fill: parent

                    GridLayout {
                        id: gridLayout
                        width: 100
                        height: 100
                        columns: 3
                        columnSpacing: 5

                        Label {
                            id: label
                            text: qsTr("Roll")
                            Layout.columnSpan: 1
                            font.pointSize: 12
                        }

                        Label {
                            id: rollLabel
                            text: qsTr("Label")
                            horizontalAlignment: Text.AlignRight
                            Layout.minimumWidth: 100
                            Layout.columnSpan: 2
                            font.pointSize: 12
                        }

                        Label {
                            id: label2
                            text: qsTr("Pitch")
                            font.pointSize: 12
                        }

                        Label {
                            id: pitchLabel
                            text: qsTr("Label")
                            horizontalAlignment: Text.AlignRight
                            Layout.minimumWidth: 100
                            Layout.columnSpan: 2
                            font.pointSize: 12
                        }

                        Label {
                            id: label4
                            text: qsTr("Yaw")
                            font.pointSize: 12
                        }

                        Label {
                            id: yawLabel
                            text: qsTr("Label")
                            horizontalAlignment: Text.AlignRight
                            Layout.minimumWidth: 100
                            Layout.columnSpan: 2
                            font.pointSize: 12
                        }

                        Label {
                            id: label6
                            text: qsTr("AGL")
                            font.pointSize: 12
                        }

                        Label {
                            id: aglLabel
                            text: qsTr("Label")
                            horizontalAlignment: Text.AlignRight
                            Layout.minimumWidth: 100
                            Layout.columnSpan: 2
                            font.pointSize: 12
                        }

                        Label {
                            id: label8
                            text: qsTr("Speed")
                            font.pointSize: 12
                        }

                        Label {
                            id: speedLabel
                            text: qsTr("Label")
                            horizontalAlignment: Text.AlignRight
                            Layout.minimumWidth: 100
                            Layout.columnSpan: 2
                            font.pointSize: 12
                        }
                    }

                    ToolSeparator {
                        id: toolSeparator
                        Layout.fillHeight: true
                    }

                    Rectangle {
                        id: rectangle
                        width: 250
                        height: 250
                        color: "#ffffff"
                    }

                    Frame {
                        id: frame1
                        width: 200
                        height: 200
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                    }




                }

            }


        }

    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.75;height:720;width:1280}D{i:3}D{i:32}D{i:19}
D{i:1}
}
##^##*/
