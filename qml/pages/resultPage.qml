import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15
import QtQuick.Layouts 1.15
import "../controls"

Item {
    Rectangle {
        id: rectangle
        color: "#2c313c"
        anchors.fill: parent

        RowLayout {
            id: gridResult
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: rowBtns.top
            anchors.rightMargin: 15
            anchors.leftMargin: 15
            anchors.topMargin: 15
            anchors.bottomMargin: 30

            Rectangle {
                id: paramView
                color: "#242936"
                clip: true

                Layout.alignment: Qt.AlignHCenter
                Layout.maximumWidth: 300
                Layout.maximumHeight: 450
                Layout.fillWidth: true
                Layout.fillHeight: true

                ScrollView {
                    id: scrollViewParam
                    anchors.fill: parent
                    anchors.bottomMargin: 10
                    anchors.rightMargin: 10
                    anchors.leftMargin: 10
                    anchors.topMargin: 10
                    ListView {
                        anchors.fill: parent
                        model: paramModel
                        delegate: delegateParam
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

            Rectangle {
                id: fitnessView
                color: "#242936"
                clip: true

                Layout.alignment: Qt.AlignHCenter
                Layout.maximumWidth: 300
                Layout.maximumHeight: 450
                Layout.fillWidth: true
                Layout.fillHeight: true

                ScrollView {
                    id: scrollViewFit
                    anchors.fill: parent
                    anchors.bottomMargin: 10
                    anchors.rightMargin: 10
                    anchors.leftMargin: 10
                    anchors.topMargin: 10
                    ListView {
                        anchors.fill: parent
                        model: fitModel
                        delegate: delegateFit
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
        }

        RowLayout {
            id: rowBtns
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottomMargin: 30
            LoaderBtn {
                text: "Save Parameters"
                onClicked: {
                    backend.saveRes()
                }
            }


            /*
            LoaderBtn {
                text: "TBD"
            }
            */
        }

        Connections {
            target: backend
            function onAppResultBufferParam(str) {
                paramModel.append(JSON.parse(str))
            }

            function onAppResultBufferFitness(str) {
                fitModel.append(JSON.parse(str))
            }
        }

        Component {
            id: delegateParam
            Item {
                id: delItem
                width: parent.width
                height: 30

                RowLayout {
                    anchors.fill: parent
                    spacing: 10

                    Label {
                        id: labelR1
                        text: element1
                        color: "#ffffff"
                        font.bold: true
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }

                    Label {
                        id: labelR2
                        text: element2
                        color: "#ffffff"
                        font.bold: true
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }

                    Label {
                        id: labelR3
                        text: element3
                        color: "#ffffff"
                        font.bold: true
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        fontSizeMode: Text.Fit

                        Layout.alignment: Qt.AlignRight
                    }
                }
            }
        }

        ListModel {
            id: paramModel

            ListElement {
                element1: "Compartement"
                element2: "Channel"
                element3: "Best Solution"
            }
        }

        Component {
            id: delegateFit
            Item {
                id: delItem
                width: parent.width
                height: 30

                RowLayout {
                    anchors.fill: parent

                    Label {
                        id: labelR1
                        text: element1
                        color: "#ffffff"
                        font.bold: true
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }

                    Label {
                        id: labelR2
                        text: element2
                        color: "#ffffff"
                        font.bold: true
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        fontSizeMode: Text.Fit

                        Layout.alignment: Qt.AlignRight
                    }
                }
            }
        }

        ListModel {
            id: fitModel

            ListElement {
                element1: "Feature"
                element2: "Error"
            }
        }
    }
}



