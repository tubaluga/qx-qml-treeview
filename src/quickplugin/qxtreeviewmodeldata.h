#pragma once

#include <QModelIndex>
#include <QObject>
#include <QVariantMap>

class QxTreeViewModelData : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(QxTreeViewModelData)

    Q_PROPERTY(QPersistentModelIndex modelIndex READ modelIndex WRITE setModelIndex NOTIFY modelIndexChanged)
    Q_PROPERTY(QVariantMap modelData READ modelData NOTIFY modelDataChanged)

public:
    explicit QxTreeViewModelData(QObject *parent = nullptr);

    const QPersistentModelIndex &modelIndex() const;
    void setModelIndex(const QPersistentModelIndex &newModelIndex);

    const QVariantMap &modelData() const;

protected:
    void update();
    void setModelData(const QVariantMap &newModelData);

private:
    QPersistentModelIndex m_modelIndex;
    QVariantMap m_modelData;

signals:
    void modelIndexChanged();
    void modelDataChanged();
};

Q_DECLARE_METATYPE(QxTreeViewModelData *)
