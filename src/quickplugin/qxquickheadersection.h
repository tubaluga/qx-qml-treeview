#pragma once

#include <QObject>
#include <QPersistentModelIndex>
#include <QQmlListProperty>

class QxQuickHeaderSection : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(qreal width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(int rowSpan READ rowSpan WRITE setRowSpan NOTIFY rowSpanChanged)
    Q_PROPERTY(int columnSpan READ columnSpan WRITE setColumnSpan NOTIFY columnSpanChanged)
    Q_PROPERTY(bool isLeaf READ isLeaf NOTIFY isLeafChanged)
    Q_PROPERTY(int depth READ depth NOTIFY depthChanged)
    Q_PROPERTY(int column READ column WRITE setColumn NOTIFY columnChanged)
    Q_PROPERTY(int row READ row WRITE setRow NOTIFY rowChanged)
    Q_PROPERTY(QQmlListProperty<QxQuickHeaderSection> sections READ sectionListProperty CONSTANT)
    Q_PROPERTY(QPersistentModelIndex index READ index WRITE setIndex NOTIFY indexChanged)

public:
    explicit QxQuickHeaderSection(QObject *parent = nullptr);

    QQmlListProperty<QxQuickHeaderSection> sectionListProperty();

    void appendSection(QxQuickHeaderSection *);
    int sectionCount();
    QxQuickHeaderSection *section(int);
    void clearSections();

    const QString &title() const;
    void setTitle(const QString &newTitle);

    qreal width() const;
    void setWidth(qreal newWidth);

    bool isLeaf() const;
    int leafCount() const;
    int depth() const;
    int maxChildrenDepth() const;

    QList<QxQuickHeaderSection *> leafs() const;
    QList<QxQuickHeaderSection *> depthSections(int depth) const;

    QxQuickHeaderSection *parentSection() const;
    void setParentSection(QxQuickHeaderSection *newSectionParent);

    QxQuickHeaderSection *rootSection() const;

    const QList<QxQuickHeaderSection *> &sections() const;

    int rowSpan() const;
    void setRowSpan(int newRowSpan);

    int columnSpan() const;
    void setColumnSpan(int newColumnSpan);

    int column() const;
    void setColumn(int newColumn);

    int row() const;
    void setRow(int newRow);

    void invalidate();

    const QPersistentModelIndex &index() const;
    void setIndex(const QPersistentModelIndex &newIndex);

protected:
    void resize();
    QxQuickHeaderSection *findFirstLeafSection();

signals:
    void titleChanged();
    void widthChanged();
    void rowSpanChanged();
    void columnSpanChanged();
    void columnChanged();
    void rowChanged();
    void isLeafChanged();
    void depthChanged();

    void indexChanged();

private:
    static void appendSection(QQmlListProperty<QxQuickHeaderSection> *, QxQuickHeaderSection *);
    static int sectionCount(QQmlListProperty<QxQuickHeaderSection> *);
    static QxQuickHeaderSection *section(QQmlListProperty<QxQuickHeaderSection> *, int);
    static void clearSections(QQmlListProperty<QxQuickHeaderSection> *);

private:
    QString m_title;
    qreal m_width                    = 0;
    int m_column                     = 0;
    int m_row                        = 0;
    int m_rowSpan                    = 1;
    int m_columnSpan                 = 1;
    QxQuickHeaderSection *m_parentSection = nullptr;
    QList<QxQuickHeaderSection *> m_sections;
    QPersistentModelIndex m_index;
};

Q_DECLARE_METATYPE(QxQuickHeaderSection *)
