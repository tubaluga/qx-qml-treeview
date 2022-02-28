import QtQuick 2.0
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

        header: QxHorisontalHeaderView {
            model: root.model
            width: ListView.view.width
            height: 40
        }
    }
}
