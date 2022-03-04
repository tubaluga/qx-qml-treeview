#include "plugin.h"
#include "qxheadersection.h"
#include "qxhorizontalheaderviewtemplate.h"
#include "qxtreeviewcelldelegatetemplate.h"
#include "qxtreeviewrowdelegatetemplate.h"
#include "qxtreeviewsectionmodeldata.h"
#include "qxtreeviewtemplate.h"

#include <QtQml>

void QxTreeViewPlugin::registerTypes(const char *uri)
{
    qmlRegisterType(QUrl("qrc:/qx-qml-treeview/QxTreeView.qml"), uri, 1, 0, "QxTreeView");
    qmlRegisterType(QUrl("qrc:/qx-qml-treeview/QxHorizontalHeaderView.qml"), uri, 1, 0, "QxHorizontalHeaderView");
    qmlRegisterType<QxTreeViewTemplate>(uri, 1, 0, "QxTreeViewTemplate");
    qmlRegisterType<QxHorizontalHeaderViewTemplate>(uri, 1, 0, "QxHorizontalHeaderViewTemplate");
    qmlRegisterType<QxTreeViewRowDelegateTemplate>(uri, 1, 0, "QxTreeViewRowDelegateTemplate");
    qmlRegisterType<QxTreeViewCellDelegateTemplate>(uri, 1, 0, "QxTreeViewCellDelegateTemplate");
    qmlRegisterUncreatableType<QxTreeViewSectionModelData>(uri, 1, 0, "QxTreeViewSectionModelData", "This is the inner data class");
    qmlRegisterType<QxHeaderSection>(uri, 1, 0, "QxHeaderSection");
    qmlRegisterType<QxHeaderModelAdaptor>(uri, 1, 0, "QxHeaderModelAdaptor");
    qmlRegisterUncreatableType<QAbstractItemModel>(uri, 1, 0, "QAbstractItemModel", "");
}
