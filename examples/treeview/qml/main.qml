import QtQml 2.0
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

        Component.onCompleted: tree_view.expandAll()

        background: Rectangle {
            color: '#ffffff'
        }

        model: exampleModel
        delegate: Control {

            background: Rectangle {
                color: isHovered ? '#f9fafc' : 'transparent'
            }

            contentItem: RowLayout {
                Component {
                    id: decorator_component

                    Image {
                        id: decorator
                        source: 'qrc:/media/arrow_right_black_24dp.svg'

                        rotation: isExpanded ? 90 : 0
                        visible: hasChildren

                        Behavior on rotation {
                            NumberAnimation { duration: 100 }
                        }
                    }

                }

                Loader {
                    sourceComponent: columnIndex === 0 ? decorator_component : null
                    Layout.leftMargin: 12 * itemDepth
                    visible: sourceComponent
                }

                Text {
                    padding: 16
                    text: !!modelData.displayText ? modelData.displayText : ''
                    Layout.fillWidth: true
                    elide: Text.ElideRight
                    color: '#69707a'
                }
            }
        }

        header: QxHorizontalHeaderView {
            columnsWidth: tree_view.width / columnCount

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
