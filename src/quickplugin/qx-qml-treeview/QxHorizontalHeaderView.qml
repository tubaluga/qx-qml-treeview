import QtQuick 2.11
import QtQuick.Layouts 1.2

import Qx.treeview 1.0

QxHorizontalHeaderViewTemplate {
    id: control

    property Component delegate
    property Component handleDelegate
    property alias background: background_loader.sourceComponent

    implicitHeight: grid_layout.implicitHeight
    implicitWidth: grid_layout.implicitWidth

    Loader {
        id: background_loader
        anchors.fill: parent
    }

    GridLayout {
        id: grid_layout

        rows: control.rowCount
        columns: control.columnCount

        flow: GridLayout.LeftToRight

        columnSpacing: 0
        rowSpacing: 0

        Repeater {
            id: repeater
            model: control.adaptor
            delegate: Item {
                id: delegate_item

                implicitWidth: adaptor_section.width
                implicitHeight: delegate_loader.implicitHeight

                Layout.row: adaptor_section.row
                Layout.column: adaptor_section.column
                Layout.columnSpan: adaptor_section.columnSpan
                Layout.rowSpan: adaptor_section.rowSpan
                Layout.fillWidth: true
                Layout.fillHeight: true


                Loader {
                    id: delegate_loader
                    anchors.fill: parent
                    sourceComponent: control.delegate

                    property QtObject sectionData: adaptor_section
                    property var modelData: model

                    onLoaded: {
                        if (adaptor_section.width === -1) {
                            adaptor_section.width = Math.min(100, delegate_loader.item.implicitWidth)
                        }
                    }
                }

                MouseArea {
                    property int offset: 0
                    readonly property int minimumSize: 25

                    width: 16
                    height: parent.height
                    anchors.right: parent.right
                    anchors.rightMargin: -width / 2
                    cursorShape: Qt.SizeHorCursor
                    preventStealing: true

                    onPositionChanged: control.adaptor.addSectionWidthOffset(adaptor_section, (mouseX - offset))
                    onPressedChanged: if (pressed) offset=mouseX

                    Loader {
                        anchors.fill: parent
                        sourceComponent: control.handleDelegate
                    }
                }
            }
        }
    }
}
