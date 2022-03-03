#pragma once

#include <QAbstractItemModel>
#include <QPointer>
#include <QQmlParserStatus>

#include "qxheadermodeladaptor.h"
#include "qxheaderviewtemplate.h"
#include "qxtreeviewsectionmodeldata.h"

class QxHorizontalHeaderViewTemplatePrivate;

class QxHorizontalHeaderViewTemplate : public QxHeaderViewTemplate {
    Q_OBJECT
    Q_DECLARE_PRIVATE(QxHorizontalHeaderViewTemplate)

    Q_PROPERTY(QxHeaderModelAdaptor *adaptor READ adaptor CONSTANT)
    Q_PROPERTY(int rowCount READ rowCount NOTIFY rowCountChanged)
    Q_PROPERTY(int columnCount READ columnCount NOTIFY columnCountChanged)

    Q_INTERFACES(QQmlParserStatus)
public:
    explicit QxHorizontalHeaderViewTemplate(QQuickItem *parent = nullptr);
    ~QxHorizontalHeaderViewTemplate();

    QxHeaderModelAdaptor *adaptor() const;

    int rowCount() const;
    int columnCount() const;

signals:
    void rowCountChanged();
    void columnCountChanged();

protected:
    void invalidate() override;
    void setupModel(QAbstractItemModel *new_model, QAbstractItemModel *old_model);
    void setRowCount(int newRowCount);
    void setColumnCount(int newColumnCount);

private:
    QxHorizontalHeaderViewTemplatePrivate *d_ptr;
};
