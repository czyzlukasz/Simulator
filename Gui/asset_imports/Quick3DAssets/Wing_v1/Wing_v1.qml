import QtQuick 2.15
import QtQuick3D 1.15

Node {
    id: wing_v1_obj

    Model {
        id: body1
        source: "meshes/body1.mesh"

        DefaultMaterial {
            id: steel___Satin_material
            diffuseColor: "#ff999999"
        }
        materials: [
            steel___Satin_material
        ]
    }
}
