#pragma once

#include "qxheadermodeladaptor.h"

class QxHeaderTreeModelAdaptor : public QxHeaderModelAdaptor {
    Q_OBJECT
public:
    explicit QxHeaderTreeModelAdaptor(QObject *parent = nullptr);

private:
    void createSections();
    void createSectionsByRow(QList<QxHeaderSection *> &root_sections, QAbstractItemModel *model, const QModelIndex &index, QxHeaderSection *parent_section);

protected:
    void onSourceModelChanged(QAbstractItemModel *new_model, QAbstractItemModel *old_model) override;

private:
    QMap<QModelIndex, QxHeaderSection *> m_sectionCache;
    QVector<QMetaObject::Connection> m_connections;
};
