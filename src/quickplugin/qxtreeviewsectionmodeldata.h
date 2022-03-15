#pragma once

#include <QObject>

class QxTreeViewSectionModelData : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(QxTreeViewSectionModelData)

    Q_PROPERTY(qreal width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)

public:
    explicit QxTreeViewSectionModelData(QObject *parent = nullptr);

    qreal width() const;
    void setWidth(qreal newWidth);

    const QString &text() const;
    void setText(const QString &newText);

private:
    qreal m_width = 150;
    QString m_text;

signals:
    void widthChanged();
    void textChanged();
};

Q_DECLARE_METATYPE(QxTreeViewSectionModelData *)
