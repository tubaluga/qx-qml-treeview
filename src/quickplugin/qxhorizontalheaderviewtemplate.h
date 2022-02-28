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

    Q_INTERFACES(QQmlParserStatus)
public:
    explicit QxHorizontalHeaderViewTemplate(QQuickItem *parent = nullptr);

    void componentComplete() override;

    QxHeaderModelAdaptor *adaptor() const;

protected:
    void invalidate() override;
    /*void invalidateHeaderRowHeigh(int row);
    void invalidateHeaderHeight();
    void headerDataChanged(Qt::Orientation orientation, int first, int last);
    void createTreeHeaderSection(int &position, const QModelIndex &index, Section *parent_section = nullptr);*/

private:
    QxHeaderModelAdaptor *m_adaptor = nullptr;
    QxHorizontalHeaderViewTemplatePrivate *d_ptr;
    bool m_treeMode = true;
};
