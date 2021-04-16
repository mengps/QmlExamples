import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 1000
    height: 800
    title: qsTr("Hello World")

    Column {
        anchors.fill: parent
        spacing: 20

        Rectangle {
            width: parent.width / 2
            height: parent.height / 2 - 20
            anchors.horizontalCenter: parent.horizontalCenter
            color: "#e6a8f7"

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onEntered: parent.color = "#c91bf9";
                onExited: parent.color = "#e6a8f7";
            }

            Row {
                anchors.centerIn: parent
                spacing: 20

                Rectangle {
                    width: 80
                    height: 80
                    color: "#ff4d4d"

                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        onEntered: parent.color = "#cc0808";
                        onExited: parent.color = "#ff4d4d";
                    }
                }

                Rectangle {
                    width: 80
                    height: 80
                    color: "#4dff4d"

                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        onEntered: parent.color = "#08cc08";
                        onExited: parent.color = "#4dff4d";
                    }
                }

                Rectangle {
                    width: 80
                    height: 80
                    color: "#4d4dff"

                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        onEntered: parent.color = "#0808cc";
                        onExited: parent.color = "#4d4dff";
                    }
                }
            }
        }

        Rectangle {
            width: parent.width / 2
            height: parent.height / 2 - 20
            anchors.horizontalCenter: parent.horizontalCenter
            color: "#e6a8f7"

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onEntered: parent.color = "#c91bf9";
                onExited: parent.color = "#e6a8f7";
                onClicked: console.log("parent clicked");

                Row {
                    anchors.centerIn: parent
                    spacing: 20

                    Rectangle {
                        width: 80
                        height: 80
                        color: "#ff4d4d"

                        MouseArea {
                            anchors.fill: parent
                            hoverEnabled: true
                            propagateComposedEvents: true
                            onEntered: parent.color = "#cc0808";
                            onExited: parent.color = "#ff4d4d";
                            onClicked: {
                                console.log("child 1 clicked");
                                mouse.accepted = false;
                            }
                        }
                    }

                    Rectangle {
                        width: 80
                        height: 80
                        color: "#4dff4d"

                        MouseArea {
                            anchors.fill: parent
                            hoverEnabled: true
                            propagateComposedEvents: true
                            onEntered: parent.color = "#08cc08";
                            onExited: parent.color = "#4dff4d";
                            onClicked: {
                                console.log("child 2 clicked");
                                mouse.accepted = false;
                            }
                        }
                    }

                    Rectangle {
                        width: 80
                        height: 80
                        color: "#4d4dff"
                        border.color: "blue"

                        MouseArea {
                            anchors.fill: parent
                            hoverEnabled: true
                            propagateComposedEvents: true
                            onEntered: parent.color = "#0808cc";
                            onExited: parent.color = "#4d4dff";
                            onClicked: {
                                console.log("child 3 clicked");
                                mouse.accepted = false;
                            }
                        }
                    }
                }
            }
        }
    }
}
