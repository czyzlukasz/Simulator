import QtQuick 2.15
import QtQuick.Window 2.15
import QtCharts 2.3
import QtQuick.Controls 2.15
import QtQuick.Dialogs.qml 1.0
import QtQuick.Extras 1.4
import QtQuick.Layouts 1.11
import QtQuick3D 1.15

Window {
    width: 1280
    height: 720
    visible: true
    color: "#2f2f2f"
    title: qsTr("Hello World")

    GridLayout {
        id: gridLayout
        anchors.fill: parent
        rows: 4
        columns: 4

        GroupBox {
            id: groupBox
            width: 200
            height: 200
            Layout.minimumWidth: 200
            Layout.fillHeight: true
            Layout.rowSpan: 3
            title: qsTr("")

            GridLayout {
                id: gridLayout1
                anchors.fill: parent
            }
        }

        TabBar {
            id: tabBar
            anchors.left: stackLayout.left
            anchors.right: stackLayout.right
            anchors.bottom: stackLayout.top
            Layout.columnSpan: 3

            TabButton {
                text: "Tab 0"
            }

            TabButton {
                text: "Tab 1"
            }

            TabButton {
                text: "Simulation"
            }
        }


        StackLayout {
            id: stackLayout
            width: 100
            height: 100
            Layout.rowSpan: 2
            currentIndex: tabBar.currentIndex
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.columnSpan: 3

            Item {
            }

            Item {
            }

            Item {
                SimulatorItem {
                    id: simulatorItem
                }
            }
        }

        GroupBox {
            id: groupBox1
            width: 200
            height: 200
            Layout.maximumHeight: 65535
            Layout.minimumHeight: 0
            Layout.fillWidth: true
            Layout.columnSpan: 4
            title: qsTr("")

            RowLayout {
                id: rowLayout
                anchors.fill: parent


                ChartView {
                    id: line
                    width: 300
                    height: 300
                    Layout.fillWidth: true
                    Layout.minimumHeight: 200
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
                    id: line1
                    width: 300
                    height: 300
                    Layout.fillWidth: true
                    Layout.minimumHeight: 200
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

                Rectangle {
                    id: rectangle
                    width: 200
                    height: 200
                    color: "#ffffff"
                }

                ChartView {
                    id: percent
                    width: 300
                    height: 300
                    Layout.fillWidth: true
                    Layout.minimumHeight: 200
                    Layout.maximumHeight: 200
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
    D{i:0;formeditorZoom:0.75;height:720;width:1280}
}
##^##*/
