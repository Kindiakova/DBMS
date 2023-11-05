// databasewindow.cpp
#include "databasewindow.h"
#include <QInputDialog>
#include <QCloseEvent>
#include <QMessageBox>
#include "ui_mainwindow.h"
#include "newtableinputdialog.h"
#include "table.h"
#include <QHeaderView>
#include <QFileDialog>

DatabaseWindow::DatabaseWindow(QWidget *parent, DataBase *database)
    : QMainWindow(parent)
{
    DB = database;
    setWindowTitle("DBMS :: " + database->getName());
    // Create menu bar
    QMenu *fileMenu = menuBar()->addMenu("File");
    QAction *saveAction = fileMenu->addAction("Save Database");
    connect(saveAction, &QAction::triggered, this, [&](){
        saveDatabase(DB->getFilePath());});

    QAction *saveAsAction = fileMenu->addAction("Save Database As");
    connect(saveAsAction, &QAction::triggered, this, [&](){
        saveDatabase();});

    QAction *closeAction = fileMenu->addAction("Close Database");
    connect(closeAction, &QAction::triggered, this, [&](){
        closeDatabase();});

    QAction *deleteAction = fileMenu->addAction("Delete Database");
    connect(deleteAction, &QAction::triggered, this, [&](){
        deleteDatabase();});

    // Create list widget
    listWidget = new QListWidget(this);
    listWidget->setFixedWidth(200);

    for (int i = 0; i < DB->countTables(); ++i){
       listWidget->addItem(DB->getTable(i)->getName());
    }

    // Create button to add a new table
    QPushButton *addButton = new QPushButton("Add table", this);
    addButton->setFixedWidth(listWidget->width());
    QPushButton *addRowButton = new QPushButton("Add row", this);
    QPushButton *deleteTableButton = new QPushButton("Delete table", this);

    addButton->setFixedWidth(listWidget->width());

    QHBoxLayout * HButtonlayout = new QHBoxLayout(this);
    HButtonlayout->addWidget(addRowButton);
    HButtonlayout->addWidget(deleteTableButton);

    // Create table widget
    tableWidget = new QTableWidget(this);
    connect(tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(onItemChanged(QTableWidgetItem*)));
    connect(tableWidget->horizontalHeader(), SIGNAL(sectionDoubleClicked(int)), this, SLOT(onHeaderDoubleClicked(int)));

    QVBoxLayout * VTablelayout = new QVBoxLayout(this);

    VTablelayout->addWidget(tableWidget);
    VTablelayout->addLayout(HButtonlayout);

    // Set up layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout * Vlayout = new QVBoxLayout(this);

    Vlayout->addWidget(listWidget);
    Vlayout->addWidget(addButton);

    QHBoxLayout *layout = new QHBoxLayout(this);


    layout->addLayout(Vlayout);
    layout->addLayout(VTablelayout);

    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    // Connect signals and slots
    connect(listWidget, &QListWidget::itemDoubleClicked, this, &DatabaseWindow::onListWidgetItemDoubleClicked);
    connect(addButton, &QPushButton::clicked, this, &DatabaseWindow::onAddTableButtonClicked);
    connect(addRowButton, &QPushButton::clicked, this, &DatabaseWindow::onaddRowButtonClicked);
    connect(deleteTableButton, &QPushButton::clicked, this, &DatabaseWindow::ondeleteTableButtonClicked);

}
void DatabaseWindow::clearTable(){
    tableWidget->clearContents();
    tableWidget->clear();
    tableWidget->setRowCount(0);
    tableWidget->setColumnCount(0);
}

void DatabaseWindow::addEmptyRow(){
    int row = tableWidget->rowCount();
    tableWidget->insertRow(row);
    for (int j = 0; j < currTable->countColumns(); ++j){
        QTableWidgetItem *item = new QTableWidgetItem("");
        tableWidget->setItem(row, j, item);
    }
}

void DatabaseWindow::onListWidgetItemDoubleClicked(QListWidgetItem *item) {
    clearTable();
    currTable = DB->getTable(listWidget->row(item));

    tableWidget->setColumnCount(currTable->countColumns()+1);
    tableWidget->setRowCount(currTable->countRows());

    QList<QString> headers = currTable->getColumnNames();
    headers.append("Delete");
    tableWidget->setHorizontalHeaderLabels(headers);


    for (int i = 0; i < currTable->countRows(); ++i) {
        for (int j = 0; j < currTable->countColumns(); ++j) {
            qDebug() << i<< " " <<j;
            QTableWidgetItem *item = new QTableWidgetItem(currTable->getCell(i, j));
            tableWidget->setItem(i, j, item);
        }

        QPushButton *del = new QPushButton("X", tableWidget);
        connect(del, SIGNAL(clicked()), this, SLOT(onDeleteRowButtonClicked()));

        tableWidget->setCellWidget(i, currTable->countColumns(), del);
    }

    tableWidget->resizeColumnsToContents();
    addEmptyRow();
}

