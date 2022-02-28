#pragma once

#include "qxtreeviewtemplate.h"

class QxTreeViewRowDelegateTemplate : public QQuickItem {
    Q_OBJECT
    Q_DISABLE_COPY(QxTreeViewRowDelegateTemplate)

    Q_PROPERTY(QxTreeViewTemplate *view READ view WRITE setView NOTIFY viewChanged)
public:
    explicit QxTreeViewRowDelegateTemplate(QQuickItem *parent = nullptr);

    QxTreeViewTemplate *view() const;
    void setView(QxTreeViewTemplate *newView);

signals:
    void viewChanged();

private:
    QPointer<QxTreeViewTemplate> m_view;
};

Q_DECLARE_METATYPE(QxTreeViewRowDelegateTemplate *)
