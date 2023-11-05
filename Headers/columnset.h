#ifndef COLUMNSET_H
#define COLUMNSET_H

#include "column.h"
#include <QList>
#include <QPair>

class ColumnSet
{
    QList<Column*> columns;

public:
    static const QList<QString> ColumnTypes;


    struct ColumnData
    {
        QString Name;
        QString Type;
        bool PK;
        bool notNull;
    };


    ColumnSet(const QList<ColumnData> &columnData);

    bool isRowCorrect(QList<QString> &row, int &errorColumn);
    QList<QString> readRow(QDataStream &stream);
    void write();
    int size();
    QList<QString> getColumnNames();
    QList<int> getPKindex();
    Column* getColumn(int index);
    void write(QDataStream &stream);
    ~ColumnSet();
};

#endif // COLUMNSET_H
