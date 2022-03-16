#include "qxquicktreeviewrowtemplate.h"

QxQuickTreeViewRowTemplate::QxQuickTreeViewRowTemplate(QQuickItem *parent) :
    QQuickItem{ parent }
{
}

QxQuickTreeViewTemplate *QxQuickTreeViewRowTemplate::view() const
{
    return m_view;
}

void QxQuickTreeViewRowTemplate::setView(QxQuickTreeViewTemplate *newView)
{
    if (m_view == newView) {
        return;
    }

    m_view = newView;

    emit viewChanged();

    emit adaptorChanged();
}

QxQuickTreeModelAdaptor *QxQuickTreeViewRowTemplate::adaptor() const
{
    return m_view.isNull() ? nullptr : m_view->adaptor();
}
