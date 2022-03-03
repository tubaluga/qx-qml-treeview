#include "qxheadermodeladaptor.h"

QxHeaderModelAdaptor::QxHeaderModelAdaptor(QObject *parent) :
    QAbstractListModel{ parent }
{
    m_root = new QxHeaderSection(this);
    m_root->setTitle("adaptor_root");
}

QAbstractItemModel *QxHeaderModelAdaptor::source() const
{
    return m_source;
}

void QxHeaderModelAdaptor::setSource(QAbstractItemModel *newSource)
{
    if (m_source == newSource) {
        return;
    }

    m_source = newSource;
    emit sourceChanged();
}

void QxHeaderModelAdaptor::setSections(const QList<QxHeaderSection *> &newSections)
{
    m_root->clearSections();
    m_sections.clear();

    foreach (auto sec, newSections) {
        m_root->appendSection(sec);
    }

    std::function<void(QxHeaderSection * section)> tree_visitor = [&tree_visitor, this](QxHeaderSection *section) {
        for (int i = 0; i < section->sections().size(); ++i) {
            auto s = section->sections().at(i);
            m_sections << s;

            tree_visitor(s);
        }
    };

    tree_visitor(m_root);

    invalidate();

    beginResetModel();
    endResetModel();
}

int QxHeaderModelAdaptor::rowCount(const QModelIndex &parent) const
{
    return m_sections.size();
}

QVariant QxHeaderModelAdaptor::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() && index.model() != this) {
        return QVariant();
    }

    auto section = m_sections.at(index.row());

    if (role == Title) {
        return section->title();
    }
    else if (role == ColSpan) {
        return section->columnSpan();
    }
    else if (role == RowSpan) {
        return section->rowSpan();
    }
    else if (role == Column) {
        return section->column();
    }
    else if (role == HeaderSection) {
        return QVariant::fromValue(section);
    }
    else if (role == IsLeaf) {
        return section->isLeaf();
    }

    return QVariant();
}

QHash<int, QByteArray> QxHeaderModelAdaptor::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles.insert(Role::Title, "adaptor_title");
    roles.insert(Role::ColSpan, "adaptor_col_span");
    roles.insert(Role::RowSpan, "adaptor_row_span");
    roles.insert(Role::Row, "adaptor_row");
    roles.insert(Role::Column, "adaptor_column");
    roles.insert(Role::HeaderSection, "adaptor_section");
    roles.insert(Role::IsLeaf, "adaptor_is_leaf");

    return roles;
}

void QxHeaderModelAdaptor::invalidate()
{
    foreach (auto section, m_sections) {
        section->invalidate();
    }
}

int QxHeaderModelAdaptor::sectionColumn(QxHeaderSection *section) const
{
    int depth = section->depth();

    int column = 0;
    bool find  = false;

    std::function<void(QxHeaderSection * section)> tree_visitor = [&tree_visitor, depth, &column, section, &find](QxHeaderSection *v_section) {
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

QxHeaderSection *QxHeaderModelAdaptor::root() const
{
    return m_root;
}

void QxHeaderModelAdaptor::setRoot(QxHeaderSection *newRoot)
{
    m_root = newRoot;

    setSections(m_root->sections());
}

void QxHeaderModelAdaptor::addSectionWidthOffset(QxHeaderSection *section, int offset)
{
    if (section == nullptr) {
        return;
    }

    auto parent_section = section->parentSection();

    while (parent_section) {
        parent_section->setWidth(qMax(20, parent_section->width() + offset));
        parent_section = parent_section->parentSection();
    }

    section->setWidth(section->width() + offset);

    if (!section->sections().isEmpty()) {
        auto child_section = section->sections().last();

        while (child_section != nullptr) {
            child_section->setWidth(qMax(20, child_section->width() + offset));

            if (!child_section->sections().isEmpty()) {
                child_section = child_section->sections().last();
            }
            else {
                break;
            }
        }
    }
}
