import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    Rectangle {
        id: rectangle
        color: "#2c313c"
        anchors.fill: parent

        BusyIndicator {
            id: busyIndicator
            x: 290
            y: 133
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter

            contentItem: Item {
                    implicitWidth: 64
                    implicitHeight: 64

                    Item {
                        id: itemBI
                        x: parent.width / 2 - 32
                        y: parent.height / 2 - 32
                        width: 64
                        height: 64
                        opacity: busyIndicator.running ? 1 : 0

                        Behavior on opacity {
                            OpacityAnimator {
                                duration: 250
                            }
                        }

                        RotationAnimator {
                            target: itemBI
                            running: busyIndicator.visible && busyIndicator.running
                            from: 0
                            to: 360
                            loops: Animation.Infinite
                            duration: 1250
                        }

                        Repeater {
                            id: repeater
                            model: 6

                            Rectangle {
                                x: itemBI.width / 2 - width / 2
                                y: itemBI.height / 2 - height / 2
                                implicitWidth: 10
                                implicitHeight: 10
                                radius: 5
                                color: "#21be2b"
                                transform: [
                                    Translate {
                                        y: -Math.min(itemBI.width, itemBI.height) * 0.5 + 5
                                    },
                                    Rotation {
                                        angle: index / repeater.count * 360
                                        origin.x: 5
                                        origin.y: 5
                                    }
                                ]
                            }
                        }
                    }
                }
        }
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
