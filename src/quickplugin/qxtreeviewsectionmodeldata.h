#pragma once

#include <QObject>

class QxTreeViewSectionModelData : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(QxTreeViewSectionModelData)

    Q_PROPERTY(qint32 width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)

public:
    explicit QxTreeViewSectionModelData(QObject *parent = nullptr);

    qint32 width() const;
    void setWidth(qint32 newWidth);

    const QString &text() const;
    void setText(const QString &newText);

private:
    qint32 m_width = 150;
    QString m_text;

signals:
    void widthChanged();
    void textChanged();
};

Q_DECLARE_METATYPE(QxTreeViewSectionModelData *)
