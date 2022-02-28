#pragma once

#include <QAbstractItemModel>
#include <QPointer>
#include <QQuickItem>

#include "qxtreeviewsectionmodeldata.h"

class QxTreeViewTemplate : public QQuickItem {
    Q_OBJECT
    Q_DISABLE_COPY(QxTreeViewTemplate)

    Q_PROPERTY(QAbstractItemModel *model READ model WRITE setModel NOTIFY modelChanged)
public:
    explicit QxTreeViewTemplate(QQuickItem *parent = nullptr);

    QAbstractItemModel *model() const;
    void setModel(QAbstractItemModel *newModel);

    Q_INVOKABLE QxTreeViewSectionModelData *sectionData(int section) const;

private:
    void modelHeaderDataChanged(Qt::Orientation orientation, int first, int last);

protected:
    void invalidate();

private:
    QPointer<QAbstractItemModel> m_model;
    QList<QxTreeViewSectionModelData *> m_sectionModels;

signals:
    void modelChanged();
};

Q_DECLARE_METATYPE(QxTreeViewTemplate *)
