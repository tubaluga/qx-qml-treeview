#include "qxheaderviewtemplate.h"

#include <QQmlContext>
#include <QQmlEngine>
#include <QTimer>

QxHeaderViewTemplate::QxHeaderViewTemplate(QQuickItem *parent) :
    QQuickItem(parent)
{
    m_rootSection = new QxHeaderSection(this);
}

QxHeaderViewTemplate::~QxHeaderViewTemplate()
{
}

QAbstractItemModel *QxHeaderViewTemplate::model() const
{
    return m_model;
}

void QxHeaderViewTemplate::setModel(QAbstractItemModel *newModel)
{
    if (m_model == newModel) {
        return;
    }

    auto old_model = m_model.data();

    m_model = newModel;

    setupModel(m_model.data(), old_model);

    emit modelChanged();
}

QQmlComponent *QxHeaderViewTemplate::sectionDelegate() const
{
    return m_sectionDelegate;
}

void QxHeaderViewTemplate::setSectionDelegate(QQmlComponent *newDelegate)
{
    if (m_sectionDelegate == newDelegate) {
        return;
    }

    m_sectionDelegate = newDelegate;
    emit sectionDelegateChanged();
}

quint32 QxHeaderViewTemplate::displayTextRole() const
{
    return m_displayTextRole;
}

void QxHeaderViewTemplate::setDisplayTextRole(quint32 newDisplayTextRole)
{
    if (m_displayTextRole == newDisplayTextRole) {
        return;
    }

    m_displayTextRole = newDisplayTextRole;

    emit displayTextRoleChanged();
}

const QList<QxHeaderSection *> &QxHeaderViewTemplate::sections() const
{
    return m_sections;
}

void QxHeaderViewTemplate::setupModel(QAbstractItemModel *new_model, QAbstractItemModel *old_model)
{
    Q_UNUSED(new_model)
    Q_UNUSED(old_model)
}

QList<QxHeaderSection *> QxHeaderViewTemplate::leafs() const
{
    std::function<void(QxHeaderSection * begin, QList<QxHeaderSection *> &)> find_leaf = [&find_leaf](QxHeaderSection *begin, QList<QxHeaderSection *> &target) {
        foreach (auto section, begin->sections()) {
            if (section->isLeaf()) {
                target.append(section);
            }
            else {
                find_leaf(section, target);
            }
        }
    };

    QList<QxHeaderSection *> leaf_list;

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

QQmlListProperty<QxHeaderSection> QxHeaderViewTemplate::sectionListProperty()
{
    return { this, this, &QxHeaderViewTemplate::appendSection, &QxHeaderViewTemplate::sectionCount, &QxHeaderViewTemplate::section, &QxHeaderViewTemplate::clearSections };
}

void QxHeaderViewTemplate::appendSection(QxHeaderSection *section)
{
    m_sections.append(section);
    invalidate();
}

int QxHeaderViewTemplate::sectionCount()
{
    return m_sections.size();
}

QxHeaderSection *QxHeaderViewTemplate::section(int index)
{
    return m_sections.at(index);
}

void QxHeaderViewTemplate::clearSections()
{
    foreach (auto sec, m_sections) {
        sec->deleteLater();
    }

    m_sections.clear();
}

void QxHeaderViewTemplate::appendSection(QQmlListProperty<QxHeaderSection> *list, QxHeaderSection *p)
{
    reinterpret_cast<QxHeaderViewTemplate *>(list->data)->appendSection(p);
}

int QxHeaderViewTemplate::sectionCount(QQmlListProperty<QxHeaderSection> *list)
{
    return reinterpret_cast<QxHeaderViewTemplate *>(list->data)->sectionCount();
}

QxHeaderSection *QxHeaderViewTemplate::section(QQmlListProperty<QxHeaderSection> *list, int index)
{
    return reinterpret_cast<QxHeaderViewTemplate *>(list->data)->section(index);
}

void QxHeaderViewTemplate::clearSections(QQmlListProperty<QxHeaderSection> *list)
{
    reinterpret_cast<QxHeaderViewTemplate *>(list->data)->clearSections();
}

QxHeaderSection *QxHeaderViewTemplate::rootSection() const
{
    return m_rootSection;
}
