#pragma once

#include "qxquickheadermodeladaptor.h"

class QxQuickHeaderSyncViewModelAdaptor : public QxQuickHeaderModelAdaptor {
    Q_OBJECT
public:
    explicit QxQuickHeaderSyncViewModelAdaptor(QObject *parent = nullptr);

private:
    void createSections();

protected:
    void onSourceModelChanged(QAbstractItemModel *new_model, QAbstractItemModel *old_model) override;

private:
    QVector<QMetaObject::Connection> m_connections;
};
