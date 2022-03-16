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

    ExampleTreeItemModel {
        id: example_model

        Component.onCompleted: example_model.populate()
    }

    QxTreeView {
        id: tree_view

        anchors.fill: parent
        anchors.margins: 16

        clip: true

        background: Rectangle {
            color: '#ffffff'
        }

        model: exampleModel
        delegate: Control {

            background: Rectangle {
                color: isHovered ? '#f9fafc' : 'transparent'
            }

            contentItem: Text {
                padding: 16
                text: !!modelData.displayText ? modelData.displayText : ''
                width: parent.width
                elide: Text.ElideRight
                color: '#69707a'
            }
        }

        header: QxHorizontalHeaderView {
            columnsWidth: control.width / columnCount

            width: tree_view.width

            background: Rectangle {
                color: '#f9fafc'
                opacity: 0.4
            }

            delegate: Control {
                background: Rectangle {
                    color: '#f9fafc'
                }
                contentItem: Text {
                    padding: 8
                    text: !!sectionData ? sectionData.title : ''
                    elide: Text.ElideRight
                    color: '#697283'
                    font.bold: true
                }
            }
            syncView: tree_view
            model: example_model
            handleDelegate: Item {
                Rectangle {
                    width: 1
                    height: parent.height - 12
                    anchors.centerIn: parent
                    color: '#eeeff3'
                }
            }
        }
    }
}
