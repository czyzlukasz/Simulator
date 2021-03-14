#ifndef SIMULATORINTERFACE_HPP
#define SIMULATORINTERFACE_HPP

#include <QObject>
#include <QDebug>
#include <QVector3D>
#include <QQuaternion>
#include <QUrl>


enum class AirplaneItemtype{
    WING,
    AILERON
};


struct AirplaneItem {
    QObject* componentInstance;
    QString name;
    AirplaneItemtype itemType;

    bool operator ==(const AirplaneItem& other) const{
        return name == other.name;
    }
};


class SimulatorInterface : public QObject
{
    Q_OBJECT

public:
    explicit SimulatorInterface(QObject *parent = nullptr);
    SimulatorInterface& addComponent(AirplaneItemtype itemType, const std::string& name);
    void setItemPosition(const std::string& name, const QVector3D& position);
    void setItemRotation(const std::string& name, const QQuaternion& rotation);

signals:
    // Notify QML that specified component needs to be created
    void createComponent(const QString& componentName, const QUrl& componentUrl);

public slots:
    // Save pointer to componed returned from QML
    void saveComponent(QObject* component, const QString& componentName);
    // Notify interface that QML is ready for components
    void startAddingComponents();
    void testing();

private:
    std::optional<std::reference_wrapper<AirplaneItem>> getItem(const QString& name);
    std::vector<AirplaneItem> airplaneItems;
    static const inline std::map<AirplaneItemtype, QUrl> typeToUrlMap = {
        {AirplaneItemtype::AILERON, QUrl("asset_imports/Quick3DAssets/Aileron/Aileron.qml")},
        {AirplaneItemtype::WING, QUrl("asset_imports/Quick3DAssets/Wing/Wing.qml")},
    };
};

#endif // SIMULATORINTERFACE_HPP
