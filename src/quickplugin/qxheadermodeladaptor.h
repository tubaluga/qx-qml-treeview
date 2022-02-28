#pragma once

#include <QAbstractListModel>
#include <QPointer>

#include "qxheadersection.h"

class QxHeaderModelAdaptor : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(QAbstractItemModel *source READ source WRITE setSource NOTIFY sourceChanged)

    struct Item {
        QString title;
        int span = 0;
    };

public:
    enum Role {
        Title         = Qt::DisplayRole,
        RowSpan       = Qt::UserRole + 1,
        ColSpan       = Qt::UserRole + 2,
        Column        = Qt::UserRole + 3,
        Row           = Qt::UserRole + 4,
        HeaderSection = Qt::UserRole + 5
    };

    Q_ENUM(Role)

    explicit QxHeaderModelAdaptor(QObject *parent = nullptr);

    QAbstractItemModel *source() const;
    void setSource(QAbstractItemModel *newSource);

    void setSections(const QList<QxHeaderSection *> &newSections);

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void invalidate();

    QxHeaderSection *root() const;
    void setRoot(QxHeaderSection *newRoot);

protected:
    void rebuildModel();
    int sectionColumn(QxHeaderSection *section) const;

signals:
    void sourceChanged();

private:
    QPointer<QAbstractItemModel> m_source;
    QxHeaderSection *m_root;
    QList<QxHeaderSection *> m_sections;
};
