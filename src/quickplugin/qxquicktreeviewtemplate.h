#pragma once

#include <QAbstractItemModel>
#include <QPointer>
#include <QQuickItem>

#include "qxquicktreeviewcolumnmodel.h"

class QxQuickTreeModelAdaptor;

class QxQuickTreeViewTemplate : public QQuickItem {
    Q_OBJECT
    Q_DISABLE_COPY(QxQuickTreeViewTemplate)

    Q_PROPERTY(QxQuickTreeModelAdaptor *adaptor READ adaptor CONSTANT)
    Q_PROPERTY(QAbstractItemModel *model READ model WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(QxQuickTreeViewColumnModel *columnModel READ columnModel CONSTANT)

public:
    explicit QxQuickTreeViewTemplate(QQuickItem *parent = nullptr);

    QAbstractItemModel *model() const;
    void setModel(QAbstractItemModel *newModel);

    void setColumnWidth(int column, qreal width);

    QxQuickTreeViewColumnModel *columnModel() const;

    QxQuickTreeModelAdaptor *adaptor() const;

    Q_INVOKABLE void expand(int row);
    Q_INVOKABLE void expandAll();
    Q_INVOKABLE bool isExpanded(int row) const;

    Q_INVOKABLE void collapse(int row);

protected:
    void invalidate();

private:
    QxQuickTreeModelAdaptor *m_adaptor        = nullptr;
    QxQuickTreeViewColumnModel *m_columnModel = nullptr;

signals:
    void modelChanged();
    void requestResizeColumns();
};

Q_DECLARE_METATYPE(QxQuickTreeViewTemplate *)
