#include "qxhorizontalheaderviewtemplate.h"
#include "qxheadersyncviewmodeladaptor.h"
#include "qxheadertreemodeladaptor.h"
#include "qxtreeviewtemplate.h"

#include <QQmlContext>
#include <QQmlEngine>

class QxHorizontalHeaderViewTemplatePrivate {
    Q_DECLARE_PUBLIC(QxHorizontalHeaderViewTemplate)

public:
    QxHorizontalHeaderViewTemplatePrivate(QxHorizontalHeaderViewTemplate *parent) :
        q_ptr(parent)
    {
    }

    void bindingAdaptor()
    {
        foreach (const auto &connection, adaptor_connections) {
            QObject::disconnect(connection);
        }

        adaptor_connections << QObject::connect(adaptor, &QxHeaderModelAdaptor::sectionColumnCountChanged, q_ptr, [this]() {
            q_ptr->setColumnCount(adaptor->sectionColumnCount());
            updateDefaultColumnWidth();
        });

        adaptor_connections << QObject::connect(adaptor, &QxHeaderModelAdaptor::sectionRowCountChanged, q_ptr, [this]() {
            q_ptr->setRowCount(adaptor->sectionRowCount());
            updateDefaultColumnWidth();
        });
    }

    void bindingSyncView()
    {
        foreach (const auto &connection, view_connections) {
            QObject::disconnect(connection);
        }

        view_connections << QObject::connect(sync_view, &QxTreeViewTemplate::modelChanged, q_ptr, [this]() {
            setSyncViewModel();
        });
    }

    void setSyncViewModel()
    {
        if (q_ptr->model() == nullptr) {
            auto adaptor = new QxHeaderSyncViewModelAdaptor(q_ptr);
            q_ptr->setAdaptor(adaptor);

            if (sync_view) {
                adaptor->setSource(sync_view->model());
            }

            updateDefaultColumnWidth();
            syncSectionWidth();
        }
    }

    void syncSectionWidth()
    {
        if (adaptor && sync_view && sync_view->model()) {
            foreach (auto section, adaptor->root()->leafs()) {
                sync_view->model()->setHeaderData(section->column(), Qt::Horizontal, section->width());
            }
        }
    }

    void updateDefaultColumnWidth()
    {
        /*if (default_column_width < 1 && sync_view) {
            int defautl_width = sync_view->width() / q_ptr->columnCount();
            q_ptr->setDefaultColumnWidth(defautl_width);
        }*/
    }

    QxHeaderModelAdaptor *adaptor         = nullptr;
    QxHorizontalHeaderViewTemplate *q_ptr = nullptr;
    int row_count                         = 0;
    int column_count                      = 0;
    QPointer<QxTreeViewTemplate> sync_view;
    qreal default_column_width = 0;
    QVector<QMetaObject::Connection> adaptor_connections;
    QVector<QMetaObject::Connection> view_connections;
    QVector<QMetaObject::Connection> header_view_connections;
};

QxHorizontalHeaderViewTemplate::QxHorizontalHeaderViewTemplate(QQuickItem *parent) :
    QxHeaderViewTemplate(parent), d_ptr(new QxHorizontalHeaderViewTemplatePrivate(this))
{
    setZ(2);
}

QxHorizontalHeaderViewTemplate::~QxHorizontalHeaderViewTemplate()
{
    delete d_ptr;
}

void QxHorizontalHeaderViewTemplate::setupModel(QAbstractItemModel *new_model, QAbstractItemModel *old_model)
{
    auto tree_adaptor = new QxHeaderTreeModelAdaptor(this);

    tree_adaptor->setSource(model());

    setAdaptor(tree_adaptor);

    d_ptr->syncSectionWidth();
}

int QxHorizontalHeaderViewTemplate::columnCount() const
{
    return d_ptr->column_count;
}

void QxHorizontalHeaderViewTemplate::setColumnCount(int newColumnCount)
{
    if (d_ptr->column_count == newColumnCount) {
        return;
    }

    d_ptr->column_count = newColumnCount;
    emit columnCountChanged();
}

void QxHorizontalHeaderViewTemplate::setAdaptor(QxHeaderModelAdaptor *adaptor)
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
    d_ptr->adaptor->setSectionDefaultWidth(defaultColumnWidth());

    setColumnCount(d_ptr->adaptor->sectionColumnCount());
    setRowCount(d_ptr->adaptor->sectionRowCount());

    d_ptr->bindingAdaptor();

    emit adaptorChanged();

    d_ptr->header_view_connections << connect(this, &QxHorizontalHeaderViewTemplate::defaultColumnWidthChanged, d_ptr->adaptor, [this]() {
        d_ptr->adaptor->setSectionDefaultWidth(defaultColumnWidth());
    });

    d_ptr->header_view_connections << connect(adaptor, &QxHeaderModelAdaptor::sectionWidthChanged, this, [this](int section, qreal width) {
        if (syncView() && syncView()->model()) {            
            syncView()->model()->setHeaderData(section, Qt::Horizontal, width);
        }
    });

    d_ptr->updateDefaultColumnWidth();
}

qreal QxHorizontalHeaderViewTemplate::defaultColumnWidth() const
{
    return d_ptr->default_column_width;
}

void QxHorizontalHeaderViewTemplate::setDefaultColumnWidth(qreal newDefaultColumnWidth)
{
    if (d_ptr->default_column_width == newDefaultColumnWidth) {
        return;
    }

    d_ptr->default_column_width = newDefaultColumnWidth;

    if (d_ptr->adaptor) {
        d_ptr->adaptor->setSectionDefaultWidth(newDefaultColumnWidth);
    }

    emit defaultColumnWidthChanged();
}

QxTreeViewTemplate *QxHorizontalHeaderViewTemplate::syncView() const
{
    return d_ptr->sync_view;
}

void QxHorizontalHeaderViewTemplate::setSyncView(QxTreeViewTemplate *newSyncView)
{
    if (d_ptr->sync_view == newSyncView) {
        return;
    }

    d_ptr->sync_view = newSyncView;

    d_ptr->updateDefaultColumnWidth();

    d_ptr->setSyncViewModel();

    d_ptr->syncSectionWidth();
    d_ptr->bindingSyncView();

    emit syncViewChanged();
}

int QxHorizontalHeaderViewTemplate::rowCount() const
{
    return d_ptr->row_count;
}

void QxHorizontalHeaderViewTemplate::setRowCount(int newRowCount)
{
    if (d_ptr->row_count == newRowCount) {
        return;
    }

    d_ptr->row_count = newRowCount;
    emit rowCountChanged();
}

QxHeaderModelAdaptor *QxHorizontalHeaderViewTemplate::adaptor() const
{
    return d_ptr->adaptor;
}
