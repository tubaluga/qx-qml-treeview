import QtQuick 2.11
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.2

import Qx.treeview 1.0

import Example 1.0

ApplicationWindow {    
    width: 1024
    height: 768

    title: Qt.application.displayName
    visible: true

    Component {
        id: header_delegate_component

        Control {
            background:  Rectangle {
                color: 'white'
                border.width: 1
                border.color: 'black'
                Rectangle {
                    height: 1
                    width: parent.width
                    y: parent.height-1
                    color: 'black'
                }
            }
            contentItem: Text {
                padding: 8
                text: !!sectionData ? sectionData.title : ''
                elide: Text.ElideRight
            }
        }
    }

    Component {
        id: handle_delegate_component
        Item {
            Rectangle {
                width: 1
                height: parent.height
                anchors.horizontalCenter: parent.horizontalCenter
                color: 'black'
            }
        }
    }

    FileSystemModel {
        id: file_system_model
    }

    ExampleTreeItemModel {
        id: example_model
    }

    Component.onCompleted: example_model.populate()

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 16
        spacing: 8

        RowLayout {
            spacing: 8

            Button {
                text: 'Populate'
                onClicked: {
                    example_model.populate()
                }
            }

            Button {
                text: 'Test'
                onClicked: example_model.test()
            }
        }



        QxTreeView {
            id: tree_view

            Layout.fillHeight: true
            Layout.fillWidth: true

            clip: true

            background: Rectangle {
                color: 'orange'
            }

            model: example_model
            delegate: Rectangle {
                implicitHeight: text_item.implicitHeight
                implicitWidth: text_item.implicitWidth

                color: isHovered ? 'gray' : 'transparent'

                Text {
                    id: text_item
                    padding: 16
                    text: !!modelData.displayText ? modelData.displayText : ''
                    width: parent.width
                    elide: Text.ElideRight
                }
            }

            header: QxHorizontalHeaderView {
                id: header_view
                delegate: header_delegate_component
                syncView: tree_view
                model: example_model
                defaultColumnWidth: tree_view.width / columnCount
                handleDelegate: handle_delegate_component
            }
        }
    }
}
