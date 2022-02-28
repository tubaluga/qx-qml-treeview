#pragma once

#include <QQuickItem>

class QxTreeViewCellDelegateTemplate : public QQuickItem {
    Q_OBJECT
    Q_DISABLE_COPY(QxTreeViewCellDelegateTemplate)
public:
    explicit QxTreeViewCellDelegateTemplate(QQuickItem *parent = nullptr);
};

Q_DECLARE_METATYPE(QxTreeViewCellDelegateTemplate *)
