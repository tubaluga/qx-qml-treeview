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

    Q_PROPERTY(QxHeaderModelAdaptor *adaptor READ adaptor NOTIFY adaptorChanged)
    Q_PROPERTY(int rowCount READ rowCount NOTIFY rowCountChanged)
    Q_PROPERTY(int columnCount READ columnCount NOTIFY columnCountChanged)
    Q_PROPERTY(QxTreeViewTemplate *syncView READ syncView WRITE setSyncView NOTIFY syncViewChanged)
    Q_PROPERTY(qreal defaultColumnWidth READ defaultColumnWidth WRITE setDefaultColumnWidth NOTIFY defaultColumnWidthChanged)

public:
    explicit QxHorizontalHeaderViewTemplate(QQuickItem *parent = nullptr);
    ~QxHorizontalHeaderViewTemplate();

    QxHeaderModelAdaptor *adaptor() const;

    int rowCount() const;
    int columnCount() const;

    QxTreeViewTemplate *syncView() const;
    void setSyncView(QxTreeViewTemplate *newSyncView);

    qreal defaultColumnWidth() const;
    void setDefaultColumnWidth(qreal newDefaultColumnWidth);

signals:
    void rowCountChanged();
    void columnCountChanged();
    void headerModelChanged();
    void syncViewChanged();
    void adaptorChanged();

    void defaultColumnWidthChanged();

protected:
    void setupModel(QAbstractItemModel *new_model, QAbstractItemModel *old_model) override;
    void syncViewModelChanged();
    void setRowCount(int newRowCount);
    void setColumnCount(int newColumnCount);
    void setAdaptor(QxHeaderModelAdaptor *adaptor);

private:
    QxHorizontalHeaderViewTemplatePrivate *d_ptr;
};
