import QtQuick 2.15
import QtQuick.Controls 2.15

CheckDelegate {
    id: control
    text: qsTr("CheckDelegate")

    property int widthTextField: 50
    property int heightTextField: 26
    property int radiusTextField: 4

    contentItem: Text {
        rightPadding: control.spacing
        leftPadding: control.indicator.width
        text: control.text
        font: control.font
        opacity: enabled ? 1.0 : 0.3
        color: control.down ? "#2c313c" : "#ffffff"
        elide: Text.ElideRight
        verticalAlignment: Text.AlignVCenter
    }

    indicator: Rectangle {
        implicitWidth: 26
        implicitHeight: 26
        x: 0 // control.width - width - control.rightPadding
        y: control.topPadding + control.availableHeight / 2 - height / 2
        radius: 3
        color: "transparent"
        border.color: control.down ? "#2c313c" : "#ffffff"

        Rectangle {
            width: 14
            height: 14
            x: 6
            y: 6
            radius: 2
            color: control.down ? "#2c313c" : "#ffffff"
            visible: control.checked
        }
    }

    background: Rectangle {
        implicitWidth: 100
        implicitHeight: 40
        visible: control.down || control.highlighted
        color: control.down ? "#bdbebf" : "#eeeeee"
    }
}
