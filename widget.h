#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QStandardItemModel;
namespace Ui
{
   class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButtonSolve_clicked();
    void on_pushButtonExit_clicked();
    void on_spinBoxEquationNumber_valueChanged(int arg1);
    double getValueAt(QStandardItemModel *model, int i, int j) const;
    QString getTextAt(QStandardItemModel *model, int i, int j) const;
    void appendTo(QStandardItemModel *model, double value) const;
    void appendTo(QStandardItemModel *model, QString str) const;
    void on_pushButtonLoadMatrixFromFile_clicked();
    void on_pushButtonSaveMatrixToFile_clicked();
    void on_pushButtonSaveResultToFile_clicked();

private:
    Ui::Widget *ui;
    QStandardItemModel *mModelA;
    QStandardItemModel *mModelX;
    QStandardItemModel *mModelB;
};

#endif // WIDGET_H
