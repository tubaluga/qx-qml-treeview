#pragma once

#include <QList>
#include <QQuickItem>

class QxHeaderSection : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(int m_width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(int rowSpan READ rowSpan WRITE setRowSpan NOTIFY rowSpanChanged)
    Q_PROPERTY(int columnSpan READ columnSpan WRITE setColumnSpan NOTIFY columnSpanChanged)
    Q_PROPERTY(QQmlListProperty<QxHeaderSection> sections READ sectionListProperty CONSTANT)

public:
    explicit QxHeaderSection(QObject *parent = nullptr);

    QQmlListProperty<QxHeaderSection> sectionListProperty();

    void appendSection(QxHeaderSection *);
    int sectionCount();
    QxHeaderSection *section(int);
    void clearSections();

    const QString &title() const;
    void setTitle(const QString &newTitle);

    int width() const;
    void setWidth(int newWidth);

    bool isLeaf() const;
    int leafCount() const;
    int depth() const;

    QList<QxHeaderSection *> leafs() const;

    QxHeaderSection *parentSection() const;
    void setParentSection(QxHeaderSection *newSectionParent);

    QxHeaderSection *rootSection() const;

    const QList<QxHeaderSection *> &sections() const;

    int rowSpan() const;
    void setRowSpan(int newRowSpan);

    int columnSpan() const;
    void setColumnSpan(int newColumnSpan);

    int column() const;
    void setColumn(int newColumn);

    int row() const;
    void setRow(int newRow);

    void invalidate();

protected:
    void resize();

signals:
    void titleChanged();
    void widthChanged();
    void rowSpanChanged();
    void columnSpanChanged();
    void columnChanged();
    void rowChanged();

private:
    static void appendSection(QQmlListProperty<QxHeaderSection> *, QxHeaderSection *);
    static int sectionCount(QQmlListProperty<QxHeaderSection> *);
    static QxHeaderSection *section(QQmlListProperty<QxHeaderSection> *, int);
    static void clearSections(QQmlListProperty<QxHeaderSection> *);

private:
    QString m_title;
    int m_width                      = 100;
    int m_column                     = 0;
    int m_row                        = 0;
    int m_rowSpan                    = 1;
    int m_columnSpan                 = 1;
    QxHeaderSection *m_parentSection = nullptr;
    QList<QxHeaderSection *> m_sections;
    Q_PROPERTY(int column READ column WRITE setColumn NOTIFY columnChanged)
    Q_PROPERTY(int row READ row WRITE setRow NOTIFY rowChanged)
};

Q_DECLARE_METATYPE(QxHeaderSection *)
