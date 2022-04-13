#include "qxquickhorizontalheaderviewtemplate.h"
#include "qxquickheadersyncviewmodeladaptor.h"
#include "qxquickheadertreemodeladaptor.h"
#include "qxquicktreeviewtemplate.h"

#include <QQmlContext>
#include <QQmlEngine>

class QxQuickHorizontalHeaderViewTemplatePrivate {
    Q_DECLARE_PUBLIC(QxQuickHorizontalHeaderViewTemplate)

public:
    QxQuickHorizontalHeaderViewTemplatePrivate(QxQuickHorizontalHeaderViewTemplate *parent) :
        q_ptr(parent)
    {
    }

    void bindingAdaptor()
    {
        foreach (const auto &connection, adaptor_connections) {
            QObject::disconnect(connection);
        }

        adaptor_connections << QObject::connect(adaptor, &QxQuickHeaderModelAdaptor::sectionColumnCountChanged, q_ptr, [this]() {
            q_ptr->setColumnCount(adaptor->sectionColumnCount());            
        });

        adaptor_connections << QObject::connect(adaptor, &QxQuickHeaderModelAdaptor::sectionRowCountChanged, q_ptr, [this]() {
            q_ptr->setRowCount(adaptor->sectionRowCount());            
        });
    }

    void bindingSyncView()
    {
        foreach (const auto &connection, view_connections) {
            QObject::disconnect(connection);
        }

        view_connections << QObject::connect(sync_view, &QxQuickTreeViewTemplate::modelChanged, q_ptr, [this]() {
            setSyncViewModel();
        });

        view_connections << QObject::connect(sync_view, &QxQuickTreeViewTemplate::requestResizeColumns, q_ptr, [this]() {
            syncSectionWidth();
        });
    }

    void setSyncViewModel()
    {
        if (q_ptr->model() == nullptr) {
            auto adaptor = new QxQuickHeaderSyncViewModelAdaptor(q_ptr);
            q_ptr->setAdaptor(adaptor);

            if (sync_view) {
                adaptor->setSource(sync_view->model());
            }

            syncSectionWidth();
        }
    }

    void syncSectionWidth()
    {
        if (adaptor && sync_view) {
            foreach (auto section, adaptor->root()->leafs()) {
                sync_view->setColumnWidth(section->column(), section->width());
            }
        }
    }

    QxQuickHeaderModelAdaptor *adaptor         = nullptr;
    QxQuickHorizontalHeaderViewTemplate *q_ptr = nullptr;
    int row_count                         = 0;
    int column_count                      = 0;
    QPointer<QxQuickTreeViewTemplate> sync_view;
    qreal columns_width = 250;
    QVector<QMetaObject::Connection> adaptor_connections;
    QVector<QMetaObject::Connection> view_connections;
    QVector<QMetaObject::Connection> header_view_connections;
};

QxQuickHorizontalHeaderViewTemplate::QxQuickHorizontalHeaderViewTemplate(QQuickItem *parent) :
    QxQuickHeaderViewTemplate(parent), d_ptr(new QxQuickHorizontalHeaderViewTemplatePrivate(this))
{
    setZ(2);    
}

QxQuickHorizontalHeaderViewTemplate::~QxQuickHorizontalHeaderViewTemplate()
{
    delete d_ptr;
}

void QxQuickHorizontalHeaderViewTemplate::setupModel(QAbstractItemModel *new_model, QAbstractItemModel *old_model)
{
    Q_UNUSED(new_model)
    Q_UNUSED(old_model)

    auto tree_adaptor = new QxQuickHeaderTreeModelAdaptor(this);

    tree_adaptor->setSource(model());

    setAdaptor(tree_adaptor);

    d_ptr->syncSectionWidth();
}

int QxQuickHorizontalHeaderViewTemplate::columnCount() const
{
    return d_ptr->column_count;
}

void QxQuickHorizontalHeaderViewTemplate::setColumnCount(int newColumnCount)
{
    if (d_ptr->column_count == newColumnCount) {
        return;
    }

    d_ptr->column_count = newColumnCount;
    emit columnCountChanged();
}

void QxQuickHorizontalHeaderViewTemplate::setAdaptor(QxQuickHeaderModelAdaptor *adaptor)
{
    if (d_ptr->adaptor == adaptor) {
        return;
    }

    if (d_ptr->adaptor) {
        d_ptr->adaptor->deleteLater();
    }

    foreach (const auto &connection, d_ptr->header_view_connections) {
        disconnect(connection);
    }

    d_ptr->adaptor = adaptor;
    d_ptr->adaptor->setSectionDefaultWidth(columnsWidth());

    setColumnCount(d_ptr->adaptor->sectionColumnCount());
    setRowCount(d_ptr->adaptor->sectionRowCount());

    d_ptr->bindingAdaptor();

    emit adaptorChanged();

    d_ptr->header_view_connections << connect(this, &QxQuickHorizontalHeaderViewTemplate::columnsWidthChanged, d_ptr->adaptor, [this]() {
        d_ptr->adaptor->setSectionDefaultWidth(columnsWidth());
    });

    d_ptr->header_view_connections << connect(adaptor, &QxQuickHeaderModelAdaptor::sectionWidthChanged, this, [this](int section, qreal width) {
        if (syncView()) {
            syncView()->setColumnWidth(section, width);
        }
    });    
}

qreal QxQuickHorizontalHeaderViewTemplate::columnsWidth() const
{
    return d_ptr->columns_width;
}

void QxQuickHorizontalHeaderViewTemplate::setColumnsWidth(qreal newDefaultColumnWidth)
{
    if (d_ptr->columns_width == newDefaultColumnWidth) {
        return;
    }

    d_ptr->columns_width = newDefaultColumnWidth;

    if (d_ptr->adaptor) {
        d_ptr->adaptor->setSectionDefaultWidth(newDefaultColumnWidth);
    }

    emit columnsWidthChanged();
}

void QxQuickHorizontalHeaderViewTemplate::setColumnWidth(int section, qreal width)
{
    if (d_ptr->adaptor) {
        d_ptr->adaptor->setColumnWidth(section, width);
    }
}

QxQuickTreeViewTemplate *QxQuickHorizontalHeaderViewTemplate::syncView() const
{
    return d_ptr->sync_view;
}

void QxQuickHorizontalHeaderViewTemplate::setSyncView(QxQuickTreeViewTemplate *newSyncView)
{
    if (d_ptr->sync_view == newSyncView) {
        return;
    }

    d_ptr->sync_view = newSyncView;

    d_ptr->setSyncViewModel();

    d_ptr->syncSectionWidth();
    d_ptr->bindingSyncView();

    emit syncViewChanged();
}

int QxQuickHorizontalHeaderViewTemplate::rowCount() const
{
    return d_ptr->row_count;
}

void QxQuickHorizontalHeaderViewTemplate::setRowCount(int newRowCount)
{
    if (d_ptr->row_count == newRowCount) {
        return;
    }

    d_ptr->row_count = newRowCount;
    emit rowCountChanged();
}

QxQuickHeaderModelAdaptor *QxQuickHorizontalHeaderViewTemplate::adaptor() const
{
    return d_ptr->adaptor;
}
