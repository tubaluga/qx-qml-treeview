#include "plugin.h"

#include <QtQml>

void QxTreeViewPlugin::registerTypes(const char *uri)
{
    qmlRegisterType(QUrl("qrc:/qx-qml-treeview/TreeView.qml"), uri, 1, 0, "TreeView");
}
