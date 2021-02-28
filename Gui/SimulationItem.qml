import QtQuick 2.12
import Gui 1.0
import QtQuick.Controls 2.15
import QtQuick3D 1.15
import QtQuick 2.15

import "asset_imports/Quick3DAssets/Wing_v1"
import "asset_imports/Quick3DAssets/Aileron_v1"
import QtQuick3D.Helpers 1.15
//import QtQuick.Extras 1.4
import QtQuick.Layouts 1.11

Item {
    id: item1

    GridLayout {
        id: gridLayout
        anchors.fill: parent
        rows: 4
        columns: 2

        View3D {
            id: view3D
            width: 400
            height: 400

            PerspectiveCamera {
                id: camera
                z: 300
                Component.onCompleted: {
                    camera.lookAt(Qt.vector3d(0, 0, 0));
                }
            }

            DirectionalLight {
                eulerRotation.x: -45
                position.z: -1000
                brightness: 150
                castsShadow: true
            }

            AxisHelper {
                enableAxisLines: true
            }

            Model {
                visible: false
                source: "asset_imports/Quick3DAssets/Aileron_v1/meshes/body1.mesh"
                materials: PrincipledMaterial{
                    baseColor: "red"
                }
                eulerRotation.x: slider.value
                eulerRotation.y: slider1.value
                eulerRotation.z: slider2.value
            }

            Node {
                id: itemSpawner
                property var instances: []

                function addItem(type, position, rotation){
                    let shape;
                    let additionalRotation = Qt.vector3d(0, 0, 0); // Rotation used for aligning model with true "forward"
                    switch(type){
                    case "Aileron":
                        shape = Qt.createComponent("asset_imports/Quick3DAssets/Aileron_v1/Aileron_v1.qml");
                        additionalRotation = Qt.vector3d(0, 90, 0);
                        break;
                    case "Wing":
                        shape = Qt.createComponent("asset_imports/Quick3DAssets/Wing_v1/Wing_v1.qml");
                        additionalRotation = Qt.vector3d(0, 0, 0);
                        break;
                    }

                    let instance = shape.createObject(itemSpawner, {position: position, eulerRotation: rotation.plus(additionalRotation)});
                    instances.push(instance);

                    return instances.indexOf(instance);
                }

                function getItem(index){
                    return instances[index];
                }
            }

            Component.onCompleted: {
                for(var i = 0; i < 5; ++i)
                    itemSpawner.addItem("Aileron", Qt.vector3d(i, i, i * 20), Qt.vector3d(0, 0, 0));
            }

            MouseArea {
                property int previousMouseX: -1;
                property int previousMouseY: -1;
                anchors.fill: parent
                onWheel: {
                    if(wheel.angleDelta.y > 0)
                    {
                        camera.position.x *= 0.95;
                        camera.position.y *= 0.95;
                        camera.position.z *= 0.95;
                    }
                    else
                    {
                        camera.position.x *= 1.05;
                        camera.position.y *= 1.05;
                        camera.position.z *= 1.05;
                    }
                }

                onPositionChanged: {
                    if(previousMouseX != -1 && previousMouseY != -1)
                    {
                        let xDelta = (mouse.x - previousMouseX) * -0.25;
                        let yDelta = (mouse.y - previousMouseY) * -0.25;

                        let sinP = Math.sin(xDelta * Math.PI / 180);
                        let cosP = Math.cos(xDelta * Math.PI / 180);
                        let sinY = Math.sin(yDelta * Math.PI / 180);
                        let cosY = Math.cos(yDelta * Math.PI / 180);
                        let matrix = Qt.matrix4x4(cosP, sinP * sinY, sinP * cosY, 0,
                                                  0, cosY, -sinY, 0,
                                                  -sinP, 0, cosP * cosY, 0,
                                                  0, 0, 0, 0);
                        // TODO: fix rotation
                        let distance = camera.position.length();
                        let newPosition = matrix.times(camera.position.toVector4d()).normalized().times(distance);
                        camera.position = newPosition.toVector3d();
                        camera.lookAt(Qt.vector3d(0, 0, 0));
                    }

                    previousMouseX = mouse.x;
                    previousMouseY = mouse.y;
                }

                onReleased: {
                    previousMouseX = -1;
                    previousMouseY = -1;
                }
            }
        }

        Slider {
            id: slider
            to: 180
            from: -180
            value: 0.5
        }

        Slider {
            id: slider1
            to: 180
            from: -180
            value: 0.5
        }

        Slider {
            id: slider2
            to: 180
            from: -180
            value: 0.5
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
