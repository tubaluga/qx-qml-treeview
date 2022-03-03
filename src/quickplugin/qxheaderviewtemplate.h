#pragma once

#include <QAbstractItemModel>
#include <QPointer>
#include <QQuickItem>

#include "qxheadersection.h"
#include "qxtreeviewsectionmodeldata.h"

class QxHeaderViewTemplate : public QQuickItem {
    Q_OBJECT
    Q_PROPERTY(QAbstractItemModel *model READ model WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(QQmlComponent *sectionDelegate READ sectionDelegate WRITE setSectionDelegate NOTIFY sectionDelegateChanged)
    Q_PROPERTY(quint32 displayTextRole READ displayTextRole WRITE setDisplayTextRole NOTIFY displayTextRoleChanged)
    Q_PROPERTY(QQmlListProperty<QxHeaderSection> sections READ sectionListProperty CONSTANT)
    Q_PROPERTY(QxHeaderSection *rootSection READ rootSection CONSTANT)

public:
    explicit QxHeaderViewTemplate(QQuickItem *parent = nullptr);
    virtual ~QxHeaderViewTemplate();

    QAbstractItemModel *model() const;
    void setModel(QAbstractItemModel *newModel);

    QQmlComponent *sectionDelegate() const;
    void setSectionDelegate(QQmlComponent *newDelegate);

    quint32 displayTextRole() const;
    void setDisplayTextRole(quint32 newDisplayTextRole);

    const QList<QxHeaderSection *> &sections() const;
    QQmlListProperty<QxHeaderSection> sectionListProperty();

    void appendSection(QxHeaderSection *);
    int sectionCount();
    QxHeaderSection *section(int);
    void clearSections();

    QxHeaderSection *rootSection() const;

protected:
    virtual void invalidate() = 0;
    virtual void setupModel(QAbstractItemModel *new_model, QAbstractItemModel *old_model);

    QList<QxHeaderSection *> leafs() const;

private:
    static void appendSection(QQmlListProperty<QxHeaderSection> *, QxHeaderSection *);
    static int sectionCount(QQmlListProperty<QxHeaderSection> *);
    static QxHeaderSection *section(QQmlListProperty<QxHeaderSection> *, int);
    static void clearSections(QQmlListProperty<QxHeaderSection> *);

signals:
    void modelChanged();
    void sectionDelegateChanged();
    void displayTextRoleChanged();

private:
    QPointer<QQmlComponent> m_sectionDelegate;
    QPointer<QAbstractItemModel> m_model;
    quint32 m_displayTextRole = Qt::DisplayRole;
    QList<QxHeaderSection *> m_sections;
    QxHeaderSection *m_rootSection = nullptr;
};

Q_DECLARE_METATYPE(QxHeaderViewTemplate *)
