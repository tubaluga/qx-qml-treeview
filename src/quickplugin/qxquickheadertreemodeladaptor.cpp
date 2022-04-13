#include "qxquickheadertreemodeladaptor.h"

QxQuickHeaderTreeModelAdaptor::QxQuickHeaderTreeModelAdaptor(QObject *parent) :
    QxQuickHeaderModelAdaptor{ parent }
{
}

void QxQuickHeaderTreeModelAdaptor::createSections()
{
    m_sectionCache.clear();

    QList<QxQuickHeaderSection *> section_list;
    createSectionsByRow(section_list, source(), QModelIndex(), nullptr);

    setSections(section_list);

    invalidate();

    updateColumnSize();
}

void QxQuickHeaderTreeModelAdaptor::createSectionsByRow(QList<QxQuickHeaderSection *> &root_sections, QAbstractItemModel *model, const QModelIndex &index, QxQuickHeaderSection *parent_section)
{
    for (int row = 0; row < model->rowCount(index); ++row) {
        auto child_index = model->index(row, 0, index);

        QxQuickHeaderSection *section = new QxQuickHeaderSection(parent_section);
        section->setTitle(model->data(child_index).toString());
        section->setIndex(child_index);

        m_sectionCache.insert(child_index, section);

        if (child_index.isValid()) {
            createSectionsByRow(root_sections, model, child_index, section);
        }

        if (parent_section == nullptr) {
            root_sections << section;
        }
        else {
            parent_section->appendSection(section);
        }
    }
}

void QxQuickHeaderTreeModelAdaptor::onSourceModelChanged(QAbstractItemModel *new_model, QAbstractItemModel *old_model)
{
    Q_UNUSED(new_model)
    Q_UNUSED(old_model)

    foreach (const auto &connection, m_connections) {
        QObject::disconnect(connection);
    }

    if (source()) {
        createSections();

        m_connections << QObject::connect(source(), &QAbstractListModel::modelReset, this, &QxQuickHeaderTreeModelAdaptor::createSections);
        m_connections << QObject::connect(source(), &QAbstractListModel::dataChanged, this, [this](const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles) {
            Q_UNUSED(bottomRight)
            Q_UNUSED(roles)

            auto section = m_sectionCache.value(topLeft);
            section->setTitle(topLeft.data().toString());
        });
    }
}
