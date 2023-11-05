#include "newtableinputdialog.h"
#include "ui_newtableinputdialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QSet>
#include <QMessageBox>
#include <QLabel>

NewTableInputDialog::NewTableInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewTableInputDialog)
{
    ui->setupUi(this);
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollAreaWidgetContents->setLayout(ui->verticalLayout);

    ui->verticalLayout->setAlignment(Qt::AlignTop);
    ui->scrollAreaWidgetContents->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    addRow();
}

NewTableInputDialog::~NewTableInputDialog()
{
    delete ui;
}



void NewTableInputDialog::on_buttonBox_rejected()
{
    reject();
}


QList<ColumnSet::ColumnData> NewTableInputDialog::getColumnData()
{
    QList<ColumnSet::ColumnData> columnData;

    int rowCount = ui->verticalLayout->count();

       for (int i = 0; i < rowCount; ++i)
       {
           QWidget *widget = ui->verticalLayout->itemAt(i)->widget();
           if (widget) {
                 QHBoxLayout *rowLayout = dynamic_cast<QHBoxLayout*>(widget->layout());


           if (rowLayout)
           {
               QLineEdit* columnNameEdit = qobject_cast<QLineEdit*>(rowLayout->itemAt(1)->widget());
               QComboBox* columnTypeCombo = qobject_cast<QComboBox*>(rowLayout->itemAt(3)->widget());
               QCheckBox* isPKCheckBox = qobject_cast<QCheckBox*>(rowLayout->itemAt(4)->widget());
               QCheckBox* isNotNullCheckBox = qobject_cast<QCheckBox*>(rowLayout->itemAt(5)->widget());

               if (columnNameEdit && columnTypeCombo && isPKCheckBox && isNotNullCheckBox)
               {
                   QString columnName = columnNameEdit->text();
                   QString columnType = columnTypeCombo->currentText();
                   bool isPK = isPKCheckBox->isChecked();
                   bool notNull = isNotNullCheckBox->isChecked();

                   columnData.append({columnName, columnType, isPK, notNull});
               }
           }
        }
       }
    return columnData;
}

void NewTableInputDialog::addRow()
{
    QWidget *cont = new QWidget(ui->scrollAreaWidgetContents);
    QString number = QString::number(ui->verticalLayout->count()+1);
    QHBoxLayout* rowLayout = new QHBoxLayout(cont);

    QLabel *columnLabel  = new QLabel("Column " + number + "  Name: ");
    QLabel *typeLabel  = new QLabel("Type: ");
    QLineEdit* columnNameEdit = new QLineEdit(cont);
    QComboBox* columnTypeCombo = new QComboBox(cont);
    columnNameEdit->setMinimumHeight(15);
    columnTypeCombo->setMinimumHeight(15);

    for (QString type : ColumnSet::ColumnTypes)
        columnTypeCombo->addItem(type);

    QCheckBox* isPKCheckBox = new QCheckBox("PK", cont);
    QCheckBox* isNotNullCheckBox = new QCheckBox("NotNull", cont);
    isPKCheckBox->setMinimumHeight(15);
    isNotNullCheckBox->setMinimumHeight(15);

    rowLayout->addWidget(columnLabel);
    rowLayout->addWidget(columnNameEdit);
    rowLayout->addWidget(typeLabel);
    rowLayout->addWidget(columnTypeCombo);
    rowLayout->addWidget(isPKCheckBox);
    rowLayout->addWidget(isNotNullCheckBox);

    cont->setMinimumHeight(40);
    cont->setMinimumWidth(600);
    cont->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    ui->verticalLayout->addWidget(cont);
}

void NewTableInputDialog::on_spinBox_valueChanged(int value)
{
    int rowCount = ui->verticalLayout->count();
    while(value > rowCount){
        addRow();
        rowCount =  ui->verticalLayout->count();
    }
    while(value < rowCount){
        QLayoutItem* lastItem = ui->verticalLayout->takeAt(rowCount - 1);

        if (lastItem){
            QWidget* lastWidget = lastItem->widget();
            if (lastWidget) {
                ui->verticalLayout->removeItem(lastItem);
                delete lastWidget;
            }
        }
        rowCount = ui->verticalLayout->count();
    }

}


/*
void NewTableInputDialog::on_buttonBox_accepted()
{
    QSet<QString> columnNames;

    int rowCount = ui->verticalLayout->count();

       for (int i = 0; i < rowCount; ++i)
       {
           QWidget *widget = ui->verticalLayout->itemAt(i)->widget();
           if (widget) {
                 QHBoxLayout *rowLayout = dynamic_cast<QHBoxLayout*>(widget->layout());

                if (rowLayout){
                    QLineEdit* columnNameEdit = qobject_cast<QLineEdit*>(rowLayout->itemAt(1)->widget());
                    QCheckBox* isPKCheckBox = qobject_cast<QCheckBox*>(rowLayout->itemAt(4)->widget());
                    QCheckBox* isNotNullCheckBox = qobject_cast<QCheckBox*>(rowLayout->itemAt(5)->widget());

                    QString columnName = columnNameEdit->text();
                    if (columnName.isEmpty()){
                        QMessageBox::critical(this, "Error", "Column name cannot be empty.");
                        done(QDialog::Rejected);
                     return;
                    }
                    if (isPKCheckBox->isChecked() && !isNotNullCheckBox->isChecked()){
                        QMessageBox::critical(this, "Error", "Private key columns must be not null");
                        done(QDialog::Rejected);
                        return;
                    }
                    columnNames.insert(columnName);
                }
           }
       }

    if (rowCount != columnNames.size()){
        QMessageBox::critical(this, "Error", "The columns names must be unique.");
        done(QDialog::Rejected);
        return;
    }
    QDialog::accept();
}
*/

void NewTableInputDialog::on_okButton_clicked()
{
    QSet<QString> columnNames;

    int rowCount = ui->verticalLayout->count();

       for (int i = 0; i < rowCount; ++i)
       {
           QWidget *widget = ui->verticalLayout->itemAt(i)->widget();
           if (widget) {
                 QHBoxLayout *rowLayout = dynamic_cast<QHBoxLayout*>(widget->layout());

                if (rowLayout){
                    QLineEdit* columnNameEdit = qobject_cast<QLineEdit*>(rowLayout->itemAt(1)->widget());
                    QCheckBox* isPKCheckBox = qobject_cast<QCheckBox*>(rowLayout->itemAt(4)->widget());
                    QCheckBox* isNotNullCheckBox = qobject_cast<QCheckBox*>(rowLayout->itemAt(5)->widget());

                    QString columnName = columnNameEdit->text();
                    if (columnName.isEmpty()){
                        QMessageBox::critical(this, "Error", "Column name cannot be empty.");
                     return;
                    }
                    if (isPKCheckBox->isChecked() && !isNotNullCheckBox->isChecked()){
                        QMessageBox::critical(this, "Error", "Private key columns must be not null");
                        return;
                    }
                    columnNames.insert(columnName);
                }
           }
       }

    if (rowCount != columnNames.size()){
        QMessageBox::critical(this, "Error", "The columns names must be unique.");
        return;
    }
    accept();
}

