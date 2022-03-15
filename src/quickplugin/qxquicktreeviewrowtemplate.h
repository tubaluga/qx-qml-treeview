#pragma once

#include <QQuickItem>

#include "qxtreeviewtemplate.h"

class QxQuickTreeViewRowTemplate : public QQuickItem {
    Q_OBJECT
    Q_DISABLE_COPY(QxQuickTreeViewRowTemplate)

    Q_PROPERTY(QxTreeViewTemplate *view READ view WRITE setView NOTIFY viewChanged)
    Q_PROPERTY(int columnCount READ columnCount NOTIFY columnCountChanged)

public:
    explicit QxQuickTreeViewRowTemplate(QQuickItem *parent = nullptr);

    QxTreeViewTemplate *view() const;
    void setView(QxTreeViewTemplate *newView);

    int columnCount() const;

private:
    void didModelChanged();

signals:
    void viewChanged();
    void columnCountChanged();

private:
    QPointer<QxTreeViewTemplate> m_view;
    QMetaObject::Connection m_modelChangedConnection;
};

Q_DECLARE_METATYPE(QxQuickTreeViewRowTemplate *)
