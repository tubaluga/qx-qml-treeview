#include "exampletreeitemmodel.h"

TreeItemModel::TreeItemModel(QObject *parent) :
    QAbstractItemModel(parent), m_rootItem(new Item())
{
}

QVariant TreeItemModel::data(const QModelIndex &index, int role) const
{
    auto item = indexToItem(index);

    switch (role) {
    case Qt::DisplayRole: {
        if (index.column() == 0) {
            return item->title;
        }
        else if (index.column() == 1) {
            return item->id.toString();
        }
    }
    case Title:
        return item->title;
    default:
        break;
    }

    return QVariant();
}

QModelIndex TreeItemModel::index(int row, int column, const QModelIndex &parent) const
{
    auto parent_item = indexToItem(parent);

    if (row > -1 && row < parent_item->children.size()) {
        auto item = parent_item->children.at(row);

        return createIndex(row, column, item.data());
    }

    return QModelIndex();
}

QModelIndex TreeItemModel::parent(const QModelIndex &index) const
{
    auto item = indexToItem(index);

    if (item->parent != nullptr) {
        return createIndex(0, 0, item->parent);
    }

    return QModelIndex();
}

int TreeItemModel::rowCount(const QModelIndex &parent) const
{
    auto item = indexToItem(parent);
    return item->children.size();
}

int TreeItemModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QHash<int, QByteArray> TreeItemModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles.insert(Title, QByteArrayLiteral("title"));

    return roles;
}

QVariant TreeItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal) {
        /*switch (section) {
        case 0:
            return QStringLiteral("Title");
        case 1:
            return QStringLiteral("UID");
        default:
            break;
        }*/

        return m_horizontalHeaderData[section].value(role);
    }

    return QAbstractItemModel::headerData(section, orientation, role);
}

bool TreeItemModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (orientation == Qt::Horizontal) {
        m_horizontalHeaderData[section].insert(role, value);

        emit headerDataChanged(orientation, section, section);

        return true;
    }

    return QAbstractItemModel::setHeaderData(section, orientation, value, role);
}

void TreeItemModel::populate()
{
    beginResetModel();

    auto root_element = m_rootItem->createChild("Root");

    root_element->createChild("First");
    root_element->createChild("Second");
    root_element->createChild("Theerd");

    endResetModel();

    setHeaderData(0, Qt::Horizontal, "Title", Qt::DisplayRole);
    setHeaderData(1, Qt::Horizontal, "UUID", Qt::DisplayRole);
    setHeaderData(2, Qt::Horizontal, "Test column title text", Qt::DisplayRole);
}

TreeItemModel::Item *TreeItemModel::indexToItem(const QModelIndex &index) const
{
    Item *item = m_rootItem.data();

    if (index.isValid()) {
        item = static_cast<Item *>(index.internalPointer());
    }

    return item;
}
