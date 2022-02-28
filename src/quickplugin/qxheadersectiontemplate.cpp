#include "qxheadersectiontemplate.h"

QxHeaderSectionTemplate::QxHeaderSectionTemplate(QQuickItem *parent) :
    QQuickItem(parent)
{
}

const QString &QxHeaderSectionTemplate::text() const
{
    return m_text;
}

void QxHeaderSectionTemplate::setText(const QString &newText)
{
    if (m_text == newText) {
        return;
    }

    m_text = newText;

    emit textChanged();
}
