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

            onClicked: {
                backend.getSigSettings()
                backend.tuneModel()
            }
        }

        GridLayout {
            id: gridLayout
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: loaderBtn.top
            anchors.bottomMargin: 15
            anchors.rightMargin: 15
            anchors.leftMargin: 15
            anchors.topMargin: 15
            columnSpacing: 15

            Rectangle {
                id: rectangle4
                color: "#242936"
                width: 200
                Layout.minimumWidth: 200
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredWidth: 200
                clip: true

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 5
                    width: rectangle4.width - 10

                    RowLayout {
                        id: row
                        Layout.alignment: Qt.AlignTop
                        Layout.fillWidth: true
                        width: rectangle4.width - 10

                        spacing: 10

                        Label {
                            id: label
                            color: "#f6f7f7"
                            text: qsTr("Stimulation Protocol:")
                            verticalAlignment: Text.AlignVCenter
                        }

                        ComboBox {
                            id: stimProtocol
                            Layout.alignment: Qt.AlignRight
                            Layout.maximumHeight: 26
                            Layout.maximumWidth: 95

                            model: ["IClamp"]
                        }
                    }

                    RowLayout {
                        id: row2
                        width: rectangle4.width - 10
                        Layout.fillWidth: true

                        spacing: 10

                        Label {
                            id: label2
                            color: "#f6f7f7"
                            text: qsTr("Stimulus Type:")
                            verticalAlignment: Text.AlignVCenter
                        }

                        ComboBox {
                            id: stimType
                            Layout.maximumHeight: 26
                            Layout.maximumWidth: 95
                            Layout.alignment: Qt.AlignRight

                            model: ["Step"]
                        }
                    }

                    RowLayout {
                        id: row3
                        width: rectangle4.width - 10
                        Layout.fillWidth: true

                        spacing: 10

                        Label {
                            id: label3
                            color: "#f6f7f7"
                            text: qsTr("Amplitude:")
                            verticalAlignment: Text.AlignVCenter
                        }

                        TextField {
                            id: amplitude
                            text: qsTr("21")
                            Layout.minimumWidth: 30
                            Layout.maximumWidth: 55
                            Layout.maximumHeight: 26
                            Layout.alignment: Qt.AlignRight

                            validator: DoubleValidator {
                                    bottom: 0
                                    top: 999
                            }

                            background: Rectangle {
                                radius: 2
                            }
                        }
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        width: rectangle4.width - 10
                        RowLayout {
                            id: row4
                            height: 80
                            Layout.fillWidth: true

                            spacing: 10

                            Label {
                                id: label4
                                color: "#f6f7f7"
                                text: qsTr("Delay:")
                                verticalAlignment: Text.AlignVCenter
                            }

                            TextField {
                                id: delay
                                text: qsTr("150")
                                Layout.maximumWidth: 55
                                Layout.maximumHeight: 26
                                Layout.alignment: Qt.AlignRight

                                validator: DoubleValidator {
                                    bottom: 0
                                    top: 999
                                }
                            }
                        }

                        RowLayout {
                            id: row5
                            height: 80
                            Layout.alignment: Qt.AlignRight
                            Layout.fillWidth: false

                            spacing: 10

                            Label {
                                id: label5
                                color: "#f6f7f7"
                                text: qsTr("Duration:")
                                verticalAlignment: Text.AlignVCenter
                            }

                            TextField {
                                id: duration
                                Layout.minimumWidth: 30
                                Layout.maximumHeight: 26
                                Layout.maximumWidth: 95
                                Layout.alignment: Qt.AlignRight

                                text: qsTr("3")
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignHCenter
                                selectByMouse: true
                                validator: DoubleValidator {
                                    bottom: 0
                                    top: 999
                                }

                                background: Rectangle {
                                    radius: 4
                                }
                            }
                        }
                    }

                    RowLayout {
                        id: row6
                        Layout.fillWidth: true
                        width: rectangle4.width - 10

                        spacing: 10

                        Label {
                            id: label6
                            color: "#f6f7f7"
                            text: qsTr("Stimulus Section:")
                            verticalAlignment: Text.AlignVCenter
                        }

                        ComboBox {
                            id: stimSection
                            width: 95
                            Layout.maximumHeight: 26
                            Layout.maximumWidth: 95
                            Layout.alignment: Qt.AlignRight

                            model: ["iseg"]
                        }
                    }

                    RowLayout {
                        id: row7
                        Layout.fillWidth: true
                        width: rectangle4.width - 10

                        spacing: 10

                        Label {
                            id: label7
                            color: "#f6f7f7"
                            text: qsTr("Stimulus Position:")
                            verticalAlignment: Text.AlignVCenter
                        }

                        TextField {
                            id: stimPosition
                            text: qsTr("0.5")
                            Layout.maximumWidth: 95
                            Layout.maximumHeight: 26
                            Layout.alignment: Qt.AlignRight

                            validator: DoubleValidator {
                                bottom: 0
                                top: 999
                            }
                        }
                    }

                    RowLayout {
                        id: row8
                        Layout.fillWidth: true
                        width: rectangle4.width - 10

                        spacing: 10

                        Label {
                            id: label8
                            color: "#f6f7f7"
                            text: qsTr("Param:")
                            verticalAlignment: Text.AlignVCenter
                        }

                        ComboBox {
                            id: param
                            Layout.maximumWidth: 95
                            Layout.maximumHeight: 26
                            Layout.alignment: Qt.AlignRight

                            model: ["V"]
                        }
                    }

                    RowLayout {
                        id: row9
                        Layout.fillWidth: true
                        width: rectangle4.width - 10

                        spacing: 10

                        Label {
                            id: label9
                            color: "#f6f7f7"
                            text: qsTr("Recording Section:")
                            verticalAlignment: Text.AlignVCenter
                        }

                        ComboBox {
                            id: recordingSection
                            Layout.maximumHeight: 26
                            Layout.maximumWidth: 95
                            Layout.alignment: Qt.AlignRight

                            model: ["soma"]
                        }
                    }

                    RowLayout {
                        id: row10
                        Layout.fillWidth: true
                        width: rectangle4.width - 10

                        spacing: 10

                        Label {
                            id: label10
                            color: "#f6f7f7"
                            text: qsTr("Record Position:")
                            verticalAlignment: Text.AlignVCenter
                        }

                        TextField {
                            id: recordPos
                            Layout.maximumHeight: 26
                            Layout.maximumWidth: 95
                            Layout.alignment: Qt.AlignRight

                            text: qsTr("0.5")
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            selectByMouse: true
                            validator: DoubleValidator {
                                bottom: 0
                                top: 999
                            }

                            background: Rectangle {
                                radius: 4
                            }
                        }
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        width: rectangle4.width - 10

                        RowLayout {
                            id: row11

                            spacing: 10

                            Label {
                                id: label11
                                color: "#f6f7f7"
                                text: qsTr("Vinit:")
                                verticalAlignment: Text.AlignVCenter
                            }

                            TextField {
                                id: vinit
                                Layout.maximumHeight: 26
                                Layout.maximumWidth: 95

                                text: qsTr("-65")
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignHCenter
                                selectByMouse: true
                                validator: DoubleValidator {
                                    bottom: 0
                                    top: 999
                                }

                                background: Rectangle {
                                    radius: 4
                                }
                            }
                        }

                        RowLayout {
                            id: row12
                            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter

                            spacing: 10

                            Label {
                                id: label12
                                Layout.alignment: Qt.AlignRight
                                color: "#f6f7f7"
                                text: qsTr("T stop:")
                                verticalAlignment: Text.AlignVCenter
                            }

                            TextField {
                                id: tStop
                                Layout.maximumWidth: 95
                                Layout.maximumHeight: 26
                                Layout.alignment: Qt.AlignRight

                                text: qsTr("500")
                                horizontalAlignment: Text.AlignHCenter
                                selectByMouse: true
                                validator: DoubleValidator {
                                    bottom: 0
                                    top: 999
                                }

                                background: Rectangle {
                                    radius: 4
                                }
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

            Rectangle {
                id: rectangle5
                color: "#242936"
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredWidth: 270
                clip: true

                ScrollView {
                    id: scrollView2_2
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 5
                    anchors.rightMargin: 10
                    anchors.leftMargin: 10
                    anchors.topMargin: 5
                    ListView {
                        anchors.fill: parent
                        model: modelParam
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
                id: rectangle6
                color: "#242936"
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredWidth: 300
                Layout.minimumWidth: 340
                clip: true

                ScrollView {
                    id: scrollView_2
                    anchors.fill: parent
                    anchors.rightMargin: 10
                    anchors.leftMargin: 10
                    anchors.bottomMargin: 5
                    anchors.topMargin: 5
                    ListView {
                        anchors.fill: parent
                        model: modelFitness
                        delegate: delegateFitness
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

        Connections {
            target: backend
            function onGetText(field) {
                const sigSettings = ["Protocol Name", "Stimulus Type", "Stimulus Section", "Param", "Recording Section", "Amplitude", "Delay", "Duration", "Stimulus Position", "Recording Position", "Vinit", "T stop"]
                const sigSettingsContainers = [stimProtocol, stimType, stimSection, param, recordingSection, amplitude, delay, duration, stimPosition, recordPos, vinit, tStop]
                if (field === "all") {
                    for (var i = 0; i < 5; i++) {
                        backend.recieveSigSettings(
                                    sigSettings[i],
                                    sigSettingsContainers[i].currentText)
                    }

                    for (var i = 5; i < 12; i++) {
                        backend.recieveSigSettings(
                                    sigSettings[i],
                                    sigSettingsContainers[i].text)
                    }
                }
            }

            function onAppTuningBuffer(nameParam) {
                modelParam.append(JSON.parse(nameParam))
            }
        }

        Component {
            id: delegateFitness
            FitnessCheck {
                id: delItemFitness
                width: parent.width
                height: 35
                text: name

                onClicked:{
                    if(delItemFitness.checked) {
                        if(textFieldFitness2.text != "") {
                            if(textFieldFitness1.text != "") {
                                if(textFieldFitness3.text != "") {
                                    backend.recieveFeature(text, textFieldFitness1.text, textFieldFitness2.text, textFieldFitness3.text)
                                }
                                else {
                                    backend.recieveFeature(text, textFieldFitness1.text, textFieldFitness2.text, "None")
                                }
                            }
                            else {
                                if(textFieldFitness3.text != "") {
                                    backend.recieveFeature(text, "1", textFieldFitness2.text, textFieldFitness3.text)
                                }

                                else {
                                    backend.recieveFeature(text, "1", textFieldFitness2.text, "None")
                                }
                            }
                        }
                        else {
                            mBox.text = "Please Enter Feature mean"
                            mBox.open()
                            delItemFitness.checked = false
                        }
                    }

                    else {
                        backend.removeFeature(text)
                    }
                }

                RowLayout {
                    anchors.verticalCenter: parent.verticalCenter
                    layoutDirection: Qt.RightToLeft
                    width: parent.width - 10
                    spacing: 5

                    RowLayout {
                        Layout.alignment: Qt.AlignLeft
                        TextField {
                            id: textFieldFitness2
                            width: widthTextField
                            height: heightTextField

                            placeholderText: "mean"
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            maximumLength: 3
                            selectByMouse: true
                            validator: DoubleValidator {
                                bottom: 0
                                top: 999
                            }

                            background: Rectangle {
                                radius: radiusTextField
                            }
                        }

                        TextField {
                            id: textFieldFitness3
                            Layout.alignment: Qt.AlignLeft
                            width: widthTextField
                            height: heightTextField

                            placeholderText: "std deviation"
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            maximumLength: 3
                            selectByMouse: true
                            validator: DoubleValidator {
                                bottom: 0
                                top: 999
                            }

                            background: Rectangle {
                                radius: radiusTextField
                            }
                        }
                    }

                    TextField {
                        id: textFieldFitness1
                        Layout.maximumWidth: widthTextField
                        Layout.alignment: Qt.AlignLeft
                        Layout.rightMargin: 5
                        height: heightTextField

                        placeholderText: "weight"
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        maximumLength: 3
                        selectByMouse: true
                        validator: DoubleValidator {
                            bottom: 0
                            top: 999
                        }

                        background: Rectangle {
                            radius: radiusTextField
                        }
                    }

                    Label {
                        text: name
                        color: "#00000000"
                        Layout.fillWidth: true
                        verticalAlignment: Text.AlignVCenter
                    }

                    Rectangle {
                        Layout.minimumWidth: 30
                        Layout.maximumWidth: 35
                        color: "#00000000"
                    }
                }
            }
        }

        ListModel {
            id: modelFitness

            ListElement {
                name: "Input Resistance"
            }

            ListElement {
                name: "Time Constant"
            }

            ListElement {
                name: "Rheobase"
            }

            ListElement {
                name: "Spike Count"
            }

            ListElement {
                name: "Time to First Spike"
            }

            ListElement {
                name: "AP Amplitude"
            }

            ListElement {
                name: "AP Height"
            }

            ListElement {
                name: "AP Width"
            }

            ListElement {
                name: "AHP Absolute Depth"
            }

            ListElement {
                name: "AHP time from peak"
            }

            ListElement {
                name: "SS Voltage"
            }

            ListElement {
                name: "Voltage Base"
            }
        }

        MessageDialog {
            id: mBox
            title: "Warning"
        }

        Component {
            id: delegateParam
            FitnessCheck {
                id: delItemParam
                width: parent.width
                height: 35
                text: sectionParam
                font.bold: true

                onClicked:{
                    if(delItemParam.checked) {
                        if(textField1.text != "") {
                            if(textField2.text != "") {
                                backend.recieveParam(text, nameParam, textField1.text,textField2.text)
                            }
                            else {
                                mBox.text = "Please Enter Parameter Upper Bound"
                                mBox.open()
                                delItemParam.checked = false
                            }
                        }
                        else {
                            mBox.text = "Please Enter Parameter Lower Bound"
                            mBox.open()
                            delItemParam.checked = false
                        }
                    }

                    else {
                        backend.removeParam(text, nameParam)
                    }
                }

                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: 75
                    width: parent.width
                    spacing: 5

                    Label {
                        id: label2
                        Layout.minimumWidth: 35
                        Layout.preferredHeight: 26
                        Layout.alignment: Qt.AlignHCenter

                        text: nameParam
                        font.bold: false
                        opacity: enabled ? 1.0 : 0.3
                        color: delItemParam.down ? "#2c313c" : "#ffffff"
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }

                    RowLayout {
                        Layout.alignment: Qt.AlignRight
                        spacing: 5

                        TextField {
                            id: textField1
                            Layout.preferredWidth: 35
                            Layout.preferredHeight: 26

                            placeholderText: "00"
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            maximumLength: 3
                            selectByMouse: true
                            validator: DoubleValidator {
                                bottom: 0
                                top: 999
                            }

                            background: Rectangle {
                                radius: 4
                            }
                        }

                        Label {
                            id: label4
                            Layout.preferredWidth: 26
                            Layout.preferredHeight: 26

                            text: "to"
                            font.bold: false
                            opacity: enabled ? 1.0 : 0.3
                            color: delItemParam.down ? "#2c313c" : "#ffffff"
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                        }

                        TextField {
                            id: textField2
                            Layout.preferredWidth: 35
                            Layout.preferredHeight: 26

                            placeholderText: "00"
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            maximumLength: 3
                            selectByMouse: true
                            validator: DoubleValidator {
                                bottom: 0
                                top: 999
                            }

                            background: Rectangle {
                                radius: 4
                            }
                        }
                    }
                }
            }
        }

        ListModel {
            id: modelParam

            ListElement {
                indexParam: 0
                sectionParam: "Section"
                nameParam: "Parameter"
            }
        }


        /*
        Rectangle {
            id: rectangle1
            width: 300
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: loaderBtn.top
            anchors.topMargin: 15
            anchors.bottomMargin: 30
            anchors.rightMargin: 15
            clip: true
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

        Rectangle {
            id: rectangle2
            x: 50
            width: 270
            anchors.top: parent.top
            anchors.bottom: loaderBtn.top
            anchors.rightMargin: 15
            clip: true
            anchors.topMargin: 15
            anchors.bottomMargin: 30
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

        Rectangle {
            id: rectangle3
            anchors.top: parent.top
            anchors.bottom: loaderBtn.top
            anchors.rightMargin: 15
            anchors.leftMargin: 15
            anchors.topMargin: 15
            anchors.bottomMargin: 30
            anchors.left: parent.left
            anchors.right: rectangle2.left
            color: "#242936"
            clip: true
            */


        /*
            ColumnLayout{
                anchors.fill: parent
                anchors.margins: 5

                RowLayout {
                    id: row
                    Layout.alignment: Qt.AlignTop
                    Layout.fillWidth: true
                    height: 30

                    spacing: 10

                    Label {
                        id: label
                        color: "#f6f7f7"
                        text: qsTr("Stimulation Protocol:")
                        verticalAlignment: Text.AlignVCenter
                    }

                    ComboBox {
                        id: comboBox
                        Layout.alignment: Qt.AlignRight
                        width: 95
                        height: 26

                        model: ["IClamp"]
                    }
                }

                RowLayout {
                    id: row2
                    x: 0
                    height: 80

                    spacing: 10

                    Label {
                        id: label2
                        color: "#f6f7f7"
                        text: qsTr("Stimulus Type:")
                        verticalAlignment: Text.AlignVCenter
                    }

                    ComboBox {
                        id: comboBox2
                        width: 95
                        height: 26

                        model: ["Step"]
                    }
                }

                RowLayout {
                    id: row3
                    x: 0
                    height: 80

                    spacing: 10

                    Label {
                        id: label3
                        color: "#f6f7f7"
                        text: qsTr("Amplitude:")
                        verticalAlignment: Text.AlignVCenter
                    }

                    TextField{
                        text: qsTr("21")
                    }
                }

                RowLayout {
                    id: row4
                    height: 80

                    spacing: 10

                    Label {
                        id: label4
                        color: "#f6f7f7"
                        text: qsTr("Delay:")
                        verticalAlignment: Text.AlignVCenter
                    }

                    TextField{
                        text: qsTr("150")
                    }
                }

                RowLayout {
                    id: row5
                    height: 80

                    spacing: 10

                    Label {
                        id: label5
                        color: "#f6f7f7"
                        text: qsTr("Duration:")
                        verticalAlignment: Text.AlignVCenter
                    }

                    TextField{
                        width: 35
                        height: 26

                        text: qsTr("3")
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        selectByMouse: true
                        validator: DoubleValidator {bottom: 0; top: 999}

                        background: Rectangle { radius: 4 }
                    }
                }

                RowLayout {
                    id: row6
                    height: 80

                    spacing: 10

                    Label {
                        id: label6
                        color: "#f6f7f7"
                        text: qsTr("Stimulus Section:")
                        verticalAlignment: Text.AlignVCenter
                    }

                    ComboBox {
                        id: comboBox6
                        width: 95
                        height: 26

                        model: ["Iseg"]
                    }
                }

                RowLayout {
                    id: row7
                    height: 80

                    spacing: 10

                    Label {
                        id: label7
                        color: "#f6f7f7"
                        text: qsTr("Stimulus Position:")
                        verticalAlignment: Text.AlignVCenter
                    }

                    TextField{
                        text: qsTr("0.5")
                    }
                }

                RowLayout {
                    id: row8
                    height: 80

                    spacing: 10

                    Label {
                        id: label8
                        color: "#f6f7f7"
                        text: qsTr("Param:")
                        verticalAlignment: Text.AlignVCenter
                    }

                    ComboBox {
                        id: comboBox8
                        width: 95
                        height: 26

                        model: ["V"]
                    }
                }

                RowLayout {
                    id: row9
                    height: 80

                    spacing: 10

                    Label {
                        id: label9
                        color: "#f6f7f7"
                        text: qsTr("Recording Section:")
                        verticalAlignment: Text.AlignVCenter
                    }

                    ComboBox {
                        id: comboBox9
                        width: 95
                        height: 26

                        model: ["Soma"]

                        background: Rectangle { radius: 4 }
                    }
                }

                RowLayout {
                    id: row10
                    height: 80

                    spacing: 10

                    Label {
                        id: label10
                        color: "#f6f7f7"
                        text: qsTr("Record Position:")
                        verticalAlignment: Text.AlignVCenter
                    }

                    TextField{
                        width: 35
                        height: 26

                        text: qsTr("0.5")
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        selectByMouse: true
                        validator: DoubleValidator {bottom: 0; top: 999}

                        background: Rectangle { radius: 4 }
                    }
                }

                RowLayout {
                    id: row11
                    height: 80

                    spacing: 10

                    Label {
                        id: label11
                        color: "#f6f7f7"
                        text: qsTr("Vinit:")
                        verticalAlignment: Text.AlignVCenter
                    }

                    TextField{
                        width: 35
                        height: 26

                        text: qsTr("-65")
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        selectByMouse: true
                        validator: DoubleValidator {bottom: 0; top: 999}

                        background: Rectangle { radius: 4 }
                    }
                }

                RowLayout {
                    id: row12
                    height: 80

                    spacing: 10

                    Label {
                        id: label12
                        color: "#f6f7f7"
                        text: qsTr("T stop:")
                        verticalAlignment: Text.AlignVCenter
                    }

                    TextField{
                        width: 35
                        height: 26

                        text: qsTr("500")
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        selectByMouse: true
                        validator: DoubleValidator {bottom: 0; top: 999}

                        background: Rectangle { radius: 4 }
                    }
                }
            }
            */


        /*
        }

        DropShadow{
            anchors.fill: rectangle3
            horizontalOffset: -5
            verticalOffset: 5
            radius: 8
            samples: 17
            color: "#80000000"
            source: rectangle3
        }
        */
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:600;width:800}
}
##^##*/

