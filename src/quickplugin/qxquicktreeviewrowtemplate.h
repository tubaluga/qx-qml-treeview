#pragma once

#include <QQuickItem>

#include "qxquicktreeviewtemplate.h"

class QxQuickTreeViewRowTemplate : public QQuickItem {
    Q_OBJECT
    Q_DISABLE_COPY(QxQuickTreeViewRowTemplate)

    Q_PROPERTY(QxQuickTreeViewTemplate *view READ view WRITE setView NOTIFY viewChanged)

public:
    explicit QxQuickTreeViewRowTemplate(QQuickItem *parent = nullptr);

    QxQuickTreeViewTemplate *view() const;
    void setView(QxQuickTreeViewTemplate *newView);

private:
    void didModelChanged();

signals:
    void viewChanged();

private:
    QPointer<QxQuickTreeViewTemplate> m_view;
    QMetaObject::Connection m_modelChangedConnection;
};

Q_DECLARE_METATYPE(QxQuickTreeViewRowTemplate *)
