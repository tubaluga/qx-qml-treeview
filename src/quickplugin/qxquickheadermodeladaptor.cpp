#include "qxquickheadermodeladaptor.h"

QxQuickHeaderModelAdaptor::QxQuickHeaderModelAdaptor(QObject *parent) :
    QAbstractListModel{ parent }
{
    m_root = new QxQuickHeaderSection(this);
    m_root->setTitle("adaptor_root");
}

QAbstractItemModel *QxQuickHeaderModelAdaptor::source() const
{
    return m_source;
}

void QxQuickHeaderModelAdaptor::setSource(QAbstractItemModel *newSource)
{
    if (m_source == newSource) {
        return;
    }
    auto cur_model = m_source.data();

    m_source = newSource;

    onSourceModelChanged(m_source, cur_model);

    emit sourceChanged();
}

void QxQuickHeaderModelAdaptor::setSections(const QList<QxQuickHeaderSection *> &newSections)
{
    m_root->clearSections();
    m_sections.clear();

    foreach (auto sec, newSections) {
        m_root->appendSection(sec);
    }

    std::function<void(QxQuickHeaderSection * section)> tree_visitor = [&tree_visitor, this](QxQuickHeaderSection *section) {
        for (int i = 0; i < section->sections().size(); ++i) {
            auto s = section->sections().at(i);

            if (s->isLeaf() && s->width() < 1) {
                s->setWidth(sectionDefaultWidth());
            }

            m_sections << s;

            tree_visitor(s);
        }
    };

    tree_visitor(m_root);

    m_leafSections = m_root->leafs();

    foreach (const auto &connection, m_connections) {
        disconnect(connection);
    }

    foreach (auto column_section, m_leafSections) {
        m_connections << connect(column_section, &QxQuickHeaderSection::widthChanged, this, [column_section, this]() {
            emit sectionWidthChanged(column_section->column(), column_section->width());
        });
    }

    setSectionColumnCount(m_leafSections.size());
    setSectionRowCount(root()->maxChildrenDepth());

    invalidate();

    beginResetModel();
    endResetModel();

    updateColumnSize();
}

int QxQuickHeaderModelAdaptor::rowCount(const QModelIndex &parent) const
{
    return m_sections.size();
}

QVariant QxQuickHeaderModelAdaptor::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() && index.model() != this) {
        return QVariant();
    }

    auto section = m_sections.at(index.row());

    switch (role) {
    case Title:
        return section->title();
    case ColSpan:
        return section->columnSpan();
    case RowSpan:
        return section->rowSpan();
    case Column:
        return section->column();
    case HeaderSection:
        return QVariant::fromValue(section);
    case IsLeaf:
        return section->isLeaf();
    default:
        if (m_source.isNull()) {
            return QVariant();
        }

        return m_source->data(section->index(), role);
    }
}

QHash<int, QByteArray> QxQuickHeaderModelAdaptor::roleNames() const
{
    if (m_source.isNull()) {
        return QHash<int, QByteArray>();
    }

    QHash<int, QByteArray> roles = m_source->roleNames();

    roles.insert(Role::Title, "adaptor_title");
    roles.insert(Role::ColSpan, "adaptor_col_span");
    roles.insert(Role::RowSpan, "adaptor_row_span");
    roles.insert(Role::Row, "adaptor_row");
    roles.insert(Role::Column, "adaptor_column");
    roles.insert(Role::HeaderSection, "adaptor_section");
    roles.insert(Role::IsLeaf, "adaptor_is_leaf");

    return roles;
}

void QxQuickHeaderModelAdaptor::invalidate()
{
    foreach (auto section, m_sections) {
        section->invalidate();

        if (section->isLeaf() && section->width() < 1) {
            section->setWidth(sectionDefaultWidth());
        }
    }
}

