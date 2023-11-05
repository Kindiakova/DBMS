#include "mainwindow.h"

#include <QApplication>
#include <QListWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QInputDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();



        return a.exec();
}
/*
    QListWidget listWidget;
    listWidget.setFixedSize(200, 400);

      // Create some sample tables
    QStringList tableNames = {"Table 1", "Table 2", "Table 3"};
    listWidget.addItems(tableNames);

    // Create a button to add a new table
    QPushButton addButton("+");

    // Connect a slot to handle the button click
    QObject::connect(&addButton, &QPushButton::clicked, [&]() {
        bool ok;
        QString tableName = QInputDialog::getText(nullptr, "Create New Table", "Table Name:", QLineEdit::Normal, "", &ok);
        if (ok && !tableName.isEmpty()) {
            listWidget.addItem(tableName);
        }
    });

    // Create a vertical layout to hold the list widget and the button
    QVBoxLayout layout;
    layout.addWidget(&listWidget);
    layout.addWidget(&addButton);

    // Create a main widget to hold the layout
    QWidget mainWidget;
    mainWidget.setLayout(&layout);
    mainWidget.show();

    // Connect a slot to handle double clicks on list items
    QObject::connect(&listWidget, &QListWidget::itemDoubleClicked, [&](QListWidgetItem* item) {
        QString tableName = item->text();
         // Open the table widget (replace this with your actual code to open the table)
         qDebug() << "Opening table:" << tableName;
    });

    */
