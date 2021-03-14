#include "SimulatorInterface.hpp"
#include <QMessageLogger>

SimulatorInterface::SimulatorInterface(QObject *parent) : QObject(parent)
{

}

SimulatorInterface& SimulatorInterface::addComponent(AirplaneItemtype itemType, const std::string& name){
    if(getItem(QString::fromStdString(name))){
        QMessageLogger().warning() << "Item " << QString::fromStdString(name) << " already exists!";
        return *this;
    }

    AirplaneItem& newItem = airplaneItems.emplace_back(AirplaneItem{.name = QString::fromStdString(name), .itemType = itemType});
    if(const auto it = typeToUrlMap.find(itemType); it != typeToUrlMap.cend()){
        emit createComponent(newItem.name, it->second);
    }
    else{
        QMessageLogger().warning() << "Item type" << static_cast<int>(itemType) << " does not exist in typeToUrlMap!";
    }

    return *this;
}

void SimulatorInterface::setItemPosition(const std::string& name, const QVector3D& position){
    if(const auto newItem = getItem(QString::fromStdString(name))){
        QObject* instance = newItem->get().componentInstance;
        instance->setProperty("position", position);
    }
    else{
        QMessageLogger().warning() << "Can't set position of item " << QString::fromStdString(name) << ", because it wasn't found";
    }
}

void SimulatorInterface::setItemRotation(const std::string& name, const QQuaternion& rotation){
    if(const auto newItem = getItem(QString::fromStdString(name))){
        QObject* instance = newItem->get().componentInstance;
        instance->setProperty("rotation", rotation);
    }
    else{
        QMessageLogger().warning() << "Can't set rotation of item " << QString::fromStdString(name) << ", because it wasn't found";
    }
}

void SimulatorInterface::saveComponent(QObject* component, const QString& componentName){
    if(const auto newItemOptional = getItem(componentName)){
        AirplaneItem& newItem = newItemOptional->get();
        newItem.componentInstance = component;
    }
    else{
        QMessageLogger().warning() << "Tried to save component " << componentName << ", but it does not exist in airplaneItems!";
    }
}

void SimulatorInterface::startAddingComponents(){
    addComponent(AirplaneItemtype::AILERON, "Aileron");
    addComponent(AirplaneItemtype::WING, "Wing");
}

void SimulatorInterface::testing(){
    setItemPosition("Wing", {20, 20, 20});
    getItem("Wing").value().get().componentInstance->setProperty("eulerRotation", QVector3D(10, 20, 30));
}

std::optional<std::reference_wrapper<AirplaneItem>> SimulatorInterface::getItem(const QString& name){
    if(auto it = std::find(airplaneItems.begin(), airplaneItems.end(), AirplaneItem{.name = name}); it != airplaneItems.end()){
        return std::reference_wrapper<AirplaneItem>(*it);
    }

    return std::nullopt;
}
