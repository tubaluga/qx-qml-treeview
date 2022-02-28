#include "qxtreeviewrowdelegatetemplate.h"

QxTreeViewRowDelegateTemplate::QxTreeViewRowDelegateTemplate(QQuickItem *parent) :
    QQuickItem{ parent }
{
}

QxTreeViewTemplate *QxTreeViewRowDelegateTemplate::view() const
{
    return m_view;
}

void QxTreeViewRowDelegateTemplate::setView(QxTreeViewTemplate *newView)
{
    if (m_view == newView)
        return;
    m_view = newView;
    emit viewChanged();
}
