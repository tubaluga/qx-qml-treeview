#include "qxquicktreeviewtemplate.h"
#include "qxquicktreemodeladaptor.h"

QxQuickTreeViewTemplate::QxQuickTreeViewTemplate(QQuickItem *parent) :
    QQuickItem{ parent }, m_columnModel(new QxQuickTreeViewColumnModel(this))
{
    m_adaptor = new QxQuickTreeModelAdaptor(this);
}

QAbstractItemModel *QxQuickTreeViewTemplate::model() const
{
    return m_adaptor->model();
}

void QxQuickTreeViewTemplate::setModel(QAbstractItemModel *newModel)
{
    if (m_adaptor->model() == newModel) {
        return;
    }

    if (m_adaptor->model()) {
        disconnect(m_adaptor->model(), &QAbstractItemModel::modelReset, this, &QxQuickTreeViewTemplate::invalidate);
    }

    m_adaptor->setModel(newModel);

    if (m_adaptor->model()) {
        connect(m_adaptor->model(), &QAbstractItemModel::modelReset, this, &QxQuickTreeViewTemplate::invalidate);
    }

    invalidate();

    emit modelChanged();
}

void QxQuickTreeViewTemplate::setColumnWidth(int column, qreal width)
{    
    m_columnModel->setColumnWidth(column, width);
}

void QxQuickTreeViewTemplate::invalidate()
{
    QList<qreal> column_items;

    if (m_adaptor->model()) {
        int total_column_count = m_adaptor->model()->columnCount();

        for (int i = 0; i < total_column_count; ++i) {
            column_items.append(-1.);
        }
    }

    m_columnModel->setItems(column_items);
}

QxQuickTreeModelAdaptor *QxQuickTreeViewTemplate::adaptor() const
{
    return m_adaptor;
}

QxQuickTreeViewColumnModel *QxQuickTreeViewTemplate::columnModel() const
{
    return m_columnModel;
}
