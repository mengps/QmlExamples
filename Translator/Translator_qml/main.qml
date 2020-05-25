import QtQuick 2.13
import QtQuick.Window 2.13
import QtQuick.Controls 2.13
import an.translate 1.0

ApplicationWindow {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("MainWindow")

    property int language: Language.English

    ActionGroup {
        id: languageGroup
    }

    menuBar: MenuBar {
        Menu {
            id: languageMenu
            title: qsTr("Language")

            Action {
                checked: language == Language.English
                checkable: true
                text: qsTr("English")
                ActionGroup.group: languageGroup
                onTriggered: {
                    controller.loadLanguage(Language.English);
                    language = Language.English;
                }
            }

            Action {
                checked: language == Language.Chinese
                checkable: true
                text: qsTr("Chinese")
                ActionGroup.group: languageGroup
                onTriggered: {
                    controller.loadLanguage(Language.Chinese);
                    language = Language.Chinese;
                }
            }
        }
    }

    Connections {
        target: controller
        onMessage: {
            statusBar.text = msg;
        }
    }

    Text {
        id: statusBar
        visible: false
        color: "red"
        anchors {
            bottom: parent.bottom
            bottomMargin: 30
            left: parent.left
            leftMargin: 20
        }
        onTextChanged: {
            visible = true;
            textTimer.restart();
        }

        Timer {
            id: textTimer
            running: false
            interval: 1000
            onTriggered: statusBar.visible = false;
        }
    }

    Label {
        id: label
        anchors.centerIn: parent
        text: qsTr("This is \"Test Text\"")
        font { pointSize: 26 }
    }

    Button {
        id: button
        text: qsTr("Change Language")
        anchors {
            bottom: label.top
            bottomMargin: 30
            horizontalCenter: parent.horizontalCenter
        }

        onClicked: {
            if (language == Language.English){
                controller.loadLanguage(Language.Chinese);
                language = Language.Chinese;
            } else {
                controller.loadLanguage(Language.English);
                language = Language.English;
            }
        }
    }
}