void DatabaseWindow::onItemChanged(QTableWidgetItem *item)
{
    int col = item->column(), row = item->row();
    QString errorH, errorT, newVal = item->text();
    QString oldVal = currTable->getCell(row, col);
    bool ok = currTable->getColumn(col)->checkandPrepValue(newVal, errorH, errorT);
    if (!ok){
        if (errorH == "Format error")
                QMessageBox::critical(this, errorH, errorT);
        item->setText(oldVal);
        return;
    }
    item->setText(newVal);
    if (newVal != oldVal && row < currTable->countRows()){
        if (currTable->getColumn(col)->isPK()) {
             QList<QString> curRow = currTable->getRow(row);
             curRow[col] = newVal;
             if (!currTable->checkPK(curRow)){
                 QMessageBox::critical(this, "Private Key Error", "Private Key must be unique.");
                 item->setText(oldVal);
                return;
            }
        }
        currTable->setCell(row, col, newVal);
   }

}

void DatabaseWindow::onAddTableButtonClicked() {
    bool ok;
    QString tableName;
    while(true)
    {
        tableName = QInputDialog::getText(this, "Create New Table", "Table Name:", QLineEdit::Normal, "", &ok);
        if (!ok) return;

        if (tableName.isEmpty())
            QMessageBox::critical(this, "Error", "Table name cannot be empty.");
        else if (DB->getTable(tableName) != nullptr)
             QMessageBox::critical(this, "Error", "The table name must be unique.");
        else break;
    }

    NewTableInputDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {
        ColumnSet * columnSet = new ColumnSet(dialog.getColumnData());
        Table *table = new Table(DB, tableName, columnSet);
        DB->addTable(table);
        listWidget->addItem(tableName);
    }
}

QString DatabaseWindow::getCell(int row, int column){
    return currTable->getCell(row, column);
}

void DatabaseWindow::setCell(int row, int column, const QString &value){
    currTable->setCell(row, column, value);
}


void DatabaseWindow::onaddRowButtonClicked(){
    if (currTable == nullptr) return;

    int row = tableWidget->rowCount()-1;
    QString errorH, errorT;
    QList<QString> currRow;

    for (int i = 0; i < currTable->countColumns(); ++i)
    {
        QTableWidgetItem *item = tableWidget->item(row, i);
        QString str = item->text();
        if (!(currTable->getColumn(i)->checkandPrepValue(str, errorH, errorT))){
            QMessageBox::critical(this, errorH, errorT);
            return;
        }
        item->setText(str);
        currRow.append(str);
    }
    if (!(currTable->checkPK(currRow))){
        QMessageBox::critical(this, "Private Key Error", "Private Key must be unique.");
        return;
    }
    currTable->addRow(currRow);
    QPushButton *del = new QPushButton("X", tableWidget);
    connect(del, &QPushButton::clicked, this, &DatabaseWindow::onDeleteRowButtonClicked);

    tableWidget->setCellWidget(row, currTable->countColumns(), del);
    addEmptyRow();
}

void DatabaseWindow::onHeaderDoubleClicked(int column){
    currTable->sort(column);
    for (int i = 0; i < currTable->countRows(); ++i){
        for (int j = 0; j < currTable->countColumns(); ++j) {
            QTableWidgetItem *item = tableWidget->item(i, j);
            item->setText(currTable->getCell(i, j));
        }
    }
}

void DatabaseWindow::ondeleteTableButtonClicked(){
    if (currTable == nullptr) return;
    clearTable();
    DB->deleteTable(currTable);
    currTable = nullptr;
    QListWidgetItem *it = listWidget->takeItem(listWidget->currentRow());
    delete it;
}

void DatabaseWindow::onDeleteRowButtonClicked(){
    qDebug() << "Button clicked";
    QPushButton *senderButton = qobject_cast<QPushButton*>(sender());
    if (senderButton) {
        int row = tableWidget->indexAt(senderButton->pos()).row();
        qDebug() << row;
        tableWidget->removeRow(row);
        currTable->deleteRow(row);
     }

}

void DatabaseWindow::saveDatabase(const QString& fpth){
    QString filepath = fpth;
    if (filepath.isEmpty())
        filepath = QFileDialog::getSaveFileName(this, "Save File", DB->getName(), "Text Files (*.db);");

    if (!filepath.isEmpty()) {
        QFile file(filepath);

        if (file.open(QIODevice::WriteOnly)) {
            DB->save(file);
            file.close();
            return;
        }
        else {
            QMessageBox::critical(this, "Error", "Error opening the file:" + file.errorString());
        }
    }
    else {
        QMessageBox::critical(this, "Error", "Failed to save the database");
    }

}

void DatabaseWindow::closeDatabase(){
    this->close();

}
void DatabaseWindow::deleteDatabase(){
   DB->deleteFile();
   this->close();
}

void DatabaseWindow::closeEvent(QCloseEvent *event) {
    if (!DB->isSaved()){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Save Changes?", "Do you want to save changes?",
                                  QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (reply == QMessageBox::Cancel){
            event->ignore();
            return;
        }
        if (reply == QMessageBox::Save) saveDatabase();
    }

    emit closed();
}

DatabaseWindow::~DatabaseWindow() {
    delete DB;
}
