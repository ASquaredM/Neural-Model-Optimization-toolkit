import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15
import "controls"

Window {
    id: mainWindow
    width: 1000
    height: 600
    minimumWidth: 1000
    minimumHeight: 550
    visible: true
    color: "#00000000"
    title: qsTr("App")

    //Remove the default title bar
    flags: Qt.Window | Qt.FramelessWindowHint

    // Propeties
    property int windowStatus: 0
    property int windowMargin: 10
    property int currPage: 0
    property int modelUp: 0

    // Internal functions
    QtObject {
        id: internal

        function resetResizeBorders() {
            // Resize visibility
            resizeLeft.visible = true
            resizeRight.visible = true
            resizeBottom.visible = true
            resizeWindow.visible = true
        }

        function maximizeRestore() {
            if (windowStatus == 0) {
                mainWindow.showMaximized()
                windowStatus = 1
                windowMargin = 0
                // Resize visibility
                resizeLeft.visible = false
                resizeRight.visible = false
                resizeBottom.visible = false
                resizeWindow.visible = false
                maximizeBtn.btnIconSource = "../images/svg_images/restore_icon.svg"
            } else {
                mainWindow.showNormal()
                windowStatus = 0
                windowMargin = 10
                // Resize visibility
                internal.resetResizeBorders()
                maximizeBtn.btnIconSource = "../images/svg_images/maximize_icon.svg"
            }
        }

        function ifMaximizedWindowRestore() {
            if (windowStatus == 1) {
                mainWindow.showNormal()
                windowStatus = 0
                windowMargin = 10
                // Resize visibility
                internal.resetResizeBorders()
                maximizeBtn.btnIconSource = "../images/svg_images/maximize_icon.svg"
            }
        }

        function restoreMargins() {
            windowStatus = 0
            windowMargin = 10
            // Resize visibility
            internal.resetResizeBorders()
            maximizeBtn.btnIconSource = "../images/svg_images/maximize_icon.svg"
        }
    }

    Rectangle {
        id: bg
        color: "#2c313c"
        border.color: "#383e4c"
        border.width: 1
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.rightMargin: windowMargin
        anchors.leftMargin: windowMargin
        anchors.bottomMargin: windowMargin
        anchors.topMargin: windowMargin
        z: 1

        Rectangle {
            id: appContainer
            color: "#00000000"
            anchors.fill: parent
            anchors.rightMargin: 1
            anchors.leftMargin: 1
            anchors.bottomMargin: 1
            anchors.topMargin: 1

            Rectangle {
                id: topBar
                height: 60
                color: "#1c1d20"
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.rightMargin: 0
                anchors.leftMargin: 0
                anchors.topMargin: 0

                ToggleBtn {
                    onClicked: leftMenuAnimation.running = true
                }

                Rectangle {
                    id: topBarDescription
                    y: 8
                    height: 25
                    color: "#282c34"
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.rightMargin: 0
                    anchors.leftMargin: 70
                    anchors.bottomMargin: 0

                    Label {
                        id: labelTopInfo
                        color: "#5f6a82"
                        text: qsTr("Tune Neural Models")
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        verticalAlignment: Text.AlignVCenter
                        anchors.rightMargin: 301
                        anchors.leftMargin: 10
                        anchors.bottomMargin: 0
                        anchors.topMargin: 0
                    }

                    Label {
                        id: labelTopRightInfo
                        color: "#5f6a82"
                        text: qsTr("HOME")
                        anchors.left: labelTopInfo.right
                        anchors.right: parent.right
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        horizontalAlignment: Text.AlignRight
                        verticalAlignment: Text.AlignVCenter
                        anchors.leftMargin: 0
                        anchors.rightMargin: 10
                        anchors.topMargin: 0
                        anchors.bottomMargin: 0
                    }
                }

                Rectangle {
                    id: titleBar
                    height: 35
                    color: "#00000000"
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.rightMargin: 105
                    anchors.leftMargin: 70
                    anchors.topMargin: 0

                    DragHandler {
                        onActiveChanged: if (active) {
                                             mainWindow.startSystemMove()
                                             internal.ifMaximizedWindowRestore()
                                         }
                    }

                    Image {
                        id: appIcon
                        width: 28
                        anchors.left: parent.left
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        source: "../images/svg_images/app_icon.svg"
                        layer.format: ShaderEffectSource.RGB
                        anchors.bottomMargin: 0
                        anchors.leftMargin: 5
                        anchors.topMargin: 0
                        fillMode: Image.PreserveAspectFit
                    }

                    ColorOverlay {
                        anchors.fill: appIcon
                        source: appIcon
                        color: "#c3cbdd"
                        antialiasing: false
                    }

                    Label {
                        id: labelAppTitle
                        color: "#c3cbdd"
                        text: qsTr("Neural Model Optimization toolkit")
                        anchors.left: appIcon.right
                        anchors.right: parent.right
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        verticalAlignment: Text.AlignVCenter
                        font.pointSize: 11
                        anchors.leftMargin: 5
                    }
                }

                Row {
                    id: btnRow
                    x: 0
                    y: 0
                    width: 105
                    height: 35
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.rightMargin: 0
                    anchors.topMargin: 0

                    TopBarBtn {
                        id: minimizeBtn
                        onClicked: {
                            mainWindow.showMinimized()
                            internal.restoreMargins()
                        }
                    }

                    TopBarBtn {
                        id: maximizeBtn
                        btnIconSource: "../images/svg_images/maximize_icon.svg"
                        onClicked: internal.maximizeRestore()
                    }

                    TopBarBtn {
                        id: closeBtn
                        btnColorClicked: "#ff0000"
                        btnIconSource: "../images/svg_images/close_icon.svg"
                        onClicked: mainWindow.close()
                    }
                }
            }

            Rectangle {
                id: content
                color: "#00000000"
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: topBar.bottom
                anchors.bottom: parent.bottom
                anchors.topMargin: 0

                Rectangle {
                    id: leftMenu
                    width: 70
                    color: "#1c1d20"
                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    clip: true
                    anchors.leftMargin: 0
                    anchors.bottomMargin: 0
                    anchors.topMargin: 0

                    PropertyAnimation {
                        id: leftMenuAnimation
                        target: leftMenu
                        property: "width"
                        to: (leftMenu.width == 70) ? 170 : 70
                        duration: 650
                        easing.type: Easing.InOutQuint
                    }

                    Column {
                        id: column
                        width: 70
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.rightMargin: 0
                        anchors.leftMargin: 0
                        anchors.bottomMargin: 90
                        anchors.topMargin: 0

                        LeftMenuBtn {
                            id: homeBtn
                            width: leftMenu.width
                            text: "Home"
                            isActiveMenu: true
                            onClicked: {
                                if (currPage != 0) {
                                    currPage = 0
                                    labelTopRightInfo.text = qsTr("Home")
                                    homeBtn.isActiveMenu = true
                                    measurementsBtn.isActiveMenu = false
                                    tuningBtn.isActiveMenu = false
                                    settingsBtn.isActiveMenu = false
                                    stackView.replace([stackView.currentItem,stackView.get(5)])
                                }
                            }
                        }

                        LeftMenuBtn {
                            id: tuningBtn
                            width: leftMenu.width
                            text: "Tuning"
                            enabled: false
                            btnIconSource: "../images/svg_images/tuning_icon.svg"
                            isActiveMenu: false
                            onClicked: {
                                if (currPage != 2) {
                                    currPage = 2
                                    labelTopRightInfo.text = qsTr("Tuning")
                                    homeBtn.isActiveMenu = false
                                    measurementsBtn.isActiveMenu = false
                                    tuningBtn.isActiveMenu = true
                                    settingsBtn.isActiveMenu = false
                                    stackView.replace([stackView.currentItem,stackView.get(3)])
                                    backend.fetchParam()
                                    backend.fetchSections()
                                }
                            }
                        }

                        LeftMenuBtn {
                            id: measurementsBtn
                            width: leftMenu.width
                            text: "Result"
                            enabled: false
                            btnIconSource: "../images/svg_images/measurements_icon.svg"
                            isActiveMenu: false
                            onClicked: {
                                if (currPage != 1) {
                                    currPage = 1
                                    labelTopRightInfo.text = qsTr(
                                                "Result")
                                    homeBtn.isActiveMenu = false
                                    measurementsBtn.isActiveMenu = true
                                    tuningBtn.isActiveMenu = false
                                    settingsBtn.isActiveMenu = false
                                    stackView.replace([stackView.currentItem,stackView.get(1)])
                                }
                            }
                        }
                    }

                    LeftMenuBtn {
                        id: settingsBtn
                        x: 0
                        y: 323
                        width: leftMenu.width
                        text: "Settings"
                        anchors.bottom: parent.bottom
                        btnIconSource: "../images/svg_images/settings_icon.svg"
                        isActiveMenu: false
                        anchors.bottomMargin: 25
                        onClicked: {
                            if (currPage != 3) {
                                currPage = 3
                                labelTopRightInfo.text = qsTr("Settings")
                                homeBtn.isActiveMenu = false
                                measurementsBtn.isActiveMenu = false
                                tuningBtn.isActiveMenu = false
                                settingsBtn.isActiveMenu = true
                                stackView.replace([stackView.currentItem,stackView.get(2)])
                            }
                        }
                    }
                }

                Rectangle {
                    id: pagesContent
                    color: "#00000000"
                    anchors.left: leftMenu.right
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    clip: true
                    anchors.rightMargin: 0
                    anchors.leftMargin: 0
                    anchors.bottomMargin: 25
                    anchors.topMargin: 0

                    StackView {
                        id: stackView
                        anchors.fill: parent
                        Component.onCompleted: {
                            stackView.push(Qt.resolvedUrl("pages/waitingPage.qml"))
                            stackView.push(Qt.resolvedUrl("pages/resultPage.qml"))
                            stackView.push(Qt.resolvedUrl("pages/settingsPage.qml"))
                            stackView.push(Qt.resolvedUrl("pages/tuningPage.qml"))
                            stackView.push(Qt.resolvedUrl("pages/measurementsPage.qml"))
                            stackView.push(Qt.resolvedUrl("pages/homePage.qml"))
                        }
                    }
                }

                Rectangle {
                    id: pagesBottomBar
                    color: "#282c34"
                    anchors.left: leftMenu.right
                    anchors.right: parent.right
                    anchors.top: pagesContent.bottom
                    anchors.bottom: parent.bottom
                    anchors.rightMargin: 0
                    anchors.leftMargin: 0
                    anchors.bottomMargin: 0
                    anchors.topMargin: 0

                    Label {
                        id: labelBottomBar
                        color: "#5f6a82"
                        text: qsTr("Build: 1.0")
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        verticalAlignment: Text.AlignVCenter
                        anchors.leftMargin: 10
                        anchors.rightMargin: 31
                        anchors.topMargin: 0
                        anchors.bottomMargin: 0
                    }
                    MouseArea {
                        id: resizeWindow
                        x: 884
                        y: 0
                        width: 25
                        height: 25
                        opacity: 0.5
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 0
                        anchors.rightMargin: 0
                        cursorShape: Qt.SizeFDiagCursor

                        DragHandler {
                            target: null
                            onActiveChanged: if (active) {
                                                 mainWindow.startSystemResize(
                                                             Qt.RightEdge | Qt.BottomEdge)
                                             }
                        }

                        Image {
                            id: resizeImage
                            width: 16
                            height: 16
                            anchors.fill: parent
                            source: "../images/svg_images/resize_icon.svg"
                            anchors.leftMargin: 5
                            anchors.topMargin: 5
                            sourceSize.height: 16
                            sourceSize.width: 16
                            fillMode: Image.PreserveAspectFit
                            antialiasing: false
                        }
                    }
                }
            }
        }
    }
    DropShadow {
        anchors.fill: bg
        horizontalOffset: 0
        verticalOffset: 0
        radius: 10
        samples: 16
        color: "#80000000"
        source: bg
        z: 0
    }

    MouseArea {
        id: resizeLeft
        width: 10
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.leftMargin: 0
        anchors.bottomMargin: 10
        anchors.topMargin: 10
        cursorShape: Qt.SizeHorCursor

        DragHandler {
            target: null
            onActiveChanged: if (active) {
                                 mainWindow.startSystemResize(Qt.LeftEdge)
                             }
        }
    }

    MouseArea {
        id: resizeRight
        width: 10
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.rightMargin: 0
        anchors.bottomMargin: 10
        anchors.topMargin: 10
        cursorShape: Qt.SizeHorCursor

        DragHandler {
            target: null
            onActiveChanged: if (active) {
                                 mainWindow.startSystemResize(Qt.RightEdge)
                             }
        }
    }

    MouseArea {
        id: resizeBottom
        height: 10
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        anchors.bottomMargin: 0
        cursorShape: Qt.SizeVerCursor

        DragHandler {
            target: null
            onActiveChanged: if (active) {
                                 mainWindow.startSystemResize(Qt.BottomEdge)
                             }
        }
    }

    Connections{
        target: backend

        function onEnableTune() {
            tuningBtn.enabled = true
        }

        function onPushRes() {
            currPage = 1
            labelTopRightInfo.text = qsTr("Result")
            homeBtn.isActiveMenu = false
            measurementsBtn.isActiveMenu = true
            tuningBtn.isActiveMenu = false
            settingsBtn.isActiveMenu = false
            stackView.replace([stackView.currentItem,stackView.get(1)])
            measurementsBtn.enabled = true
        }

        function onPushWait() {
            stackView.replace([stackView.currentItem,stackView.get(0)])
        }
    }
}
