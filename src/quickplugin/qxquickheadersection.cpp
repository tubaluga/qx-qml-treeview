#include "qxquickheadersection.h"

QxQuickHeaderSection::QxQuickHeaderSection(QObject *parent) :
    QObject(parent)
{
}

QQmlListProperty<QxQuickHeaderSection> QxQuickHeaderSection::sectionListProperty()
{
    return { this, this, &QxQuickHeaderSection::appendSection, &QxQuickHeaderSection::sectionCount, &QxQuickHeaderSection::section, &QxQuickHeaderSection::clearSections };
}

void QxQuickHeaderSection::appendSection(QxQuickHeaderSection *section)
{
    section->setParentSection(this);
    m_sections.append(section);

    emit isLeafChanged();

    section->invalidate();
}

int QxQuickHeaderSection::sectionCount()
{
    return m_sections.size();
}

QxQuickHeaderSection *QxQuickHeaderSection::section(int index)
{
    return m_sections.at(index);
}

void QxQuickHeaderSection::clearSections()
{
    foreach (auto section, m_sections) {
        section->deleteLater();
    }
    m_sections.clear();
}

void QxQuickHeaderSection::appendSection(QQmlListProperty<QxQuickHeaderSection> *list, QxQuickHeaderSection *p)
{
    reinterpret_cast<QxQuickHeaderSection *>(list->data)->appendSection(p);
}

int QxQuickHeaderSection::sectionCount(QQmlListProperty<QxQuickHeaderSection> *list)
{
    return reinterpret_cast<QxQuickHeaderSection *>(list->data)->sectionCount();
}

QxQuickHeaderSection *QxQuickHeaderSection::section(QQmlListProperty<QxQuickHeaderSection> *list, int index)
{
    return reinterpret_cast<QxQuickHeaderSection *>(list->data)->section(index);
}

void QxQuickHeaderSection::clearSections(QQmlListProperty<QxQuickHeaderSection> *list)
{
    reinterpret_cast<QxQuickHeaderSection *>(list->data)->clearSections();
}

const QPersistentModelIndex &QxQuickHeaderSection::index() const
{
    return m_index;
}

void QxQuickHeaderSection::setIndex(const QPersistentModelIndex &newIndex)
{
    if (m_index == newIndex)
        return;
    m_index = newIndex;
    emit indexChanged();
}

int QxQuickHeaderSection::row() const
{
    return m_row;
}

void QxQuickHeaderSection::setRow(int newRow)
{
    if (m_row == newRow)
        return;
    m_row = newRow;
    emit rowChanged();
}

int QxQuickHeaderSection::column() const
{
    return m_column;
}

void QxQuickHeaderSection::setColumn(int newColumn)
{
    if (m_column == newColumn)
        return;
    m_column = newColumn;
    emit columnChanged();
}

int QxQuickHeaderSection::columnSpan() const
{
    return m_columnSpan;
}

void QxQuickHeaderSection::setColumnSpan(int newColumnSpan)
{
    if (m_columnSpan == newColumnSpan)
        return;
    m_columnSpan = newColumnSpan;
    emit columnSpanChanged();
}

int QxQuickHeaderSection::rowSpan() const
{
    return m_rowSpan;
}

void QxQuickHeaderSection::setRowSpan(int newRowSpan)
{
    if (m_rowSpan == newRowSpan)
        return;
    m_rowSpan = newRowSpan;
    emit rowSpanChanged();
}

const QList<QxQuickHeaderSection *> &QxQuickHeaderSection::sections() const
{
    return m_sections;
}

void QxQuickHeaderSection::resize()
{
    int new_size = 0;

    foreach (auto child, m_sections) {
        new_size += child->width();
    }

    setWidth(new_size);
}

QxQuickHeaderSection *QxQuickHeaderSection::findFirstLeafSection()
{
    if (sections().isEmpty()) {
        return this;
    }

    auto section = sections().first();

    while (!section->isLeaf()) {
        section = section->sections().first();
    }

    return section;
}

