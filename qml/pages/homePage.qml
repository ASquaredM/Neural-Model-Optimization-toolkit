import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15
import QtQuick.Layouts 1.15
import QtQuick.Shapes 1.15
import QtQuick.Dialogs 1.3
import "../controls"

Item {
    Rectangle {
        id: rectangle
        color: "#2c313c"
        anchors.fill: parent

        GridLayout {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: loaderBtn.top
            anchors.rightMargin: 30
            anchors.leftMargin: 30
            anchors.topMargin: 30
            anchors.bottomMargin: 15
            columns: 2
            columnSpacing: 30

            Rectangle {
                id: presetsRec
                color: "#242936"

                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 280
                Layout.preferredHeight: 102

                GridLayout {
                    anchors.fill: parent
                    anchors.rightMargin: 10
                    anchors.leftMargin: 10
                    columns: 2
                    rows: 2

                    Label {
                        color: "#f8f9f9"
                        text: "Set Model Name:"
                    }

                    TextField {
                        id: modelName
                        Layout.maximumWidth: 101
                        Layout.maximumHeight: 26
                    }

                    Label {
                        color: "#f0f0f1"
                        text: "Choose Simulator"
                    }

                    ComboBox {
                        id: simName
                        Layout.maximumWidth: 101
                        Layout.maximumHeight: 26
                        model: ["NEURON"]
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
                id: modelView

                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 280
                Layout.preferredHeight: 247
                Layout.column: 0
                Layout.row: 1

                gradient: Gradient {
                    GradientStop {
                        position: 0
                        color: "#2b5876"
                    }

                    GradientStop {
                        position: 1
                        color: "#4e4376"
                    }
                }

                Rectangle {
                    id: rectangle1
                    color: "#00000000"
                    anchors.fill: parent

                    RowLayout {
                        anchors.fill: parent


                        /*
                        Shape {
                            Layout.alignment: Qt.AlignRight
                            width: 101
                            height: 101
                            ShapePath {
                                strokeColor: "red"
                                startX: 101
                                startY: 20
                                PathLine {
                                    x: 59
                                    y: 20
                                }
                                PathLine {
                                    x: 59
                                    y: 60
                                }
                                PathLine {
                                    x: 101
                                    y: 60
                                }
                                PathLine {
                                    x: 101
                                    y: 20
                                }
                            }
                        }
                        */


                        /*
                        Shape {
                            width: 50
                            height: 50
                            ShapePath {
                                strokeWidth: 4
                                strokeColor: "red"
                                startX: 140
                                startY: 140
                                PathLine {
                                    x: 20
                                    y: 20
                                }
                                PathLine {
                                    x: 140
                                    y: 20
                                }
                                PathLine {
                                    x: 140
                                    y: 140
                                }
                            }
                        }
                        */
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
                id: paramView
                color: "#242936"
                clip: true

                Layout.alignment: Qt.AlignHCenter
                Layout.minimumWidth: 250
                Layout.minimumHeight: 300
                Layout.maximumWidth: 350
                Layout.maximumHeight: 450
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.rowSpan: 2
                Layout.column: 1

                ScrollView {
                    id: scrollView
                    anchors.fill: parent
                    anchors.bottomMargin: 10
                    anchors.rightMargin: 10
                    anchors.leftMargin: 10
                    anchors.topMargin: 10
                    ListView {
                        anchors.fill: parent
                        model: paramModel
                        delegate: delegate
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

        MessageDialog {
            id: mBox
            title: "Warning"
        }

        LoaderBtn {
            id: loaderBtn
            x: 217
            y: 391
            width: 206
            height: 40
            text: "Load Model"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 50
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                if (modelName.text != "") {
                    fileDialog.open()
                } else {
                    mBox.text = "Please Enter Model Name"
                    mBox.open()
                }
            }

            FileDialog {
                id: fileDialog
                title: "Please choose a model"
                // folder: shortcuts.home
                nameFilters: ["HOC files (*.hoc)", "All files (*)"]
                onAccepted: {
                    console.log("You chose: " + fileDialog.fileUrls)
                    backend.updateModelPath(fileDialog.fileUrl)
                    backend.updateModelName(modelName.text)
                    backend.fetchModel()
                    //tuningBtn.enabled = true
                }
                onRejected: {
                    console.log("Canceled")
                }
            }
        }

        Connections {
            target: backend
            function onAppHomeBuffer(name) {
                paramModel.append(JSON.parse(name))
            }
        }

        Component {
            id: delegate
            Item {
                id: delItem
                width: parent.width - 15
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

                        Layout.alignment: Qt.AlignRight
                    }
                }
            }
        }

        ListModel {
            id: paramModel

            ListElement {
                element1: "Compartement"
                element2: "Channels"
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:600;width:800}
}
##^##*/

