#include "columnset.h"
#include "intcolumn.h"
#include "realcolumn.h"
#include "stringcolumn.h"
#include "charcolumn.h"
#include "timecolumn.h"
#include "timeintervalcolumn.h"


const QList<QString> ColumnSet::ColumnTypes = {
        "Integer",
        "Real",
        "Char",
        "String",
        "Time",
        "TimeInterval"
};

ColumnSet::ColumnSet(const QList<ColumnData> &columnsData)
{
    for (auto cD : columnsData){

        Column *column = nullptr;
        if (cD.Type =="Integer")
             column = new IntColumn(cD.Name, cD.PK, cD.notNull);
        if (cD.Type =="Real")
            column = new RealColumn(cD.Name, cD.PK, cD.notNull);
        if (cD.Type =="Char")
            column = new CharColumn(cD.Name, cD.PK, cD.notNull);
        if (cD.Type =="String")
            column = new StringColumn(cD.Name, cD.PK, cD.notNull);
        if (cD.Type =="Time")
             column = new TimeColumn(cD.Name, cD.PK, cD.notNull);
        if (cD.Type =="TimeInterval")
            column = new TimeIntervalColumn(cD.Name, cD.PK, cD.notNull);

         columns.append(column);
    }
}

int ColumnSet::size(){
    return columns.size();
}

QList<QString> ColumnSet::getColumnNames(){
   QList<QString> names;
   for (Column* column: columns)
       names.append(column->getName());
   return names;
}

Column* ColumnSet::getColumn(int index){
    return columns[index];
}

bool ColumnSet::isRowCorrect(QList<QString> &row, int &errorColumn){
    errorColumn = -1;
    for (int i = 0; i < columns.size(); ++i)
    {
        QString x, y;
        bool ok = columns[i]->checkandPrepValue(row[i], x, y);
        if (!ok){
            errorColumn = i;
            return false;
        }
    }
    return true;
}
QList<int> ColumnSet::getPKindex(){
    QList<int> pk;
    for (int i = 0; i < columns.size(); ++i)
        if (columns[i]->isPK()) pk.append(i);
    return pk;
}

void ColumnSet::write(QDataStream &stream){

    for (Column* column : columns){
        stream << column->getName() << column->getType() << column->isPK() << column -> isNotNull();
    }
}

ColumnSet::~ColumnSet(){
    for (Column* column: columns){
        delete column;
    }
}
