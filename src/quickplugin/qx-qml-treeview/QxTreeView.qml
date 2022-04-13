import QtQuick 2.11
import QtQuick.Controls 2.0

import Qx.treeview 1.0

QxTreeViewTemplate {
    id: root

    property Component delegate
    property alias header: list_view.header    
    property alias background: background_loader.sourceComponent

    Loader {
        id: background_loader
        anchors.fill: parent
    }

    ListView {
        id: list_view
        anchors.fill: parent

        flickableDirection: Flickable.HorizontalAndVerticalFlick
        boundsBehavior: Flickable.StopAtBounds

        headerPositioning: ListView.OverlayHeader

        model: adaptor
        delegate: QxTreeViewRow {

            view: root
            cellDelegate: root.delegate

            onImplicitWidthChanged: list_view.contentWidth = implicitWidth
        }

        ScrollBar.horizontal: ScrollBar {
        }
    }
}