int QxQuickHeaderModelAdaptor::sectionColumn(QxQuickHeaderSection *section) const
{ 
    int depth = section->depth();

    int column = 0;
    bool find  = false;

    std::function<void(QxQuickHeaderSection * section)> tree_visitor = [&tree_visitor, depth, &column, section, &find](QxQuickHeaderSection *v_section) {
        if (find) {
            return;
        }

        if (v_section == section) {
            find = true;
            return;
        }

        if (v_section->depth() == depth) {
            ++column;
            return;
        }

        for (int i = 0; i < v_section->sections().size(); ++i) {
            auto s = v_section->sections().at(i);
            tree_visitor(s);
        }
    };

    tree_visitor(m_root);

    return column;
}

void QxQuickHeaderModelAdaptor::onSourceModelChanged(QAbstractItemModel *new_model, QAbstractItemModel *old_model)
{
    Q_UNUSED(new_model)
    Q_UNUSED(old_model)
}

void QxQuickHeaderModelAdaptor::updateColumnSize()
{
    foreach (auto leaf, m_leafSections) {
        emit sectionWidthChanged(leaf->column(), leaf->width());
    }
}

int QxQuickHeaderModelAdaptor::sectionRowCount() const
{
    return m_sectionRowCount;
}

void QxQuickHeaderModelAdaptor::setSectionRowCount(int newSectionRowCount)
{
    if (m_sectionRowCount == newSectionRowCount) {
        return;
    }

    m_sectionRowCount = newSectionRowCount;
    emit sectionRowCountChanged();
}

qreal QxQuickHeaderModelAdaptor::sectionDefaultWidth() const
{
    return m_sectionDefaultWidth;
}

void QxQuickHeaderModelAdaptor::setSectionDefaultWidth(qreal newSectionDefaultWidth)
{
    if (m_sectionDefaultWidth == newSectionDefaultWidth) {
        return;
    }

    m_sectionDefaultWidth = newSectionDefaultWidth;

    setColumnsWidth(m_sectionDefaultWidth);
}

void QxQuickHeaderModelAdaptor::setColumnsWidth(qreal width)
{
    foreach (auto section, m_sections) {
        if (section->isLeaf()) {
            section->setWidth(width);
        }
    }
}

void QxQuickHeaderModelAdaptor::setColumnWidth(int section, qreal width)
{
    if (section > -1 && section < m_leafSections.size()) {
        m_leafSections.at(section)->setWidth(width);
    }
}

int QxQuickHeaderModelAdaptor::sectionColumnCount() const
{
    return m_sectionColumnCount;
}

void QxQuickHeaderModelAdaptor::setSectionColumnCount(int newSectionColumnCount)
{
    if (m_sectionColumnCount == newSectionColumnCount)
        return;
    m_sectionColumnCount = newSectionColumnCount;
    emit sectionColumnCountChanged();
}

QxQuickHeaderSection *QxQuickHeaderModelAdaptor::root() const
{
    return m_root;
}

void QxQuickHeaderModelAdaptor::setRoot(QxQuickHeaderSection *newRoot)
{
    m_root = newRoot;

    setSections(m_root->sections());
}

void QxQuickHeaderModelAdaptor::addSectionWidthOffset(QxQuickHeaderSection *section, qreal offset)
{
    static qreal minimum_column_width = 25;

    if (section == nullptr) {
        return;
    }

    auto parent_section = section->parentSection();

    while (parent_section) {
        parent_section->setWidth(qMax(minimum_column_width, parent_section->width() + offset));
        parent_section = parent_section->parentSection();
    }

    section->setWidth(qMax(minimum_column_width, section->width() + offset));

    if (!section->sections().isEmpty()) {
        auto child_section = section->sections().last();

        while (child_section != nullptr) {
            child_section->setWidth(qMax(minimum_column_width, child_section->width() + offset));

            if (!child_section->sections().isEmpty()) {
                child_section = child_section->sections().last();
            }
            else {
                break;
            }
        }
    }
}
