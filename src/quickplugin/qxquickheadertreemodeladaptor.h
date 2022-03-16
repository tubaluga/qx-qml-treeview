#pragma once

#include "qxquickheadermodeladaptor.h"

class QxQuickHeaderTreeModelAdaptor : public QxQuickHeaderModelAdaptor {
    Q_OBJECT
public:
    explicit QxQuickHeaderTreeModelAdaptor(QObject *parent = nullptr);

private:
    void createSections();
    void createSectionsByRow(QList<QxQuickHeaderSection *> &root_sections, QAbstractItemModel *model, const QModelIndex &index, QxQuickHeaderSection *parent_section);

protected:
    void onSourceModelChanged(QAbstractItemModel *new_model, QAbstractItemModel *old_model) override;

private:
    QMap<QModelIndex, QxQuickHeaderSection *> m_sectionCache;
    QVector<QMetaObject::Connection> m_connections;
};
