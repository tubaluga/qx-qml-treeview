#pragma once

#include <QAbstractListModel>

class QxQuickTreeViewColumnModel : public QAbstractListModel {
    Q_OBJECT
public:
    explicit QxQuickTreeViewColumnModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void setItems(const QList<qreal> &items);
    const QList<qreal> &items() const;

    void setColumnWidth(int index, qreal width);

private:
    QList<qreal> m_items;
};

Q_DECLARE_METATYPE(QxQuickTreeViewColumnModel *)