void QxQuickHeaderSection::invalidate()
{
    if (isLeaf()) {
        setColumnSpan(1);        
    }
    else {
        setColumnSpan(leafCount());
    }

    setRow(qMax(depth() - 1, 0));

    if (parentSection() != nullptr) {
        auto root = rootSection();

        int column_index = -1;

        if (isLeaf()) {
            column_index = root->leafs().indexOf(this);
        }
        else {
            auto leaf_section = findFirstLeafSection();

            column_index = root->leafs().indexOf(leaf_section);
        }

        setColumn(column_index);
    }
    else {
        setColumn(0);
        setRow(0);
    }

    if (children().empty()) {
        int current_depth = depth();
        int max_depth     = rootSection()->maxChildrenDepth();

        if (current_depth < max_depth) {
            setRowSpan(max_depth - current_depth);
        }
    }

    emit depthChanged();
}

QxQuickHeaderSection *QxQuickHeaderSection::parentSection() const
{
    return m_parentSection;
}

void QxQuickHeaderSection::setParentSection(QxQuickHeaderSection *newSectionParent)
{
    m_parentSection = newSectionParent;
}

QxQuickHeaderSection *QxQuickHeaderSection::rootSection() const
{
    auto p = parentSection();

    while (p->parentSection() != nullptr) {
        p = p->parentSection();
    }

    return p;
}

qreal QxQuickHeaderSection::width() const
{
    return m_width;
}

void QxQuickHeaderSection::setWidth(qreal newWidth)
{
    if (qFuzzyCompare(m_width, newWidth)) {
        return;
    }

    m_width = newWidth;

    emit widthChanged();
}

bool QxQuickHeaderSection::isLeaf() const
{
    return m_sections.empty();
}

int QxQuickHeaderSection::leafCount() const
{
    return leafs().size();
}

int QxQuickHeaderSection::depth() const
{
    int depth = 0;

    auto parent_section = parentSection();

    while (parent_section) {
        ++depth;
        parent_section = parent_section->parentSection();
    }

    return depth;
}

int QxQuickHeaderSection::maxChildrenDepth() const
{
    std::function<void(const QxQuickHeaderSection *, int &)> tree_visitor = [&tree_visitor](const QxQuickHeaderSection *section, int &depth) {
        ++depth;

        for (int i = 0; i < section->sections().size(); ++i) {
            auto s = section->sections().at(i);
            tree_visitor(s, depth);
        }
    };

    int res = 0;
    tree_visitor(this, res);

    return res;
}

QList<QxQuickHeaderSection *> QxQuickHeaderSection::leafs() const
{
    QList<QxQuickHeaderSection *> result;

    std::function<void(const QList<QxQuickHeaderSection *> &)> tree_visitor = [&tree_visitor, &result](const QList<QxQuickHeaderSection *> &sections) {
        for (int i = 0; i < sections.size(); ++i) {
            auto s = sections.at(i);

            if (s->sections().isEmpty()) {
                result.append(s);
            }
            else {
                tree_visitor(s->sections());
            }
        }
    };

    tree_visitor(m_sections);

    return result;
}

QList<QxQuickHeaderSection *> QxQuickHeaderSection::depthSections(int depth) const
{
    QList<QxQuickHeaderSection *> res;
    std::function<void(const QList<QxQuickHeaderSection *> &, QList<QxQuickHeaderSection *> &)> tree_visitor = [&tree_visitor, depth](const QList<QxQuickHeaderSection *> &sections, QList<QxQuickHeaderSection *> &container) {
        for (int i = 0; i < sections.size(); ++i) {
            auto s = sections.at(i);

            if (s->depth() == depth) {
                container << s;
            }
            else {
                tree_visitor(s->sections(), container);
            }
        }
    };

    tree_visitor(m_sections, res);

    return res;
}

const QString &QxQuickHeaderSection::title() const
{
    return m_title;
}

void QxQuickHeaderSection::setTitle(const QString &newTitle)
{
    if (m_title == newTitle) {
        return;
    }

    m_title = newTitle;

    emit titleChanged();
}
