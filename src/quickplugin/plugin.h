#pragma once

#include <QQmlExtensionPlugin>

class QxTreeViewPlugin : public QQmlExtensionPlugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qx.treeview")

public:    
    void registerTypes(const char *uri) override;
};
