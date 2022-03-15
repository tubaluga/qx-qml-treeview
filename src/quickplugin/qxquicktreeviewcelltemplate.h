#pragma once

#include <QQuickItem>

class QxQuickTreeViewCellTemplate : public QQuickItem {
    Q_OBJECT
    Q_DISABLE_COPY(QxQuickTreeViewCellTemplate)

    Q_PROPERTY(bool hovered READ hovered WRITE setHovered NOTIFY hoveredChanged)
public:
    explicit QxQuickTreeViewCellTemplate(QQuickItem *parent = nullptr);

    bool hovered() const;
    void setHovered(bool newHovered);

signals:
    void hoveredChanged();

private:
    bool m_hovered = false;
};

Q_DECLARE_METATYPE(QxQuickTreeViewCellTemplate *)
