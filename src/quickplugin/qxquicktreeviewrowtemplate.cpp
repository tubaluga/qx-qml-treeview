#include "qxquicktreeviewrowtemplate.h"

QxQuickTreeViewRowTemplate::QxQuickTreeViewRowTemplate(QQuickItem *parent) :
    QQuickItem{ parent }
{
}

QxTreeViewTemplate *QxQuickTreeViewRowTemplate::view() const
{
    return m_view;
}

void QxQuickTreeViewRowTemplate::setView(QxTreeViewTemplate *newView)
{
    if (m_view == newView) {
        return;
    }

    if (!m_view.isNull()) {
        disconnect(m_view, &QxTreeViewTemplate::modelChanged, this, &QxQuickTreeViewRowTemplate::didModelChanged);
    }

    m_view = newView;

    if (!m_view.isNull()) {
        connect(m_view, &QxTreeViewTemplate::modelChanged, this, &QxQuickTreeViewRowTemplate::didModelChanged);
    }

    if (m_view->model()) {
        didModelChanged();
    }

    emit viewChanged();
}

int QxQuickTreeViewRowTemplate::columnCount() const
{
    if (m_view.isNull() || m_view->model() == nullptr) {
        return 0;
    }

    return m_view->model()->columnCount();
}

void QxQuickTreeViewRowTemplate::didModelChanged()
{
    disconnect(m_modelChangedConnection);

    if (!m_view.isNull()) {
        m_modelChangedConnection = connect(m_view->model(), &QAbstractItemModel::modelReset, this, &QxQuickTreeViewRowTemplate::columnCountChanged);
    }

    emit columnCountChanged();
}
