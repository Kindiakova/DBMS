#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Create "Open Database" button
    QPushButton *openButton = new QPushButton("Open Database", this);

    // Create "Create Database" button
    QPushButton *createButton = new QPushButton("Create Database", this);

    openButton->setFixedSize(200, 200);
    createButton->setFixedSize(200, 200);

    // Connect button signals to slots
    connect(openButton, &QPushButton::clicked, this, &MainWindow::onOpenButtonClicked);
    connect(createButton, &QPushButton::clicked, this, &MainWindow::onCreateButtonClicked);


    // Create a horizontal layout
    QHBoxLayout *layout = new QHBoxLayout;

    // Add buttons to the layout
    layout->addWidget(openButton);
    layout->addWidget(createButton);

     // Set layout for central widget
     QWidget *centralWidget = new QWidget(this);
     centralWidget->setLayout(layout);
     setCentralWidget(centralWidget);

}

void  MainWindow::onOpenButtonClicked(){
    this->hide();
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Database File"), "", tr("Database Files (*.db)"));

    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly)) {

            DataBase *DB = new DataBase(file);            
            dbWindow = new DatabaseWindow(this, DB);
            connect(dbWindow, SIGNAL(closed()), this, SLOT(dbclosed()));
            dbWindow->show();

            file.close();
        }

        else {
            QMessageBox::critical(this, "Error", "Error opening the file:" + file.errorString());
            this->show();
        }
    }
    else this->show();
}

void MainWindow::dbclosed() {
        delete dbWindow;
        dbWindow = nullptr;
        this->show();
}

void MainWindow::onCreateButtonClicked(){
    this->hide();
    bool ok;
    QString Name = "";
    while(Name.isEmpty()){
        Name = QInputDialog::getText(this, "Create New Database", "Database Name:", QLineEdit::Normal, "", &ok);
        if (!ok){
            this->show();
            return;
        }
        if (Name.isEmpty())
             QMessageBox::critical(this, "Error", "Database name cannot be empty.");

    }
    DataBase *DB = new DataBase(Name);
    dbWindow = new DatabaseWindow(this, DB);
    connect(dbWindow, SIGNAL(closed()), this, SLOT(dbclosed()));
    dbWindow->show();
}


MainWindow::~MainWindow()
{
    delete ui;
}

