#include "qxhorizontalheaderviewtemplate.h"
#include "qxtreeviewtemplate.h"

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

    void createSectionsBySyncView()
    {
        if (!syncView.isNull() && syncView->model() != nullptr && q_ptr->model() == nullptr) {
            q_ptr->clearSections();

            auto source_model = syncView->model();

            if (source_model == nullptr) {
                return;
            }

            for (int col = 0; col < source_model->columnCount(); ++col) {
                QxHeaderSection *section = new QxHeaderSection(q_ptr);
                section->setTitle(source_model->headerData(col, Qt::Horizontal).toString());

                q_ptr->appendSection(section);
            }

            q_ptr->invalidate();

            syncColumnSize();
        }
    }

    void createSectionsByRow(QAbstractItemModel *model, const QModelIndex &index, QxHeaderSection *parent_section)
    {
        for (int row = 0; row < model->rowCount(index); ++row) {
            auto child_index = model->index(row, 0, index);

            QxHeaderSection *section = new QxHeaderSection(parent_section);
            section->setTitle(model->data(child_index).toString());

            if (child_index.isValid()) {
                createSectionsByRow(model, child_index, section);
            }

            if (parent_section == nullptr) {
                q_ptr->appendSection(section);
            }
            else {
                parent_section->appendSection(section);
            }
        }
    }

    void createSectionsFromInternalModel()
    {
        if (q_ptr->model()) {
            q_ptr->clearSections();

            createSectionsByRow(q_ptr->model(), QModelIndex(), nullptr);

            q_ptr->invalidate();

            syncColumnSize();
        }
    }

    void syncColumnSize()
    {
        if (syncView.isNull()) {
            return;
        }

        auto leaf_sections = adaptor->root()->leafs();

        foreach (auto leaf, leaf_sections) {
            if (syncView->model()) {
                syncView->model()->setHeaderData(leaf->column(), Qt::Horizontal, leaf->width());
            }

            QObject::connect(leaf, &QxHeaderSection::widthChanged, q_ptr, [leaf, this]() {
                if (syncView->model()) {
                    syncView->model()->setHeaderData(leaf->column(), Qt::Horizontal, leaf->width());
                }
            });
        }
    }

    void setSyncViewModel(QAbstractItemModel *model)
    {
        if (syncViewModel == model) {
            return;
        }

        if (!syncViewModel.isNull()) {
            QObject::disconnect(syncViewModelConnection);
        }

        syncViewModel = model;

        if (syncViewModel) {
            syncViewModelConnection = QObject::connect(syncViewModel, &QAbstractItemModel::modelReset, q_ptr, [this]() {
                createSectionsBySyncView();
            });

            createSectionsBySyncView();
        }
    }

    QxHeaderModelAdaptor *adaptor         = nullptr;
    QxHorizontalHeaderViewTemplate *q_ptr = nullptr;
    int rowCount                          = 0;
    int columnCount                       = 0;
    QPointer<QAbstractItemModel> syncViewModel;
    QPointer<QxTreeViewTemplate> syncView;
    QMetaObject::Connection modelConnection;
    QMetaObject::Connection syncViewModelConnection;
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
    if (old_model != nullptr) {
        disconnect(d_ptr->modelConnection);
    }

    if (new_model != nullptr) {
        d_ptr->modelConnection = connect(new_model, &QAbstractListModel::modelReset, this, [this]() {
            d_ptr->createSectionsFromInternalModel();
        });
    }

    d_ptr->createSectionsFromInternalModel();
}

void QxHorizontalHeaderViewTemplate::syncViewModelChanged()
{
    if (d_ptr->syncView) {
        d_ptr->setSyncViewModel(d_ptr->syncView->model());
    }
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

QxTreeViewTemplate *QxHorizontalHeaderViewTemplate::syncView() const
{
    return d_ptr->syncView;
}

void QxHorizontalHeaderViewTemplate::setSyncView(QxTreeViewTemplate *newSyncView)
{
    if (d_ptr->syncView == newSyncView) {
        return;
    }

    if (d_ptr->syncView) {
        disconnect(d_ptr->syncView, &QxTreeViewTemplate::modelChanged, this, &QxHorizontalHeaderViewTemplate::syncViewModelChanged);
    }

    d_ptr->syncView = newSyncView;

    if (d_ptr->syncView) {
        connect(d_ptr->syncView, &QxTreeViewTemplate::modelChanged, this, &QxHorizontalHeaderViewTemplate::syncViewModelChanged);
    }

    d_ptr->createSectionsBySyncView();

    emit syncViewChanged();
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
