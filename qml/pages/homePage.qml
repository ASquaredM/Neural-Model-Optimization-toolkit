import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15
import "../controls"

Item {
    Rectangle {
        id: rectangle
        color: "#2c313c"
        anchors.fill: parent

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
                backend.sendParamList(loaderBtn.text)
            }
        }

        Component {
            id: delegate
            Item{
                id: delItem
                width: 200
                height:50

                Row {
                    anchors.fill:parent
                    spacing: 10

                    Label {
                        id: labelR1
                        text: element1
                        color: "#ffffff"
                        font.bold:true
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }

                    Label {
                        id: labelR2
                        text: element2
                        color: "#ffffff"
                        font.bold:true
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }

                    Label {
                        id: labelR3
                        text: element3
                        color: "#ffffff"
                        font.bold:true
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
                }
            }
        }

        ListModel{
            id: paramModel

            ListElement{
                element1: "e1"
                element2: "e2"
                element3: "e3"
            }
        }

        Rectangle {
            id: rectangle2
            width: 250
            color: "#242936"
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: loaderBtn.top
            clip: true
            anchors.topMargin: 60
            anchors.bottomMargin: 50
            anchors.rightMargin: 50

            ScrollView {
                id: scrollView
                anchors.fill: parent
                anchors.bottomMargin: 10
                anchors.rightMargin: 10
                anchors.leftMargin: 10
                anchors.topMargin: 10
                ListView{
                    anchors.fill: parent
                    model: paramModel
                    delegate: delegate
                }
            }
        }

        DropShadow{
            anchors.fill: rectangle2
            horizontalOffset: -5
            verticalOffset: 5
            radius: 8
            samples: 17
            color: "#80000000"
            source: rectangle2
        }

        Rectangle {
            id: modelView
            width: 280
            height: 247
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.topMargin: 60
            anchors.leftMargin: 50
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
        }

        DropShadow{
            anchors.fill: modelView
            horizontalOffset: -5
            verticalOffset: 5
            radius: 8
            samples: 17
            color: "#80000000"
            source: modelView
        }

        Connections{
            target: backend
            function onAppBuffer(name){
                paramModel.append(JSON.parse(name))
                loaderBtn.text = name
            }
        }

    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:800}
}
##^##*/
