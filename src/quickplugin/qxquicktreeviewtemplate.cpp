#include "qxquicktreeviewtemplate.h"
#include "qxquicktreemodeladaptor.h"

#include <QDebug>

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

    emit requestResizeColumns();
}

QxQuickTreeModelAdaptor *QxQuickTreeViewTemplate::adaptor() const
{
    return m_adaptor;
}

void QxQuickTreeViewTemplate::expand(int row)
{
    m_adaptor->expand(m_adaptor->mapRowToModelIndex(row));
}

void QxQuickTreeViewTemplate::collapse(int row)
{
    m_adaptor->collapse(m_adaptor->mapRowToModelIndex(row));
}

bool QxQuickTreeViewTemplate::isExpanded(int row) const
{
    return m_adaptor->isExpanded(m_adaptor->mapRowToModelIndex(row));
}

void QxQuickTreeViewTemplate::expandAll()
{
    if (!m_adaptor->model()) {
        return;
    }

    std::function<void(const QModelIndex &)> expand_function = [this, &expand_function](const QModelIndex &parent) {
        for (int row = 0; row < m_adaptor->model()->rowCount(parent); ++row) {
            auto model_index = m_adaptor->model()->index(row, 0, parent);

            if (model_index.isValid()) {
                m_adaptor->expand(model_index);
                expand_function(model_index);
            }
        }
    };

    expand_function(QModelIndex());
}

QxQuickTreeViewColumnModel *QxQuickTreeViewTemplate::columnModel() const
{
    return m_columnModel;
}
