#ifndef DATABASEWINDOW_H
#define DATABASEWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QListWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <database.h>

class DatabaseWindow : public QMainWindow {
    Q_OBJECT
    DataBase *DB;
    QListWidget *listWidget;
    QTableWidget *tableWidget;
    Table* currTable = nullptr;

public:
    DatabaseWindow(QWidget *parent, DataBase *database);
    QString getCell(int row, int column);
    void setCell(int row, int column, const QString &value);
    void addEmptyRow();
    void clearTable();
    void saveDatabase(const QString& fpth = "");
    void closeDatabase();
    void deleteDatabase();
     ~DatabaseWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void onListWidgetItemDoubleClicked(QListWidgetItem *item);
    void onAddTableButtonClicked();
    void onaddRowButtonClicked();
    void onHeaderDoubleClicked(int column);
    void ondeleteTableButtonClicked();
    void onItemChanged(QTableWidgetItem *item);
    void onDeleteRowButtonClicked();

signals:
        void closed();



};

#endif // DATABASEWINDOW_H
