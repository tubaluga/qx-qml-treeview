#include "qxtreeviewtemplate.h"

QxTreeViewTemplate::QxTreeViewTemplate(QQuickItem *parent) :
    QQuickItem{ parent }
{
}

QAbstractItemModel *QxTreeViewTemplate::model() const
{
    return m_model;
}

void QxTreeViewTemplate::setModel(QAbstractItemModel *newModel)
{
    if (m_model == newModel) {
        return;
    }

    if (!m_model.isNull()) {
        disconnect(m_model, &QAbstractItemModel::headerDataChanged, this, &QxTreeViewTemplate::modelHeaderDataChanged);
        disconnect(m_model, &QAbstractItemModel::modelReset, this, &QxTreeViewTemplate::invalidate);
    }

    m_model = newModel;

    if (!m_model.isNull()) {
        connect(m_model, &QAbstractItemModel::headerDataChanged, this, &QxTreeViewTemplate::modelHeaderDataChanged);
        connect(m_model, &QAbstractItemModel::modelReset, this, &QxTreeViewTemplate::invalidate);
    }

    invalidate();

    emit modelChanged();
}

QxTreeViewSectionModelData *QxTreeViewTemplate::sectionData(int section) const
{
    if (section > -1 && section < m_sectionModels.size()) {
        return m_sectionModels[section];
    }

    return nullptr;
}

void QxTreeViewTemplate::modelHeaderDataChanged(Qt::Orientation orientation, int first, int last)
{
    if (orientation == Qt::Horizontal && first > -1 && first < m_sectionModels.size()) {
        m_sectionModels[first]->setWidth(m_model->headerData(first, orientation, Qt::EditRole).toDouble());
    }
}

void QxTreeViewTemplate::invalidate()
{
    if (m_model.isNull()) {
        return;
    }

    foreach (auto section_data, m_sectionModels) {
        section_data->deleteLater();
    }

    m_sectionModels.clear();

    for (int i = 0; i < m_model->columnCount(); ++i) {
        QxTreeViewSectionModelData *data = new QxTreeViewSectionModelData(this);

        const auto section_size = m_model->headerData(i, Qt::Horizontal, Qt::EditRole);

        if (!section_size.isNull()) {
            data->setWidth(section_size.toDouble());
        }
        else {
            data->setWidth(100);
        }

        m_sectionModels << data;
    }
}
