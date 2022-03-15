#pragma once

#include <QAbstractListModel>
#include <QPointer>

#include "qxheadersection.h"

class QxHeaderModelAdaptor : public QAbstractListModel {
    Q_OBJECT

    Q_PROPERTY(QAbstractItemModel *source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(int sectionColumnCount READ sectionColumnCount WRITE setSectionColumnCount NOTIFY sectionColumnCountChanged)
    Q_PROPERTY(int sectionRowCount READ sectionRowCount WRITE setSectionRowCount NOTIFY sectionRowCountChanged)

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
        HeaderSection = Qt::UserRole + 5,
        IsLeaf        = Qt::UserRole + 6
    };

    Q_ENUM(Role)

    explicit QxHeaderModelAdaptor(QObject *parent = nullptr);

    QAbstractItemModel *source() const;
    void setSource(QAbstractItemModel *newSource);

    void setSections(const QList<QxHeaderSection *> &newSections);

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    QxHeaderSection *root() const;
    void setRoot(QxHeaderSection *newRoot);

    Q_INVOKABLE void addSectionWidthOffset(QxHeaderSection *section, qreal offset);

    int sectionColumnCount() const;

    int sectionRowCount() const;

    qreal sectionDefaultWidth() const;
    void setSectionDefaultWidth(qreal newSectionDefaultWidth);

protected:
    void invalidate();
    int sectionColumn(QxHeaderSection *section) const;
    virtual void onSourceModelChanged(QAbstractItemModel *new_model, QAbstractItemModel *old_model);
    void updateColumnSize();
    void setSectionColumnCount(int newSectionColumnCount);
    void setSectionRowCount(int newSectionRowCount);

signals:
    void sourceChanged();
    void sectionWidthChanged(int section, qreal width);
    void sectionColumnCountChanged();
    void sectionRowCountChanged();

private:
    QPointer<QAbstractItemModel> m_source;
    QxHeaderSection *m_root;
    QList<QxHeaderSection *> m_sections;
    QList<QMetaObject::Connection> m_connections;
    int m_sectionColumnCount = 0;
    int m_sectionRowCount    = 0;
    qreal m_sectionDefaultWidth = 0;
};
