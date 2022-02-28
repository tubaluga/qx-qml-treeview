import QtQuick 2.0

import Qx.treeview 1.0

QxTreeViewRowDelegateTemplate {
    id: control

    property int columnCount: 1
    property alias cellDelegate: cell_repeater.delegate

    Image {
        id: decorator
        x: 24 * _q_TreeView_ItemDepth
        anchors.verticalCenter: parent.verticalCenter

        source: 'qrc:/media/arrow_right_black_24dp.svg'

        rotation: _q_TreeView_ItemExpanded ? 90 : 0
        visible: _q_TreeView_HasChildren

        Behavior on rotation {
            NumberAnimation { duration: 100 }
        }
    }

    Row {
        anchors.left: decorator.right
        anchors.verticalCenter: parent.verticalCenter

        Repeater {
            id: cell_repeater
            model: control.columnCount
            delegate: QxTreeViewCellDelegate {
                property QxTreeViewSectionModelData sectionModelData: control.view.sectionData(index)
                width: !!sectionModelData ? sectionModelData.width : 150
            }
        }
    }

    MouseArea {
        anchors.fill: parent
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
