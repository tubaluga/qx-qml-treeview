import QtQuick 2.11
import QtQuick.Controls 2.2

import Qx.treeview 1.0

import Example 1.0

ApplicationWindow {    
    width: 1024
    height: 768

    title: Qt.application.displayName
    visible: true

    FileSystemModel {
        id: file_system_model
    }

    ExampleTreeItemModel {
        id: example_model
    }

    /*QxTreeView {
        anchors.fill: parent
        model: example_model
    }*/

    /*QxHorisontalHeaderView {
        id: header_view

        model: example_model

        Component.onCompleted: {
            header_view.setSectionWidth(0, 100)
            header_view.setSectionWidth(1, 200)
            header_view.setSectionWidth(2, 300)
        }
    }*/

    QxTreeView {
        id: tree_view
        anchors.fill: parent
        //model: example_model
    }

   /* Column {

        spacing: 0

        QxHorizontalHeaderView {
            id: header_view

            delegate: Control {
                background:  Item {
                    Rectangle {
                        height: 1
                        width: parent.width
                        y: parent.height-1
                        color: 'black'
                    }
                }
                contentItem: Text {
                    padding: 8
                    text: sectionData.title
                }
            }

            handleDelegate: Item {
                Rectangle {
                    width: 1
                    height: parent.height
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: 'black'
                }
            }

            sections: [
                QxHeaderSection {
                    title: qsTr("General 1")
                    sections: [
                        QxHeaderSection { title: qsTr("First") },
                        QxHeaderSection {
                            title: qsTr("Second")
                            sections: [

                                QxHeaderSection {
                                    title: qsTr("Test")
                                    sections: [
                                        QxHeaderSection { title: qsTr("T (1)") },
                                        QxHeaderSection { title: qsTr("T (2)") },
                                        QxHeaderSection { title: qsTr("T (3)") }
                                    ]
                                },
                                QxHeaderSection { title: qsTr("R1") },
                                QxHeaderSection { title: qsTr("R3") }
                            ]
                        }
                    ]
                },
                QxHeaderSection {
                    title: qsTr("General 2")

                    sections: [
                        QxHeaderSection { title: qsTr("G1") },
                        QxHeaderSection { title: qsTr("G2") },
                        QxHeaderSection { title: qsTr("G3") }
                    ]
                },
                QxHeaderSection {
                    title: qsTr("General 3")
                }
            ]
        }
    }*/


    Component.onCompleted: {

        example_model.populate()
        tree_view.model = example_model
    }
}
