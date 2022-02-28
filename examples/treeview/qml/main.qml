import QtQuick 2.0
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

    QxHorizontalHeaderView {

        sections: [
            QxHeaderSection {
                title: qsTr("General fdsfd fsdfsd fds")
                sections: [
                    QxHeaderSection { title: qsTr("First") },
                    QxHeaderSection { title: qsTr("Second") }
                ]
            }/*,
            QxHeaderSection {
                title: qsTr("General 1")

                sections: [
                    QxHeaderSection { title: qsTr("1") },
                    QxHeaderSection { title: qsTr("2") },
                    QxHeaderSection { title: qsTr("3") }
                ]
            },
            QxHeaderSection {
                title: qsTr("General 2")
            }*/
        ]
    }


    Component.onCompleted: example_model.populate()
}
