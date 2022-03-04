import QtQuick 2.11
import QtQuick.Controls 2.2 as QtControlV2
import QtQuick.Controls 1.4
import QtQuick.Controls.Private 1.0

import Qx.treeview 1.0

QxTreeViewTemplate {
    id: root

    TreeModelAdaptor {
        id: model_adaptor
        model: root.model
    }

    ListView {
        id: list_view
        anchors.fill: parent

        model: model_adaptor
        delegate: QxTreeViewRowDelegate {
            width: ListView.view.width
            height: 32
            columnCount: 2
            view: root
        }

        /*header: QxHorizontalHeaderView {
            model: root.model
            width: ListView.view.width
            height: 40

            handleDelegate: Item {
                Rectangle {
                    width: 1
                    height: parent.height - 8
                    anchors.centerIn: parent
                    color: 'black'
                }
            }

            delegate: QtControlV2.Control {
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

        }*/
    }
}
