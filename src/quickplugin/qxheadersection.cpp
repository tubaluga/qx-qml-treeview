#include "qxheadersection.h"

QxHeaderSection::QxHeaderSection(QObject *parent) :
    QObject(parent)
{
}

QQmlListProperty<QxHeaderSection> QxHeaderSection::sectionListProperty()
{
    return { this, this, &QxHeaderSection::appendSection, &QxHeaderSection::sectionCount, &QxHeaderSection::section, &QxHeaderSection::clearSections };
}

void QxHeaderSection::appendSection(QxHeaderSection *section)
{
    section->setParentSection(this);
    m_sections.append(section);

    /*invalidate();
    section->invalidate();*/
}

int QxHeaderSection::sectionCount()
{
    return m_sections.size();
}

QxHeaderSection *QxHeaderSection::section(int index)
{
    return m_sections.at(index);
}

void QxHeaderSection::clearSections()
{
    m_sections.clear();
}

void QxHeaderSection::appendSection(QQmlListProperty<QxHeaderSection> *list, QxHeaderSection *p)
{
    reinterpret_cast<QxHeaderSection *>(list->data)->appendSection(p);
}

int QxHeaderSection::sectionCount(QQmlListProperty<QxHeaderSection> *list)
{
    return reinterpret_cast<QxHeaderSection *>(list->data)->sectionCount();
}

QxHeaderSection *QxHeaderSection::section(QQmlListProperty<QxHeaderSection> *list, int index)
{
    return reinterpret_cast<QxHeaderSection *>(list->data)->section(index);
}

void QxHeaderSection::clearSections(QQmlListProperty<QxHeaderSection> *list)
{
    reinterpret_cast<QxHeaderSection *>(list->data)->clearSections();
}

int QxHeaderSection::row() const
{
    return m_row;
}

void QxHeaderSection::setRow(int newRow)
{
    if (m_row == newRow)
        return;
    m_row = newRow;
    emit rowChanged();
}

int QxHeaderSection::column() const
{
    return m_column;
}

void QxHeaderSection::setColumn(int newColumn)
{
    if (m_column == newColumn)
        return;
    m_column = newColumn;
    emit columnChanged();
}

int QxHeaderSection::columnSpan() const
{
    return m_columnSpan;
}

void QxHeaderSection::setColumnSpan(int newColumnSpan)
{
    if (m_columnSpan == newColumnSpan)
        return;
    m_columnSpan = newColumnSpan;
    emit columnSpanChanged();
}

int QxHeaderSection::rowSpan() const
{
    return m_rowSpan;
}

void QxHeaderSection::setRowSpan(int newRowSpan)
{
    if (m_rowSpan == newRowSpan)
        return;
    m_rowSpan = newRowSpan;
    emit rowSpanChanged();
}

const QList<QxHeaderSection *> &QxHeaderSection::sections() const
{
    return m_sections;
}

void QxHeaderSection::resize()
{
    int new_size = 0;

    foreach (auto child, m_sections) {
        new_size += child->width();
    }

    setWidth(new_size);
}

void QxHeaderSection::invalidate()
{
    if (isLeaf()) {
        setColumnSpan(1);        
    }
    else {
        setColumnSpan(leafCount());
    }

    qDebug() << "depth" << depth();

    setRow(qMax(depth() - 1, 0));

    if (parentSection() != nullptr) {
        auto root = rootSection();

        int col = 0;

        if (isLeaf()) {
            col = root->leafs().indexOf(this);
        }
        else {
            col = leafs().indexOf(root->leafs().at(0));
        }

        setColumn(col);
    }
    else {
        setColumn(0);
        setRow(0);
    }

    qDebug() << "INVALIDATE" << this << title() << row() << column() << "span" << columnSpan() << rowSpan();
}

QxHeaderSection *QxHeaderSection::parentSection() const
{
    return m_parentSection;
}

void QxHeaderSection::setParentSection(QxHeaderSection *newSectionParent)
{
    m_parentSection = newSectionParent;
}

QxHeaderSection *QxHeaderSection::rootSection() const
{
    auto p = parentSection();

    while (p->parentSection() != nullptr) {
        p = p->parentSection();
    }

    return p;
}

int QxHeaderSection::width() const
{
    return m_width;
}

void QxHeaderSection::setWidth(int newWidth)
{
    if (m_width == newWidth) {
        return;
    }

    m_width = newWidth;
    emit widthChanged();
}

bool QxHeaderSection::isLeaf() const
{
    return m_sections.empty();
}

int QxHeaderSection::leafCount() const
{
    return leafs().size();
}

int QxHeaderSection::depth() const
{
    int depth = 0;

    auto parent_section = parentSection();

    while (parent_section) {
        ++depth;
        parent_section = parent_section->parentSection();
    }

    return depth;
}

QList<QxHeaderSection *> QxHeaderSection::leafs() const
{
    QList<QxHeaderSection *> result;

    std::function<void(const QList<QxHeaderSection *> &)> tree_visitor = [&tree_visitor, &result](const QList<QxHeaderSection *> &sections) {
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

const QString &QxHeaderSection::title() const
{
    return m_title;
}

void QxHeaderSection::setTitle(const QString &newTitle)
{
    if (m_title == newTitle) {
        return;
    }

    m_title = newTitle;

    emit titleChanged();
}
