#pragma once

#include <QAbstractItemModel>
#include <QScopedPointer>
#include <QSharedPointer>
#include <QUuid>

class TreeItemModel : public QAbstractItemModel {
    Q_OBJECT

public:
    struct Item {
        QUuid id;
        QString title;
        Item *parent = nullptr;
        QList<QSharedPointer<Item>> children;

        Item *createChild(const QString &title)
        {
            QSharedPointer<Item> item(new Item);
            item->id     = QUuid::createUuid();
            item->title  = title;
            item->parent = this;
            children << item;
            return item.data();
        }
    };

public:
    enum Roles {
        Title = Qt::UserRole + 1
    };

    Q_ENUM(Roles)

    explicit TreeItemModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role) const override;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QHash<int, QByteArray> roleNames() const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

    Q_INVOKABLE void populate();

protected:
    Item *indexToItem(const QModelIndex &index) const;

private:
    QScopedPointer<Item> m_rootItem;
    QMap<int, QMap<int, QVariant>> m_horizontalHeaderData;
};
