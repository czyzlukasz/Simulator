import QtQuick 2.12
import Gui 1.0
import QtCharts 2.3
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.15

Rectangle {
    width: Constants.width
    height: Constants.height

    color: Constants.backgroundColor

    GridLayout {
        id: gridLayout
        anchors.fill: parent
        rows: 3
        columns: 2

        GroupBox {
            id: groupBox1
            width: 200
            height: 200
            Layout.fillHeight: true
            Layout.rowSpan: 2
            title: qsTr("")

            ColumnLayout {
                id: columnLayout
                anchors.fill: parent

                Switch {
                    id: switch1
                    text: qsTr("Switch")
                }

                Switch {
                    id: switch2
                    text: qsTr("Switch")
                }

                Switch {
                    id: switch3
                    text: qsTr("Switch")
                }
            }

        }

        TabBar {
            id: tabBar
            height: 46
            anchors.left: stackLayout.left
            anchors.right: stackLayout.right
            anchors.bottom: stackLayout.top
            clip: false
            Layout.fillHeight: false
            wheelEnabled: false
            currentIndex: 0
            contentHeight: 38
            Layout.fillWidth: true
            TabButton {
                text: "Overview"
            }

            TabButton {
                text: "Parameters"
            }

            TabButton {
                text: "Simulation"
            }

            TabButton {
                text: "Log"
            }
        }

        StackLayout {
            id: stackLayout
            width: 100
            height: 100
            currentIndex: 2
            Layout.fillHeight: true

            Item {
            }

            Item {
            }

            Item {
                SimulationItem {
                    id: simulationItem
                    x: 0
                    y: 0
                    anchors.fill: parent
                }
            }

            Item {
            }
        }

        GroupBox {
            id: groupBox
            width: 200
            height: 200
            Layout.columnSpan: 2
            Layout.fillHeight: false
            Layout.fillWidth: true
            title: qsTr("")

            RowLayout {
                id: rowLayout
                anchors.fill: parent

                Pane {
                    id: pane
                    width: 200
                    height: 200
                    Layout.minimumHeight: 200
                    Layout.minimumWidth: 200
                }

                ChartView {
                    id: line
                    width: 300
                    height: 200
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    localizeNumbers: false
                    Layout.minimumWidth: 0
                    Layout.maximumHeight: 200
                    LineSeries {
                        name: "LineSeries"
                        XYPoint {
                            x: 0
                            y: 2
                        }

                        XYPoint {
                            x: 1
                            y: 1.2
                        }

                        XYPoint {
                            x: 2
                            y: 3.3
                        }

                        XYPoint {
                            x: 5
                            y: 2.1
                        }
                    }
                }

                ChartView {
                    id: spline
                    width: 300
                    height: 300
                    Layout.fillWidth: true
                    transformOrigin: Item.Center
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.minimumWidth: 0
                    Layout.maximumHeight: 200
                    SplineSeries {
                        name: "SplineSeries"
                        XYPoint {
                            x: 0
                            y: 1
                        }

                        XYPoint {
                            x: 3
                            y: 4.3
                        }

                        XYPoint {
                            x: 5
                            y: 3.1
                        }

                        XYPoint {
                            x: 8
                            y: 5.8
                        }
                    }
                }

                ChartView {
                    id: percent
                    width: 300
                    height: 300
                    Layout.fillWidth: true
                    Layout.maximumHeight: 200
                    Layout.minimumWidth: 0
                    PercentBarSeries {
                        name: "PercentBarSeries"
                        BarSet {
                            values: [2, 2, 3]
                            label: "Set1"
                        }

                        BarSet {
                            values: [5, 1, 2]
                            label: "Set2"
                        }

                        BarSet {
                            values: [3, 5, 8]
                            label: "Set3"
                        }
                    }
                }
            }
        }

    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
