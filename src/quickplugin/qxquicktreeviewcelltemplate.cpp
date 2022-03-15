#include "qxquicktreeviewcelltemplate.h"

QxQuickTreeViewCellTemplate::QxQuickTreeViewCellTemplate(QQuickItem *parent) :
    QQuickItem{ parent }
{
}

bool QxQuickTreeViewCellTemplate::hovered() const
{
    return m_hovered;
}

void QxQuickTreeViewCellTemplate::setHovered(bool newHovered)
{
    if (m_hovered == newHovered)
        return;
    m_hovered = newHovered;
    emit hoveredChanged();
}
