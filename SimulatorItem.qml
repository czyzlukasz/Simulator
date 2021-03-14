import QtQuick 2.0
import Qt3D.Core 2.14
import Qt3D.Extras 2.15
import Qt3D.Logic 2.0
import QtQuick3D 1.15
import QtQuick.Layouts 1.11
import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt3D.Render 2.15
import com.SimulatorInterface 1.0


Item {

    SimulatorInterface {
        id: simulatorInterface

        onCreateComponent: {
            let instance = itemSpawner.addComponent(componentUrl)
            saveComponent(instance, componentName)
        }
    }

    GridLayout {
        id: gridLayout
        anchors.fill: parent

        View3D {
            id: view3D
            width: 400
            height: 400
            Layout.minimumHeight: 400
            Layout.minimumWidth: 400
            SceneEnvironment {
                id: sceneEnvironment
                antialiasingQuality: SceneEnvironment.High
                antialiasingMode: SceneEnvironment.MSAA
            }

            Node {
                id: scene
                DirectionalLight {
                    worldDirection: Qt.vector3d(0.3, -3.0, 0.0).normalized();
                    color: "#fbf9ce"
                    intensity: 0.3
                }

                PerspectiveCamera {
                    id: perspectiveCamera
                    objectName: "camera"
                    z: 350
                    pivot: Qt.vector3d(0, 0, 0)

                    function rotateCamera(panAngle, tiltAngle){
                        var oldPosition = perspectiveCamera.position
                        // Convert angles to find comfortable rotation speeds
                        var deltaTiltAngle = -tiltAngle * 0.25
                        var deltaPanAngle = -panAngle * 0.25
                        var tiltAxis = perspectiveCamera.forward.crossProduct(Qt.vector3d(0, 1, 0))
                        var panAxis = Qt.vector3d(0, 1, 0)

                        var matrix = Qt.matrix4x4()
                        matrix.rotate(deltaTiltAngle, tiltAxis)
                        matrix.rotate(deltaPanAngle, panAxis)
                        var newPosition = matrix.times(oldPosition)

                        perspectiveCamera.position = newPosition
                        perspectiveCamera.lookAt(Qt.vector3d(0, 0, 0))
                    }

                    function zoom(delta){
                        var factor = delta < 0 ? 1.05 : 0.95
                        perspectiveCamera.position = perspectiveCamera.position.times(factor)
                    }
                }

                //                Model {
                //                    id: aileronModel
                //                    source: "asset_imports/Quick3DAssets/Aileron/meshes/body1.mesh"
                //                    materials: PrincipledMaterial{
                //                        baseColor: "red"
                //                    }
                //                }

                Node {
                    id: itemSpawner
                    property var instances: []

                    function addComponent(componentUrl) {
                        var newComponent = Qt.createComponent(componentUrl)
                        let newObject = newComponent.createObject(itemSpawner)

                        instances.push(newObject)

                        return instances[instances.length - 1]
                    }
                }
            }

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                property var previousMouxeX: -1
                property var previousMouxeY: -1

                onPositionChanged: {
                    if(previousMouxeX !== -1 && previousMouxeY !== -1){
                        var mouseDeltaX = mouseX - previousMouxeX
                        var mouseDeltaY = mouseY - previousMouxeY

                        perspectiveCamera.rotateCamera(mouseDeltaX, mouseDeltaY)
                    }
                    previousMouxeX = mouseX
                    previousMouxeY = mouseY
                }

                onPressed: {
                    previousMouxeX = mouseX
                    previousMouxeY = mouseY
                }

                onWheel: {
                    perspectiveCamera.zoom(wheel.angleDelta.y)
                }
            }
        }

        Label {
            id: label
            color: "blue"
            text: "TESTS"
        }

        Button {
            id: button
            text: qsTr("Button")
            onClicked: {
                simulatorInterface.startAddingComponents()
            }
        }

        Button {
            id: button1
            text: qsTr("Button")
            onClicked: {
                simulatorInterface.testing()
            }
        }
    }


}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
