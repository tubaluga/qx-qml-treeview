import QtQuick 2.11
import QtQuick.Layouts 1.2

import Qx.treeview 1.0

QxHorizontalHeaderViewTemplate {
    id: control

    /* property Component delegate: Text {
        anchors.fill: parent
        verticalAlignment: Qt.AlignVCenter
        horizontalAlignment: Qt.AlignHCenter

        wrapMode: Text.Wrap

        text: sectionModelData.text
    }

    property Component dragHandleDelegate: Item {
        Rectangle {
            x: parent.width - 1
            width: 2
            height: parent.height

            color: '#040404'
        }
    }

    sectionDelegate: Item {
        id: delegate

        implicitHeight: content_loader.implicitHeight
        implicitWidth: content_loader.implicitWidth

        Rectangle {
            anchors.fill: parent
            color: 'orange'

        }

        Loader {
            id: content_loader
            anchors.fill: parent

            property QtObject sectionModelData: sectionData

            sourceComponent: control.delegate
        }

        Loader {
            anchors.fill: parent
            sourceComponent: control.dragHandleDelegate
        }

        MouseArea {
            property int offset: 0
            readonly property int minimumSize: 20

            width: 16
            height: parent.height
            anchors.right: parent.right
            anchors.rightMargin: -width / 2
            cursorShape: Qt.SizeHorCursor
            preventStealing: true

            onPositionChanged: {
                var newHeaderWidth = headerView.sectionWidth(index) + (mouseX - offset)
                headerView.setSectionWidth(index, Math.max(minimumSize, newHeaderWidth))

            }

            onPressedChanged: if (pressed) offset=mouseX
        }
    }*/

    GridLayout {
        rows: 3
        columns: 10

        Repeater {
            model: control.adaptor
            delegate: Item {
                id: delegate_item

                implicitWidth: text_view.implicitWidth
                implicitHeight: text_view.implicitHeight

                Text {
                    id: text_view

                    text: adaptor_title
                    Layout.row: adaptor_section.row
                    Layout.column: adaptor_section.column
                    Layout.columnSpan: adaptor_section.columnSpan
                    Layout.rowSpan: adaptor_section.rowSpan

                    padding: 8

                    Rectangle {
                        anchors.fill: parent

                        color: 'transparent'
                        border.width: 1
                        border.color: 'black'
                    }

                    MouseArea {
                        property int offset: 0
                        readonly property int minimumSize: 20

                        width: 16
                        height: parent.height
                        anchors.right: parent.right
                        anchors.rightMargin: -width / 2
                        cursorShape: Qt.SizeHorCursor
                        preventStealing: true

                        onPositionChanged: {
                            var newHeaderWidth = delegate_item.width + (mouseX - offset)
                            delegate_item.implicitWidth = Math.max(minimumSize, newHeaderWidth)
                            //headerView.setSectionWidth(index, Math.max(minimumSize, newHeaderWidth))

                        }

                        onPressedChanged: if (pressed) offset=mouseX
                    }
                }
            }
        }

        Component.onCompleted: {
            console.log("ready")
            //control.adaptor.invalidate()
        }
    }
}
