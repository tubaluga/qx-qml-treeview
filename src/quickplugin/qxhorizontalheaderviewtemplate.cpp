#include "qxhorizontalheaderviewtemplate.h"

#include <QtQuick/private/qquickpositioners_p.h>

#include <QQmlContext>
#include <QQmlEngine>
#include <QTimer>

class QxHorizontalHeaderViewTemplatePrivate {
    Q_DECLARE_PUBLIC(QxHorizontalHeaderViewTemplate)

public:
    QxHorizontalHeaderViewTemplatePrivate(QxHorizontalHeaderViewTemplate *parent) :
        q_ptr(parent)
    {
        gridItem = new QQuickGrid(q_ptr);
    }

    QQuickGrid *gridItem;

    QxHorizontalHeaderViewTemplate *q_ptr = nullptr;
};

QxHorizontalHeaderViewTemplate::QxHorizontalHeaderViewTemplate(QQuickItem *parent) :
    QxHeaderViewTemplate(parent)
{
    m_adaptor = new QxHeaderModelAdaptor(this);
    //m_adaptor->setRoot(rootSection());
}

void QxHorizontalHeaderViewTemplate::componentComplete()
{
    QxHeaderViewTemplate::componentComplete();
}

void QxHorizontalHeaderViewTemplate::invalidate()
{
    m_adaptor->setSections(sections());

    /*qDeleteAll(m_sections.begin(), m_sections.end());

    m_sections.clear();

    if (!m_treeMode) {
        int pos = 0, index = 0;
        for (int column = 0; column < m_model->columnCount(); ++column) {
            QQmlContext *context = new QQmlContext(m_sectionDelegate->creationContext());

            QxTreeViewSectionModelData *section_data = new QxTreeViewSectionModelData(this);

            section_data->setText(m_model->headerData(column, Qt::Horizontal, displayTextRole()).toString());

            context->setContextProperty("headerView", this);
            context->setContextProperty("sectionData", section_data);
            context->setContextProperty("index", index++);

            auto section_item = qobject_cast<QQuickItem *>(m_sectionDelegate->beginCreate(context));

            if (section_item) {
                section_item->setParentItem(this);

                section_item->setX(pos);
                section_item->setWidth(m_model->headerData(column, Qt::Horizontal, Qt::EditRole).toDouble());

                pos += section_item->width();
            }

            m_sectionDelegate->completeCreate();

            m_sections << new Section(section_item, section_data);

            connect(section_item, &QQuickItem::implicitHeightChanged, this, &QxHorizontalHeaderViewTemplate::invalidateHeaderHeight);
        }
    }
    else {
        int position = 0;
        for (int row = 0; row < m_model->rowCount(); ++row) {
            QModelIndex index = m_model->index(row, 0);
            createTreeHeaderSection(position, index, nullptr);
        }
    }

    invalidateHeaderHeight();*/
}

QxHeaderModelAdaptor *QxHorizontalHeaderViewTemplate::adaptor() const
{
    return m_adaptor;
}
/*
void QxHorizontalHeaderViewTemplate::invalidateHeaderRowHeigh(int row)
{
    qreal max_height = 0;

    QVector<Section *> row_sections;

    foreach (auto section, m_sections) {
        if (section->row() == row) {
            max_height = qMax(section->item->implicitHeight(), max_height);
            row_sections << section;
        }
    }

    foreach (auto section, row_sections) {
        section->item->setHeight(max_height);
    }
}

void QxHorizontalHeaderViewTemplate::invalidateHeaderHeight()
{
    int row_count = 0;

    foreach (auto section, m_sections) {
        row_count = qMax(section->row() + 1, row_count);
    }

    for (int i = 0; i < row_count; ++i) {
        invalidateHeaderRowHeigh(i);
    }
}

void QxHorizontalHeaderViewTemplate::headerDataChanged(Qt::Orientation orientation, int first, int last)
{
    if (orientation == Qt::Horizontal && !m_treeMode) {
        int section_index = first;

        if (section_index > -1 && section_index < m_sections.size()) {
            auto section = m_sections[section_index];

            section->itemData->setText(m_model->headerData(section_index, Qt::Horizontal, displayTextRole()).toString());
        }
    }
}

void QxHorizontalHeaderViewTemplate::createTreeHeaderSection(int &position, const QModelIndex &index, Section *parent_section)
{
    QQmlContext *context = new QQmlContext(m_sectionDelegate->creationContext());

    QxTreeViewSectionModelData *section_data = new QxTreeViewSectionModelData(this);

    section_data->setText(index.data(displayTextRole()).toString());

    context->setContextProperty("headerView", this);
    context->setContextProperty("sectionData", section_data);

    auto section_item = qobject_cast<QQuickItem *>(m_sectionDelegate->beginCreate(context));

    qreal y_position = 0;

    if (parent_section != nullptr) {
        y_position = parent_section->item->y() + parent_section->item->height();
    }

    if (section_item) {
        section_item->setParentItem(this);

        section_item->setX(position);
        section_item->setY(y_position);

        position += section_item->width();

        qDebug() << "position" << position;
    }

    m_sectionDelegate->completeCreate();

    auto section    = new Section(section_item, section_data);
    section->parent = parent_section;

    m_sections << section;

    int pos = 0;
    for (int row = 0; row < m_model->rowCount(index); ++row) {
        createTreeHeaderSection(pos, m_model->index(row, 0, index), section);
    }
}
*/
