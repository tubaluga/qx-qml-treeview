#pragma once

#include <QQuickItem>

#include "qxquicktreeviewtemplate.h"

class QxQuickTreeModelAdaptor;

class QxQuickTreeViewRowTemplate : public QQuickItem {
    Q_OBJECT
    Q_DISABLE_COPY(QxQuickTreeViewRowTemplate)

    Q_PROPERTY(QxQuickTreeViewTemplate *view READ view WRITE setView NOTIFY viewChanged)
    Q_PROPERTY(QxQuickTreeModelAdaptor *adaptor READ adaptor NOTIFY adaptorChanged)

public:
    explicit QxQuickTreeViewRowTemplate(QQuickItem *parent = nullptr);

    QxQuickTreeViewTemplate *view() const;
    void setView(QxQuickTreeViewTemplate *newView);

    QxQuickTreeModelAdaptor *adaptor() const;

private:
    void didModelChanged();

signals:
    void viewChanged();
    void adaptorChanged();

private:
    QPointer<QxQuickTreeViewTemplate> m_view;
    QMetaObject::Connection m_modelChangedConnection;
};

Q_DECLARE_METATYPE(QxQuickTreeViewRowTemplate *)
