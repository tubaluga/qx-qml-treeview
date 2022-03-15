import QtQuick 2.11
import QtQuick.Controls 2.0

import Qx.treeview 1.0

QxTreeViewTemplate {
    id: root

    property Component delegate
    property alias header: list_view.header    
    property alias background: background_loader.sourceComponent

    function expand(index) {
        var model_index = model_adaptor.mapRowToModelIndex(index)
        model_adaptor.expand(model_index)
    }

    function collapse(index) {
        var model_index = model_adaptor.mapRowToModelIndex(index)
        model_adaptor.collapse(model_index)
    }

    function isExpanded(index) {
        var model_index = model_adaptor.mapRowToModelIndex(index)
        return model_adaptor.isExpanded(model_index)
    }

    QxQuickTreeModelAdaptor {
        id: model_adaptor
        model: root.model
    }

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

        model: model_adaptor
        delegate: QxTreeViewRow {

            view: root
            cellDelegate: root.delegate

            onImplicitWidthChanged: list_view.contentWidth = implicitWidth
        }

        /*ScrollBar.vertical: ScrollBar {
        }*/

        ScrollBar.horizontal: ScrollBar {
        }
    }
}
