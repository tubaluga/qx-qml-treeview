#pragma once

#include "qxheadermodeladaptor.h"

class QxHeaderSyncViewModelAdaptor : public QxHeaderModelAdaptor {
    Q_OBJECT
public:
    explicit QxHeaderSyncViewModelAdaptor(QObject *parent = nullptr);

private:
    void createSections();

protected:
    void onSourceModelChanged(QAbstractItemModel *new_model, QAbstractItemModel *old_model) override;

private:
    QVector<QMetaObject::Connection> m_connections;
};
