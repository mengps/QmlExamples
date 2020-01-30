import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    id: root
    visible: true
    width: 860
    height: 660 + tabBar.height + 4
    title: qsTr("MultiView Test")

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page {
            id: page1
            width: 860
            height: 660

            Connections {
                target: view
                onViewNeedUpdate: {
                    /**
                      * 1. index为视图索引
                      * 2. ###用于分隔
                      * 3. Date.now()用于更新
                      */
                    viewRepeater.itemAt(index).source = "image://MultiView/" + index + "###" + Date.now();
                }
            }

            Grid {
                rows: 3
                columns: 3
                anchors.fill: parent

                Repeater {
                    id: viewRepeater
                    model: 9

                    Image {
                        cache: false
                        mipmap: true
                        width: page1.width / 3
                        height: page1.height / 3

                        Text {
                            anchors.left: parent.left
                            anchors.leftMargin: 12
                            anchors.top: parent.top
                            anchors.topMargin: 12
                            font.bold: true
                            font.pointSize: 30
                            color: "red"
                            text: index
                        }

                        Rectangle {
                            anchors.fill: parent
                            border.width: 2
                            border.color: "yellow"
                            color: "transparent"
                        }
                    }
                }
            }
        }

        Page {
            id: page2
            width: 860
            height: 660

            Connections {
                target: view
                onSourceNeedUpdate: {
                    /**
                      * 1. source为图像源索引
                      * 2. ###用于分隔
                      * 3. Date.now()用于更新
                      */
                    sourceRepeater.itemAt(source).source = "image://MultiSource/" + source + "###" + Date.now();
                }
            }

            Grid {
                rows: 2
                columns: 2
                anchors.fill: parent

                Repeater {
                    id: sourceRepeater
                    model: 4

                    Image {
                        mipmap: true
                        width: page2.width / 2
                        height: page2.height / 2
                        fillMode: Image.PreserveAspectFit

                        property bool running: true

                        Image {
                            width: 80
                            height: 80
                            anchors.centerIn: parent
                            opacity: 0.7
                            mipmap: true
                            source: parent.running ? "" : "qrc:/play.png"
                        }

                        Text {
                            anchors.left: parent.left
                            anchors.leftMargin: 12
                            anchors.top: parent.top
                            anchors.topMargin: 12
                            font.bold: true
                            font.pointSize: 30
                            color: "red"
                            text: index
                        }

                        Rectangle {
                            anchors.fill: parent
                            border.width: 2
                            border.color: "#89f2f5"
                            color: "transparent"
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                if (parent.running) {
                                    view.pauseSource(index);
                                    parent.running = false;
                                } else {
                                    view.resumeSource(index);
                                    parent.running = true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex

        TabButton {
            font.pointSize: 12
            text: qsTr("多视图")
            onClicked: view.stopSource();
        }

        TabButton {
            font.pointSize: 12
            text: qsTr("多图像源")
            onClicked: {
                view.startSource();

                for (let i = 0; i < 4; i++)
                    sourceRepeater.itemAt(i).running = true;
            }
        }
    }
}
