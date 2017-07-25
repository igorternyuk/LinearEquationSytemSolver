#include "widget.h"
#include "ui_widget.h"
#include <QStandardItemModel>
#include "doublespinboxdelegate.h"
#include "matrix.h"
#include <QFileDialog>
#include <fstream>
#ifdef DEBUG
#include <QDebug>
#endif

using namespace iat;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    mModelA = new QStandardItemModel(this);
    mModelB = new QStandardItemModel(this);
    mModelX = new QStandardItemModel(this);
    ui->tableViewA->setModel(mModelA);
    ui->tableViewB->setModel(mModelB);
    ui->tableViewX->setModel(mModelX);
    ui->tableViewA->setItemDelegate(new DoubleSpinBoxDelegate(this));
    ui->tableViewB->setItemDelegate(new DoubleSpinBoxDelegate(this));
}
Widget::~Widget()
{
    delete ui;
}
void Widget::on_pushButtonSolve_clicked()
{
   mModelX->clear();
   const int matrixARowCount = mModelA->rowCount();
   const int matrixAColumnCount = mModelA->columnCount();
   Matrix<double> matrixA(matrixARowCount, matrixAColumnCount, 0.0);
   for(int i = 0; i < matrixARowCount; ++i)
       for(int j = 0; j < matrixAColumnCount; ++j)
           matrixA[i][j] = getValueAt(mModelA, i, j);
   Matrix<double> matrixB(matrixARowCount, 1, 0.0);
   for(int i = 0; i < matrixARowCount; ++i)
           matrixB[i][0] = getValueAt(mModelB, i, 0);
   //Matrix<double> matrixX = matrixA.inverse() * matrixB;
   Matrix<double> matrixX = matrixA.solveEquationSystem(matrixB);
   mModelX->setRowCount(matrixX.getRowCount());
   mModelX->setColumnCount(1);
   for(int i = 0; i < matrixARowCount; ++i)
           appendTo(mModelX, "X[" + QString::number(i) + "] = " +
           QString::number(matrixX[i][0], 'f', ui->spinBoxPrec->value()));
}
double Widget::getValueAt(QStandardItemModel *model, int i, int j) const
{
    if(!model->item(i,j)) return 0.0;
    else return model->item(i,j)->text().toDouble();
}
QString Widget::getTextAt(QStandardItemModel *model, int i, int j) const
{
    if(!model->item(i,j)) return " ";
    else return model->item(i,j)->text();
}
void Widget::appendTo(QStandardItemModel *model, double value) const
{
    const int rowCount = model->rowCount();
    const int colCount = model->columnCount();
    for(int i = 0; i < rowCount; ++i)
        for(int j = 0; j < colCount; ++j)
        {
            if(!model->item(i, j))
            {
              model->setItem(i, j, new QStandardItem(QString::number(value, 'f', ui->spinBoxPrec->value())));
              return;
            }
        }
}
void Widget::appendTo(QStandardItemModel *model, QString str) const
{
    const int rowCount = model->rowCount();
    const int colCount = model->columnCount();
    for(int i = 0; i < rowCount; ++i)
        for(int j = 0; j < colCount; ++j)
        {
            if(!model->item(i, j))
            {
              model->setItem(i, j, new QStandardItem(str));
              return;
            }
        }
}
void Widget::on_pushButtonExit_clicked()
{
    close();
}
void Widget::on_spinBoxEquationNumber_valueChanged(int arg1)
{
    mModelA->setRowCount(arg1);
    mModelA->setColumnCount(arg1);
    mModelB->setRowCount(arg1);
    mModelB->setColumnCount(1);
    mModelX->setRowCount(arg1);
    mModelX->setColumnCount(1);
}

void Widget::on_pushButtonLoadMatrixFromFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Выберите файл с матрицей коэффициентов СЛАУ ...",
                       QDir::currentPath(), "Текстовые файлы *.txt");
    std::ifstream fi(fileName.toStdString());
    int numberOFEquations;
    fi >> numberOFEquations;
   // mModelA->clear();
    ui->spinBoxEquationNumber->setValue(numberOFEquations);
    for(int i = 0; i < numberOFEquations; ++i)
    {
        for(int j = 0; j < numberOFEquations; ++j)
        {
            double aij;
            fi >> aij;
            appendTo(mModelA, aij);
        }
        double bi;
        fi >> bi;
        appendTo(mModelB, bi);
    }
   fi.close();
}

void Widget::on_pushButtonSaveMatrixToFile_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Выберите путь для сохранения файла с матрицей коэффициентов СЛАУ ...",
                       QDir::currentPath(), "Текстовые файлы *.txt");
    std::ofstream fo(fileName.toStdString());
    fo << mModelA->rowCount() << std::endl;
    for(int i = 0; i < mModelA->rowCount(); ++i)
    {
        for(int j = 0; j < mModelA->rowCount(); ++j)
        {
            fo << getValueAt(mModelA, i, j) << " ";
        }
        fo << getValueAt(mModelB, i, 0)<< std::endl;
    }
   fo.close();
}

void Widget::on_pushButtonSaveResultToFile_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Выберите путь для сохранения решения СЛАУ ...",
                       QDir::currentPath(), "Текстовые файлы *.txt");
    std::ofstream fo(fileName.toStdString());
    for(int i = 0; i < mModelX->rowCount(); ++i)
       fo << "X[" << i+1 << "]= " << getTextAt(mModelX, i, 0).toStdString() << "\n";
   fo.close();
}
