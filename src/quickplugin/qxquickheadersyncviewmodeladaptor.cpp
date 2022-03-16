#include "qxquickheadersyncviewmodeladaptor.h"

QxQuickHeaderSyncViewModelAdaptor::QxQuickHeaderSyncViewModelAdaptor(QObject *parent) :
    QxQuickHeaderModelAdaptor{ parent }
{
}

void QxQuickHeaderSyncViewModelAdaptor::createSections()
{
    auto source_model = source();

    if (source_model == nullptr) {
        return;
    }

    QList<QxQuickHeaderSection *> section_list;

    for (int col = 0; col < source_model->columnCount(); ++col) {
        QxQuickHeaderSection *section = new QxQuickHeaderSection();
        section->setTitle(source_model->headerData(col, Qt::Horizontal).toString());

        auto header_width = source_model->headerData(col, Qt::Horizontal, Qt::EditRole);

        if (!header_width.isNull()) {
            section->setWidth(header_width.toInt());
        }

        section_list << section;
    }

    setSections(section_list);

    invalidate();

    updateColumnSize();
}

void QxQuickHeaderSyncViewModelAdaptor::onSourceModelChanged(QAbstractItemModel *new_model, QAbstractItemModel *old_model)
{
    Q_UNUSED(new_model)
    Q_UNUSED(old_model)

    foreach (const auto &connection, m_connections) {
        disconnect(connection);
    }

    auto source_model = source();

    if (source_model) {
        m_connections << QObject::connect(source_model, &QAbstractItemModel::modelReset, this, [source_model, this]() {
            createSections();
        });

        m_connections << QObject::connect(source_model, &QAbstractListModel::headerDataChanged, this, [this, source_model](Qt::Orientation orientation, int first, int last) {
            if (orientation == Qt::Horizontal) {
                auto columns = root()->leafs();

                int column_index = first;

                while (column_index < last + 1 && column_index > -1 && column_index < columns.size()) {
                    auto section = columns.at(column_index);
                    section->setTitle(source_model->headerData(column_index, orientation).toString());

                    auto header_width = source_model->headerData(column_index, orientation, Qt::EditRole);

                    if (!header_width.isNull()) {
                        section->setWidth(header_width.toInt());
                    }
                    ++column_index;
                }
            }
        });
    }

    createSections();
}
