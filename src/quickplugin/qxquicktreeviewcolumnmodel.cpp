#include "qxquicktreeviewcolumnmodel.h"

QxQuickTreeViewColumnModel::QxQuickTreeViewColumnModel(QObject *parent) :
    QAbstractListModel{ parent }
{
}

int QxQuickTreeViewColumnModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_items.size();
}

QVariant QxQuickTreeViewColumnModel::data(const QModelIndex &index, int role) const
{
    if (index.row() > -1 && index.row() < m_items.size()) {
        if (role == Qt::DisplayRole) {
            return m_items.at(index.row());
        }
    }

    return QVariant();
}

QHash<int, QByteArray> QxQuickTreeViewColumnModel::roleNames() const
{
    QHash<int, QByteArray> names;

    names.insert(Qt::DisplayRole, QByteArrayLiteral("column_width"));

    return names;
}

void QxQuickTreeViewColumnModel::setItems(const QList<qreal> &items)
{
    beginResetModel();

    m_items = items;

    endResetModel();
}

void QxQuickTreeViewColumnModel::setColumnWidth(int index, qreal width)
{
    if (index > -1 && index < m_items.size()) {
        m_items[index] = width;

        QModelIndex model_index = this->index(index, 0);

        emit dataChanged(model_index, model_index, { Qt::DisplayRole });
    }
}

const QList<qreal> &QxQuickTreeViewColumnModel::items() const
{
    return m_items;
}
