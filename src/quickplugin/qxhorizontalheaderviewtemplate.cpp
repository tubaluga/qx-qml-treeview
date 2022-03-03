#include "qxhorizontalheaderviewtemplate.h"

#include <QQmlContext>
#include <QQmlEngine>

class QxHorizontalHeaderViewTemplatePrivate {
    Q_DECLARE_PUBLIC(QxHorizontalHeaderViewTemplate)

public:
    QxHorizontalHeaderViewTemplatePrivate(QxHorizontalHeaderViewTemplate *parent) :
        q_ptr(parent)
    {
        adaptor = new QxHeaderModelAdaptor(parent);
    }

    void setupFromModel()
    {
        auto source_model = q_ptr->model();

        if (source_model == nullptr) {
            return;
        }

        for (int col = 0; col < source_model->columnCount(); ++col) {
            QxHeaderSection *section = new QxHeaderSection(q_ptr);
            section->setTitle(source_model->headerData(col, Qt::Horizontal).toString());

            qDebug() << section->title();

            q_ptr->appendSection(section);
        }

        q_ptr->invalidate();

        auto leaf_sections = adaptor->root()->leafs();

        foreach (auto leaf, leaf_sections) {
            q_ptr->model()->setHeaderData(leaf->column(), Qt::Horizontal, leaf->width());
            QObject::connect(leaf, &QxHeaderSection::widthChanged, q_ptr, [leaf, this]() {
                q_ptr->model()->setHeaderData(leaf->column(), Qt::Horizontal, leaf->width());
            });
        }
    }

    QxHeaderModelAdaptor *adaptor         = nullptr;
    QxHorizontalHeaderViewTemplate *q_ptr = nullptr;
    int rowCount                          = 0;
    int columnCount                       = 0;
};

QxHorizontalHeaderViewTemplate::QxHorizontalHeaderViewTemplate(QQuickItem *parent) :
    QxHeaderViewTemplate(parent), d_ptr(new QxHorizontalHeaderViewTemplatePrivate(this))
{
}

QxHorizontalHeaderViewTemplate::~QxHorizontalHeaderViewTemplate()
{
    delete d_ptr;
}

void QxHorizontalHeaderViewTemplate::invalidate()
{
    d_ptr->adaptor->setSections(sections());
    setColumnCount(d_ptr->adaptor->root()->leafCount());
    setRowCount(d_ptr->adaptor->root()->maxChildrenDepth());
}

void QxHorizontalHeaderViewTemplate::setupModel(QAbstractItemModel *new_model, QAbstractItemModel *old_model)
{
    d_ptr->setupFromModel();
}

int QxHorizontalHeaderViewTemplate::columnCount() const
{
    return d_ptr->columnCount;
}

void QxHorizontalHeaderViewTemplate::setColumnCount(int newColumnCount)
{
    if (d_ptr->columnCount == newColumnCount) {
        return;
    }

    d_ptr->columnCount = newColumnCount;
    emit columnCountChanged();
}

int QxHorizontalHeaderViewTemplate::rowCount() const
{
    return d_ptr->rowCount;
}

void QxHorizontalHeaderViewTemplate::setRowCount(int newRowCount)
{
    if (d_ptr->rowCount == newRowCount) {
        return;
    }

    d_ptr->rowCount = newRowCount;
    emit rowCountChanged();
}

QxHeaderModelAdaptor *QxHorizontalHeaderViewTemplate::adaptor() const
{
    return d_ptr->adaptor;
}
