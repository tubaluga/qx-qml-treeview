import QtQuick 2.0
import QtQuick.Controls 2.0

import Qx.treeview 1.0

QxTreeViewCellDelegateTemplate {
    id: control

    implicitHeight: content.implicitHeight
    implicitWidth: content.implicitWidth

    Control {
        id: content

        padding: 6

        contentItem: Text {
            text: qsTr("text")
            wrapMode: Text.Wrap
        }
    }
}
