#pragma once

#include <QPointer>

#include "qxquickheadermodeladaptor.h"
#include "qxquickheaderviewtemplate.h"

class QxQuickTreeViewTemplate;
class QxQuickHorizontalHeaderViewTemplatePrivate;

class QxQuickHorizontalHeaderViewTemplate : public QxQuickHeaderViewTemplate {
    Q_OBJECT
    Q_DECLARE_PRIVATE(QxQuickHorizontalHeaderViewTemplate)

    Q_PROPERTY(qreal columnsWidth READ columnsWidth WRITE setColumnsWidth NOTIFY columnsWidthChanged)
    Q_PROPERTY(int rowCount READ rowCount NOTIFY rowCountChanged)
    Q_PROPERTY(int columnCount READ columnCount NOTIFY columnCountChanged)
    Q_PROPERTY(QxQuickHeaderModelAdaptor *adaptor READ adaptor NOTIFY adaptorChanged)
    Q_PROPERTY(QxQuickTreeViewTemplate *syncView READ syncView WRITE setSyncView NOTIFY syncViewChanged)

public:
    explicit QxQuickHorizontalHeaderViewTemplate(QQuickItem *parent = nullptr);
    ~QxQuickHorizontalHeaderViewTemplate();

    QxQuickHeaderModelAdaptor *adaptor() const;

    int rowCount() const;
    int columnCount() const;

    QxQuickTreeViewTemplate *syncView() const;
    void setSyncView(QxQuickTreeViewTemplate *newSyncView);

    qreal columnsWidth() const;
    void setColumnsWidth(qreal newDefaultColumnWidth);

    Q_INVOKABLE void setColumnWidth(int section, qreal width);

signals:
    void rowCountChanged();
    void columnCountChanged();
    void headerModelChanged();
    void syncViewChanged();
    void adaptorChanged();

    void columnsWidthChanged();

protected:
    void setupModel(QAbstractItemModel *new_model, QAbstractItemModel *old_model) override;
    void syncViewModelChanged();
    void setRowCount(int newRowCount);
    void setColumnCount(int newColumnCount);
    void setAdaptor(QxQuickHeaderModelAdaptor *adaptor);

private:
    QxQuickHorizontalHeaderViewTemplatePrivate *d_ptr;
};
