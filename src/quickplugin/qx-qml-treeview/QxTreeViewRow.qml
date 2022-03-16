import QtQuick 2.0
import QtQuick.Controls 2.0

import Qx.treeview 1.0

QxTreeViewRowDelegateTemplate {
    id: control

    implicitHeight: content.implicitHeight
    implicitWidth: content.implicitWidth

    property Component cellDelegate

    Control {
        id: content
        contentItem: Row {

            spacing: 0

            anchors.verticalCenter: parent.verticalCenter

            Repeater {
                id: cell_repeater
                model: control.view.columnModel

                property int row_index: index

                delegate: QxTreeViewCellDelegateTemplate {
                    id: cell_item

                    QxTreeViewModelData {
                        id: model_data
                        modelIndex: control.view.adaptor.mapRowToModelIndex(cell_repeater.row_index, index)
                    }                  

                    width: {

                        if (column_width > -1) {
                            return column_width
                        }

                        return implicitWidth
                    }

                    implicitWidth: !!loader.item ? loader.item.implicitWidth : 0
                    implicitHeight: !!loader.item ? loader.item.implicitHeight : 0

                    Loader {
                        id: loader
                        anchors.fill: parent

                        property var modelData: model_data.modelData
                        property bool hasChildren: _q_TreeView_HasChildren
                        property bool isExpanded: _q_TreeView_ItemExpanded
                        property int itemDepth: _q_TreeView_ItemDepth
                        property int columnIndex: index
                        property int isHovered: content.hovered

                        sourceComponent: control.cellDelegate
                    }
                }
            }
        }
    }

    MouseArea {
        id: mouse_area
        anchors.fill: parent
        propagateComposedEvents: true
        onClicked: {

            var adaptor = control.view.adaptor

            var model_index = adaptor.mapRowToModelIndex(index)

            if (adaptor.isExpanded(model_index)) {
                adaptor.collapse(model_index)
            } else {
                adaptor.expand(model_index)
            }
        }
    }
}
