import QtQuick 2.0

import Qx.treeview 1.0

QxTreeViewRowDelegateTemplate {
    id: control

    implicitHeight: column_layout.implicitHeight
    implicitWidth: column_layout.implicitWidth

    property Component cellDelegate

    Row {
        id: column_layout
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter

        Repeater {
            id: cell_repeater
            model: control.columnCount

            property int row_index: index

            delegate: QxTreeViewCell {
                id: cell_item

                QxTreeViewModelData {
                    id: model_data
                    modelIndex: model_adaptor.mapRowToModelIndex(cell_repeater.row_index, index)
                }

                property QxTreeViewSectionModelData section: control.view.sectionData(index)

                width: !!cell_item.section ? cell_item.section.width : 150
                implicitHeight: !!loader.item ? loader.item.implicitHeight : 0

                Loader {
                    id: loader
                    anchors.fill: parent

                    property var modelData: model_data.modelData
                    property bool hasChildren: _q_TreeView_HasChildren
                    property bool isExpanded: _q_TreeView_ItemExpanded
                    property int itemDepth: _q_TreeView_ItemDepth
                    property int columnIndex: index
                    property int isHovered: mouse_area.containsMouse

                    sourceComponent: control.cellDelegate
                }
            }
        }
    }

    MouseArea {
        id: mouse_area
        anchors.fill: parent
        hoverEnabled: true
        propagateComposedEvents: true
        onClicked: {

            var model_index = model_adaptor.mapRowToModelIndex(index)

            if (model_adaptor.isExpanded(model_index)) {
                model_adaptor.collapse(model_index)
            } else {
                model_adaptor.expand(model_index)
            }
        }
    }


}
