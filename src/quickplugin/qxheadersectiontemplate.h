#pragma once

#include <QQuickItem>

class QxHeaderSectionTemplate : public QQuickItem {
    Q_OBJECT
    Q_DISABLE_COPY(QxHeaderSectionTemplate)

    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
public:
    QxHeaderSectionTemplate(QQuickItem *parent = nullptr);

    const QString &text() const;
    void setText(const QString &newText);

private:
    QString m_text;

signals:
    void textChanged();
};

Q_DECLARE_METATYPE(QxHeaderSectionTemplate *)
