#include "qxtreeviewsectionmodeldata.h"

QxTreeViewSectionModelData::QxTreeViewSectionModelData(QObject *parent)
    : QObject{parent}
{
}

qint32 QxTreeViewSectionModelData::width() const
{
    return m_width;
}

void QxTreeViewSectionModelData::setWidth(qint32 newWidth)
{
    if (m_width == newWidth) {
        return;
    }

    m_width = newWidth;

    emit widthChanged();
}

const QString &QxTreeViewSectionModelData::text() const
{
    return m_text;
}

void QxTreeViewSectionModelData::setText(const QString &newText)
{
    if (m_text == newText) {
        return;
    }

    m_text = newText;
    emit textChanged();
}
