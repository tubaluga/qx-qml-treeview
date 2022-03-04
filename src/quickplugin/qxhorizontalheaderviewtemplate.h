#pragma once

#include <QPointer>

#include "qxheadermodeladaptor.h"
#include "qxheaderviewtemplate.h"
#include "qxtreeviewsectionmodeldata.h"

class QxTreeViewTemplate;
class QxHorizontalHeaderViewTemplatePrivate;

class QxHorizontalHeaderViewTemplate : public QxHeaderViewTemplate {
    Q_OBJECT
    Q_DECLARE_PRIVATE(QxHorizontalHeaderViewTemplate)

    Q_PROPERTY(QxHeaderModelAdaptor *adaptor READ adaptor CONSTANT)
    Q_PROPERTY(int rowCount READ rowCount NOTIFY rowCountChanged)
    Q_PROPERTY(int columnCount READ columnCount NOTIFY columnCountChanged)
    Q_PROPERTY(QxTreeViewTemplate *syncView READ syncView WRITE setSyncView NOTIFY syncViewChanged)

public:
    explicit QxHorizontalHeaderViewTemplate(QQuickItem *parent = nullptr);
    ~QxHorizontalHeaderViewTemplate();

    QxHeaderModelAdaptor *adaptor() const;

    int rowCount() const;
    int columnCount() const;

    QxTreeViewTemplate *syncView() const;
    void setSyncView(QxTreeViewTemplate *newSyncView);

signals:
    void rowCountChanged();
    void columnCountChanged();

    void headerModelChanged();

    void syncViewChanged();

protected:
    void invalidate() override;
    void setupModel(QAbstractItemModel *new_model, QAbstractItemModel *old_model) override;
    void syncViewModelChanged();
    void setRowCount(int newRowCount);
    void setColumnCount(int newColumnCount);

private:
    QxHorizontalHeaderViewTemplatePrivate *d_ptr;
};
