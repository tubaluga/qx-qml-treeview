#include "qxtreeviewmodeldata.h"

QxTreeViewModelData::QxTreeViewModelData(QObject *parent) :
    QObject{ parent }
{
}

const QPersistentModelIndex &QxTreeViewModelData::modelIndex() const
{
    return m_modelIndex;
}

void QxTreeViewModelData::setModelIndex(const QPersistentModelIndex &newModelIndex)
{
    if (m_modelIndex == newModelIndex) {
        return;
    }

    m_modelIndex = newModelIndex;

    update();

    emit modelIndexChanged();
}

const QVariantMap &QxTreeViewModelData::modelData() const
{
    return m_modelData;
}

void QxTreeViewModelData::update()
{
    QVariantMap model_data;

    const auto model = m_modelIndex.model();

    if (model != nullptr) {
        auto data  = model->itemData(m_modelIndex);
        auto names = model->roleNames();

        model_data.insert("displayText", m_modelIndex.data());

        for (auto i = data.begin(); i != data.end(); ++i) {
            if (names.contains(i.key())) {
                model_data.insert(names.value(i.key()), i.value());
            }
        }
    }

    setModelData(model_data);
}

void QxTreeViewModelData::setModelData(const QVariantMap &newModelData)
{
    if (m_modelData == newModelData) {
        return;
    }

    m_modelData = newModelData;
    emit modelDataChanged();
}
