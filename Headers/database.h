#ifndef DATABASE_H
#define DATABASE_H

#include<QString>
#include<QFile>
#include<table.h>

class DataBase
{
private:
    QString name;
    QList<Table*> tables;
    bool saved;
    QString filename;

public:
    DataBase(const QString & Name);
    DataBase(QFile &file);
    QString getFilePath();
    QString getName();
    void setName(const QString& new_name);
    void addTable(Table *table);
    int countTables();
    Table* getTable(int index);
    Table* getTable(const QString &table_name);
    void deleteTable(int index);
    void deleteTable(Table *table);
    bool isSaved();
    void wasChanged();
    void save(QFile &file);
    bool deleteFile();
    ~DataBase();

};

#endif // DATABASE_H
