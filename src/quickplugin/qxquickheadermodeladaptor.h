#pragma once

#include <QAbstractListModel>
#include <QPointer>

#include "qxquickheadersection.h"

class QxQuickHeaderModelAdaptor : public QAbstractListModel {
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
        Title   = Qt::DisplayRole,
        RowSpan = Qt::UserRole - 6,
        ColSpan,
        Column,
        Row,
        HeaderSection,
        IsLeaf
    };

    Q_ENUM(Role)

    explicit QxQuickHeaderModelAdaptor(QObject *parent = nullptr);

    QAbstractItemModel *source() const;
    void setSource(QAbstractItemModel *newSource);

    void setSections(const QList<QxQuickHeaderSection *> &newSections);

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    QxQuickHeaderSection *root() const;
    void setRoot(QxQuickHeaderSection *newRoot);

    Q_INVOKABLE void addSectionWidthOffset(QxQuickHeaderSection *section, qreal offset);

    int sectionColumnCount() const;

    int sectionRowCount() const;

    qreal sectionDefaultWidth() const;
    void setSectionDefaultWidth(qreal newSectionDefaultWidth);

    void setColumnsWidth(qreal width);
    void setColumnWidth(int section, qreal width);

protected:
    void invalidate();
    int sectionColumn(QxQuickHeaderSection *section) const;
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
    QxQuickHeaderSection *m_root;
    QList<QxQuickHeaderSection *> m_sections;
    QList<QxQuickHeaderSection *> m_leafSections;
    QList<QMetaObject::Connection> m_connections;
    int m_sectionColumnCount = 0;
    int m_sectionRowCount    = 0;
    qreal m_sectionDefaultWidth = 0;
};
