import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs 1.3
import "../controls"

Item {
    Rectangle {
        id: rectangle
        color: "#2c313c"
        anchors.fill: parent


        Rectangle {
            id: rectangleFore
            width: 350
            height: 201
            color: "#242936"
            anchors.top: label.bottom
            anchors.topMargin: 15
            anchors.horizontalCenter: parent.horizontalCenter
            clip: true

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 5
                anchors.rightMargin: 15
                anchors.leftMargin: 15
                width: rectangleFore.width - 10

                RowLayout {
                    id: row1
                    Layout.fillWidth: true

                    Label {
                        id: label1
                        color: "#f6f7f7"
                        text: qsTr("Random Seed:")
                        verticalAlignment: Text.AlignVCenter
                    }

                    TextField {
                        id: randSeed
                        Layout.minimumWidth: 30
                        Layout.maximumWidth: 55
                        Layout.maximumHeight: 26
                        Layout.alignment: Qt.AlignRight

                        text: qsTr("1")
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        validator: IntValidator {
                            bottom: 0
                            top: 999
                        }
                    }
                }

                RowLayout {
                    id: row2
                    Layout.fillWidth: true

                    Label {
                        id: label2
                        color: "#f6f7f7"
                        text: qsTr("Population Size:")
                        verticalAlignment: Text.AlignVCenter
                    }

                    TextField {
                        id: stimPosition
                        Layout.maximumWidth: 55
                        Layout.maximumHeight: 26
                        Layout.alignment: Qt.AlignRight

                        text: qsTr("2")
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        validator: IntValidator {
                            bottom: 0
                            top: 999
                        }
                    }
                }

                RowLayout {
                    id: row3
                    Layout.fillWidth: true

                    Label {
                        id: label3
                        color: "#f6f7f7"
                        text: qsTr("Number of Generations:")
                        verticalAlignment: Text.AlignVCenter
                    }

                    TextField {
                        id: numGenerations
                        Layout.maximumHeight: 26
                        Layout.maximumWidth: 55
                        Layout.alignment: Qt.AlignRight

                        text: qsTr("10")
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        selectByMouse: true
                        validator: IntValidator {
                            bottom: 0
                            top: 999
                        }
                    }
                }

                RowLayout {
                    id: row4
                    Layout.fillWidth: true

                    Label {
                        id: label4
                        color: "#f6f7f7"
                        text: qsTr("Offspring Size:")
                        verticalAlignment: Text.AlignVCenter
                    }

                    TextField {
                        id: offSpringSize
                        Layout.maximumHeight: 26
                        Layout.maximumWidth: 55
                        Layout.alignment: Qt.AlignRight

                        text: qsTr("2")
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        selectByMouse: true
                        validator: IntValidator {
                            bottom: 0
                            top: 999
                        }
                    }
                }

                RowLayout {
                    id: row5
                    Layout.fillWidth: true

                    Label {
                        id: label5
                        color: "#f6f7f7"
                        text: qsTr("Mutation Probability:")
                        verticalAlignment: Text.AlignVCenter
                    }

                    TextField {
                        id: mutationProb
                        Layout.maximumWidth: 55
                        Layout.maximumHeight: 26
                        Layout.alignment: Qt.AlignRight

                        text: qsTr("0.3")
                        horizontalAlignment: Text.AlignHCenter
                        selectByMouse: true
                        validator: DoubleValidator {
                            bottom: 0
                            top: 999
                        }
                    }
                }
            }

            layer.enabled: true // Set Layer for Enable
            layer.effect: DropShadow {
                transparentBorder: true
                color: "#80000000"
                radius: 8
                samples: 17
                horizontalOffset: -1
                verticalOffset: 1
            }
        }

        LoaderBtn {
            text: "Apply Parameters"
            anchors.top: rectangleFore.bottom
            anchors.topMargin: 30
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                if (randSeed.text == "") {
                    randSeed.text = qsTr("1")
                }
                else {
                    backend.recieveOptimizerSetting("Random Seed", randSeed.text)
                }

                if(stimPosition.text == "") {
                    stimPosition.text = qsTr("2")
                }
                else {
                    backend.recieveOptimizerSetting("Population Size", stimPosition.text)
                }

                if(numGenerations.text == "") {
                    numGenerations.text = qsTr("10")
                }
                else {
                    backend.recieveOptimizerSetting("Number of Generations", numGenerations.text)
                }

                if(offSpringSize.text == "") {
                    offSpringSize.text = qsTr("2")
                }
                else {
                    backend.recieveOptimizerSetting("Offspring Size", offSpringSize.text)
                }

                if(mutationProb.text == "") {
                    mutationProb.text = qsTr("0.3")
                }
                else {
                    backend.recieveOptimizerSetting("Mutation Probability", mutationProb.text)
                }
            }
        }

        Label {
            id: label
            x: 307
            color: "#ffffff"
            text: qsTr("Settings")
            anchors.top: parent.top
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 50
            font.pointSize: 17
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}





/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:3}
}
##^##*/
