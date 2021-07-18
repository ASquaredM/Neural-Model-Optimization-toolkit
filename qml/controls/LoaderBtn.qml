import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15

Button{
    id: loaderBtn
    text: qsTr("Load Model")

    // CUSTOM PROPERTIES
    property color btnColorDefault: "#4287f5"
    property color btnColorMouseOver: "#2472f0"
    property color btnColorClicked: "#95b7f0"

    QtObject{
        id: internal

        // MOUSE OVER AND CLICK CHANGE COLOR
        property var dynamicColor: if(loaderBtn.down){
                                        loaderBtn.down ? btnColorClicked : btnColorDefault
                                    } else {
                                        loaderBtn.hovered ? btnColorMouseOver : btnColorDefault
                                    }

    }

    implicitWidth: 206
    implicitHeight: 40

    background: Rectangle{
        id: bgBtn
        color: internal.dynamicColor
        radius: 20
    }

    contentItem: Item{
        id:textItem
        Text{
            id: textBtn
            text: loaderBtn.text
            anchors.verticalCenter: parent.verticalCenter
            font.pointSize: 15
            anchors.horizontalCenter: parent.horizontalCenter
            color: "#ffffff"
        }
    }
}
