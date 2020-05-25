#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QAbstractListModel>
#include <QHash>
#include <QObject>
#include <QQmlContext>
#include <QTimer>
#include "markerlist.h"

int main(int argc, char ** argv)
{
    QGuiApplication app(argc, argv);

    MarkerList markerList;
    markerList.add(std::make_shared<Marker>("marker 1"));
    auto marker2 = std::make_shared<Marker>("marker 2");
    marker2->setLowBattery(true);
    markerList.add(marker2);
    auto marker3 = std::make_shared<Marker>("marker 3");
    markerList.add(marker3);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    LowBatteryMarkerList lowBatteryMarkerList;
    lowBatteryMarkerList.setSourceModel(qobject_cast<QAbstractItemModel *>(&markerList));

    QQmlApplicationEngine engine;

    QQmlContext *ctxt = engine.rootContext();
    ctxt->setContextProperty("allMarkers", &markerList);
    ctxt->setContextProperty("lowBatteryMarkers", &lowBatteryMarkerList);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    // adding a marker with low battery
    QTimer::singleShot(2000, [&]() {
        auto marker = std::make_shared<Marker>("marker 4");
        marker->setLowBattery(true);
        markerList.add(marker);
    } );

    // modifying an existing marker with low battery
    QTimer::singleShot(3000, [&]() {
        marker3->setLowBattery(true);
        lowBatteryMarkerList.filter();
    } );

    // adding a marker with normal battery
    QTimer::singleShot(4000, [&]() {
        auto marker = std::make_shared<Marker>("marker 5");
        markerList.add(marker);
    } );

    return app.exec();
}
