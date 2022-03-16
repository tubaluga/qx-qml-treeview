#pragma once

#include <QAbstractItemModel>
#include <QPointer>
#include <QQuickItem>

#include "qxquicktreeviewcolumnmodel.h"
#include "qxtreeviewsectionmodeldata.h"

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

    Q_INVOKABLE void setColumnWidth(int column, qreal width);

    QxQuickTreeViewColumnModel *columnModel() const;

    QxQuickTreeModelAdaptor *adaptor() const;

protected:
    void invalidate();

private:
    QxQuickTreeModelAdaptor *m_adaptor        = nullptr;
    QxQuickTreeViewColumnModel *m_columnModel = nullptr;

signals:
    void modelChanged();
};

Q_DECLARE_METATYPE(QxQuickTreeViewTemplate *)
