#include "qxquickheaderviewtemplate.h"

#include <QQmlContext>
#include <QQmlEngine>
#include <QTimer>

QxQuickHeaderViewTemplate::QxQuickHeaderViewTemplate(QQuickItem *parent) :
    QQuickItem(parent)
{
    setZ(1);
}

QxQuickHeaderViewTemplate::~QxQuickHeaderViewTemplate()
{
}

QAbstractItemModel *QxQuickHeaderViewTemplate::model() const
{
    return m_model;
}

void QxQuickHeaderViewTemplate::setModel(QAbstractItemModel *newModel)
{
    if (m_model == newModel) {
        return;
    }

    auto old_model = m_model.data();

    m_model = newModel;

    setupModel(m_model.data(), old_model);

    emit modelChanged();
}

quint32 QxQuickHeaderViewTemplate::displayTextRole() const
{
    return m_displayTextRole;
}

void QxQuickHeaderViewTemplate::setDisplayTextRole(quint32 newDisplayTextRole)
{
    if (m_displayTextRole == newDisplayTextRole) {
        return;
    }

    m_displayTextRole = newDisplayTextRole;

    emit displayTextRoleChanged();
}

const QList<QxQuickHeaderSection *> &QxQuickHeaderViewTemplate::sections() const
{
    return m_sections;
}

void QxQuickHeaderViewTemplate::setupModel(QAbstractItemModel *new_model, QAbstractItemModel *old_model)
{
    Q_UNUSED(new_model)
    Q_UNUSED(old_model)
}

QList<QxQuickHeaderSection *> QxQuickHeaderViewTemplate::leafs() const
{
    std::function<void(QxQuickHeaderSection * begin, QList<QxQuickHeaderSection *> &)> find_leaf = [&find_leaf](QxQuickHeaderSection *begin, QList<QxQuickHeaderSection *> &target) {
        foreach (auto section, begin->sections()) {
            if (section->isLeaf()) {
                target.append(section);
            }
            else {
                find_leaf(section, target);
            }
        }
    };

    QList<QxQuickHeaderSection *> leaf_list;

    foreach (auto section, m_sections) {
        if (section->isLeaf()) {
            leaf_list << section;
        }
        else {
            find_leaf(section, leaf_list);
        }
    }

    return leaf_list;
}

QQmlListProperty<QxQuickHeaderSection> QxQuickHeaderViewTemplate::sectionListProperty()
{
    return { this, this, &QxQuickHeaderViewTemplate::appendSection, &QxQuickHeaderViewTemplate::sectionCount, &QxQuickHeaderViewTemplate::section, &QxQuickHeaderViewTemplate::clearSections };
}

void QxQuickHeaderViewTemplate::appendSection(QxQuickHeaderSection *section)
{
    m_sections.append(section);
}

int QxQuickHeaderViewTemplate::sectionCount()
{
    return m_sections.size();    
}

QxQuickHeaderSection *QxQuickHeaderViewTemplate::section(int index)
{
    return m_sections.at(index);
}

void QxQuickHeaderViewTemplate::clearSections()
{
    foreach (auto sec, m_sections) {
        sec->deleteLater();
    }

    m_sections.clear();
}

void QxQuickHeaderViewTemplate::appendSection(QQmlListProperty<QxQuickHeaderSection> *list, QxQuickHeaderSection *p)
{
    reinterpret_cast<QxQuickHeaderViewTemplate *>(list->data)->appendSection(p);
}

int QxQuickHeaderViewTemplate::sectionCount(QQmlListProperty<QxQuickHeaderSection> *list)
{
    return reinterpret_cast<QxQuickHeaderViewTemplate *>(list->data)->sectionCount();
}

QxQuickHeaderSection *QxQuickHeaderViewTemplate::section(QQmlListProperty<QxQuickHeaderSection> *list, int index)
{
    return reinterpret_cast<QxQuickHeaderViewTemplate *>(list->data)->section(index);
}

void QxQuickHeaderViewTemplate::clearSections(QQmlListProperty<QxQuickHeaderSection> *list)
{
    reinterpret_cast<QxQuickHeaderViewTemplate *>(list->data)->clearSections();
}
