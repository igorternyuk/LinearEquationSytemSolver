#ifndef DOUBLESPINBOXDELEGATE_H
#define DOUBLESPINBOXDELEGATE_H
#include <QDoubleSpinBox>
#include <QItemDelegate>

class DoubleSpinBoxDelegate: public QItemDelegate
{
    Q_OBJECT
public:
    explicit DoubleSpinBoxDelegate(QObject *parent = nullptr);
protected:
     QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const;
     void setEditorData(QWidget *editor, const QModelIndex &index) const;
     void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
     void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &, const QModelIndex &) const;
};

#endif // DOUBLESPINBOXDELEGATE_H
