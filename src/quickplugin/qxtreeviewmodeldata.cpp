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
        auto names = model->roleNames();

        model_data.insert("displayText", m_modelIndex.data());

        for (auto i = names.begin(); i != names.end(); ++i) {
            auto value = m_modelIndex.data(i.key());

            if (!value.isNull()) {
                model_data.insert(i.value(), value);
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
