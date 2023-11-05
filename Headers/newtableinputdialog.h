#ifndef NEWTABLEINPUTDIALOG_H
#define NEWTABLEINPUTDIALOG_H

#include <QDialog>
#include <QFormLayout>
#include "columnset.h"
#include <QAbstractButton>

namespace Ui {
class NewTableInputDialog;
}

class NewTableInputDialog : public QDialog
{
    Q_OBJECT
    QFormLayout* layout;

public:
    explicit NewTableInputDialog(QWidget *parent = nullptr);
    ~NewTableInputDialog();

    QList<ColumnSet::ColumnData> getColumnData(); // Pair: Column Name, Column Type

private slots:
    void on_buttonBox_rejected();
    void on_spinBox_valueChanged(int arg1);
    //void on_buttonBox_accepted();
    void on_okButton_clicked();

private:
    Ui::NewTableInputDialog *ui;
    void setupColumnInputs(int count);
    void addRow();
};

#endif // NEWTABLEINPUTDIALOG_H
