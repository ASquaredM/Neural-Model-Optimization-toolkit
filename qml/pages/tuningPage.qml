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
            text: qsTr("Tune Model")
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 50
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Component {
            id: delegateFitness
            FitnessCheck{
                id: delItemFitness
                width: parent.width
                height: 35
                text: name

                TextField {
                    id: textFieldFitness1
                    x: textFieldFitness2.x - textFieldFitness2.width - 20
                    width: widthTextField
                    height: heightTextField
                    anchors.verticalCenter: parent.verticalCenter

                    placeholderText: "weight"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    maximumLength: 3
                    selectByMouse: true
                    validator: IntValidator {bottom: 0; top: 999}

                    background: Rectangle { radius: radiusTextField }
                }

                TextField {
                    id: textFieldFitness2
                    x: textFieldFitness3.x - textFieldFitness3.width - 5
                    width: widthTextField
                    height: heightTextField
                    anchors.verticalCenter: parent.verticalCenter

                    placeholderText: "mean"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    maximumLength: 3
                    selectByMouse: true
                    validator: IntValidator {bottom: 0; top: 999}

                    background: Rectangle { radius: radiusTextField }
                }

                TextField {
                    id: textFieldFitness3
                    x: delItemFitness.width - width
                    width: widthTextField
                    height: heightTextField
                    anchors.verticalCenter: parent.verticalCenter

                    placeholderText: "std deviation"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    maximumLength: 3
                    selectByMouse: true
                    validator: IntValidator {bottom: 0; top: 999}

                    background: Rectangle { radius: radiusTextField }
                }
            }

            /*
            CheckDelegate {
                text: name
            }
            */
        }

        ListModel{
            id: modelFitness
            
            ListElement{
                name: "Spike Count"
            }

            ListElement{
                name: "AP amplitude"
            }

            ListElement{
                name: "AP width"
            }
            
            ListElement{
                name: "AHP depth"
            }

            ListElement{
                name: "AP width"
            }

            ListElement{
                name: "AP width"
            }
        }

        Rectangle {
            id: rectangle1
            width: 350
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: loaderBtn.top
            clip: true
            anchors.topMargin: 60
            anchors.bottomMargin: 50
            anchors.rightMargin: 43
            color: "#242936"
            
            ScrollView {
                id: scrollView
                anchors.fill: parent
                anchors.rightMargin: 10
                anchors.leftMargin: 10
                anchors.bottomMargin: 10
                anchors.topMargin: 10
                ListView{
                    anchors.fill: parent
                    model: modelFitness
                    delegate: delegateFitness
                }
            }
        }

        DropShadow{
            anchors.fill: rectangle1
            horizontalOffset: -5
            verticalOffset: 5
            radius: 8
            samples: 17
            color: "#80000000"
            source: rectangle1
        }

        Component {
            id: delegateParam
            FitnessCheck{
                id: delItemParam
                width: parent.width
                height: 35
                text: name
                font.bold: true

                Label {
                    id: label2
                    x: label3.x - label3.width - 25
                    height: 26
                    anchors.verticalCenter: parent.verticalCenter
                    
                    text: number
                    font.bold: false
                    opacity: enabled ? 1.0 : 0.3
                    color: delItemParam.down ? "#2c313c" : "#ffffff"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
                Label {
                    id: label3
                    x: textField1.x - textField1.width - 5
                    height: 26
                    anchors.verticalCenter: parent.verticalCenter

                    text: "  "
                    opacity: enabled ? 1.0 : 0.3
                    color: delItemParam.down ? "#2c313c" : "#ffffff"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
                TextField {
                    id: textField1
                    x: label4.x - label4.width - 5
                    width: 35
                    height: 26
                    anchors.verticalCenter: parent.verticalCenter

                    placeholderText: index
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    maximumLength: 3
                    selectByMouse: true
                    validator: IntValidator {bottom: 0; top: 999}

                    background: Rectangle { radius: 4 }
                }
                Label {
                    id: label4
                    x: textField2.x - textField2.width + 13
                    height: 26
                    width: 26
                    anchors.verticalCenter: parent.verticalCenter

                    text: "to"
                    font.bold: false
                    opacity: enabled ? 1.0 : 0.3
                    color: delItemParam.down ? "#2c313c" : "#ffffff"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
                TextField {
                    id: textField2
                    x: delItemParam.width - width
                    width: 35
                    height: 26
                    anchors.verticalCenter: parent.verticalCenter

                    placeholderText: index
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    maximumLength: 3
                    selectByMouse: true
                    validator: IntValidator {bottom: 0; top: 999}

                    background: Rectangle { radius: 4 }
                }
            }
        }

        ListModel{
            id: modelParam
            
            ListElement{
                index: "01"
                name: "Soma"
                number: "CaSmb1"
            }

            ListElement{
                index: "02"
                name: "Soma"
                number: "KdrSmb1"
            }

            ListElement{
                index: "03"
                name: "Soma"
                number: "NafSmb1"
            }

            ListElement{
                index: "04"
                name: "Soma"
                number: "pas"
            }
        }

        Rectangle {
            id: rectangle2
            x: 50
            width: 285
            anchors.top: parent.top
            anchors.bottom: loaderBtn.top
            anchors.rightMargin: 122
            clip: true
            anchors.topMargin: 60
            anchors.bottomMargin: 50
            color: "#242936"
            anchors.right: rectangle1.left

            ScrollView {
                id: scrollView2
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                anchors.rightMargin: 10
                anchors.leftMargin: 10
                anchors.topMargin: 10
                ListView{
                    anchors.fill: parent
                    model: modelParam
                    delegate: delegateParam
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

    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:800}
}
##^##*/
