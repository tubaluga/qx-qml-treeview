#pragma once

#include <QAbstractItemModel>
#include <QPointer>
#include <QQuickItem>

#include "qxquickheadersection.h"

class QxQuickHeaderViewTemplate : public QQuickItem {
    Q_OBJECT

    Q_DISABLE_COPY(QxQuickHeaderViewTemplate)

    Q_PROPERTY(QAbstractItemModel *model READ model WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(quint32 displayTextRole READ displayTextRole WRITE setDisplayTextRole NOTIFY displayTextRoleChanged)
    Q_PROPERTY(QQmlListProperty<QxQuickHeaderSection> sections READ sectionListProperty CONSTANT)

public:
    explicit QxQuickHeaderViewTemplate(QQuickItem *parent = nullptr);
    virtual ~QxQuickHeaderViewTemplate();

    QAbstractItemModel *model() const;
    void setModel(QAbstractItemModel *newModel);

    quint32 displayTextRole() const;
    void setDisplayTextRole(quint32 newDisplayTextRole);

    const QList<QxQuickHeaderSection *> &sections() const;
    QQmlListProperty<QxQuickHeaderSection> sectionListProperty();

    void appendSection(QxQuickHeaderSection *);
    int sectionCount();
    QxQuickHeaderSection *section(int);
    void clearSections();

protected:
    virtual void setupModel(QAbstractItemModel *new_model, QAbstractItemModel *old_model);

    QList<QxQuickHeaderSection *> leafs() const;

private:
    static void appendSection(QQmlListProperty<QxQuickHeaderSection> *, QxQuickHeaderSection *);
    static int sectionCount(QQmlListProperty<QxQuickHeaderSection> *);
    static QxQuickHeaderSection *section(QQmlListProperty<QxQuickHeaderSection> *, int);
    static void clearSections(QQmlListProperty<QxQuickHeaderSection> *);

signals:
    void modelChanged();
    void displayTextRoleChanged();

private:
    QPointer<QAbstractItemModel> m_model;
    quint32 m_displayTextRole = Qt::DisplayRole;
    QList<QxQuickHeaderSection *> m_sections;
};

Q_DECLARE_METATYPE(QxQuickHeaderViewTemplate *)
