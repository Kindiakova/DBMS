#ifndef TABLE_H
#define TABLE_H

#include<QString>
#include<QVector>
#include"columnset.h"

class DataBase;

class Table
{
private:
    DataBase *database;
    QString name;
    ColumnSet *columns;
    QList<QList<QString> > rows;

public:
    Table(DataBase *DB, QDataStream &stream);
    Table(DataBase *DB, const QString &tableName, ColumnSet* columnSet);

    QString getCell(int i, int j);
    void editrow(const QList<QString> &row, int index);
    bool addRow(const QList<QString> &row);
    void setCell(int row, int column, const QString& value);

    void sort(int index);
    void deleteRow(int index);

    QString getName();
    void setName(const QString& new_name);
    int countColumns();
    int countRows();
    bool checkPK(const  QList<QString>  &row);
    void write(QDataStream &stream);
    QList<QString> getColumnNames();
    QList<QString> getRow(int index);
    Column* getColumn(int index);

    ~Table();

};

#endif // TABLE_H
