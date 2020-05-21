import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Row {

        ListView {
            width: 200; height: 250
            model: allMarkers
            delegate: Text { text: "Marker: " + name + ", " + lowBattery }
        }

        ListView {
            width: 200; height: 250
            model: lowBatteryMarkers
            delegate: Text { text: "Marker: " + name + ", " + lowBattery }
        }
    }
}
