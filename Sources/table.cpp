#include "table.h"
#include "database.h"

Table::Table(DataBase *DB, QDataStream &stream){
    //here we read it;
    database = DB;
    int columnN, rowN;
    stream >> name >> columnN >> rowN;
    QList<ColumnSet::ColumnData> columnData;

    for (int i = 0; i < columnN; ++i)
    {
        ColumnSet::ColumnData column;
        stream >> column.Name >> column.Type >> column.PK >> column.notNull;
        columnData.append(column);
    }
    columns = new ColumnSet(columnData);
    rows.resize(rowN);
    for (int i = 0; i < rowN; ++i){
       for (int j = 0; j < columnN; ++j){
            QString cell;
            stream >> cell;
            rows[i].append(cell);
       }
    }
}

Table::Table(DataBase *DB, const QString &tableName, ColumnSet* columnSet){
    //here we are create it
    database = DB;
    name = tableName;
    columns = columnSet;

}
int Table::countColumns(){
    return columns->size();
}

int Table::countRows(){
    return rows.size();
}

QList<QString> Table::getColumnNames(){
    return columns->getColumnNames();
}

QString Table::getCell(int i, int j){
    if (i < 0 || j < 0 || i >= rows.size() || j >= columns->size()) return "";
    return rows[i][j];
}

Column* Table::getColumn(int index){
    return columns->getColumn(index);
}


void Table::editrow(const QList<QString> &row, int index){
    rows[index] = row;
     database->wasChanged();
}

void Table::sort(int index){
    if (index >= countColumns()) return;
    Column *column = columns->getColumn(index);
    std::sort(rows.begin(), rows.end(), [=](const QList<QString>& row1, const QList<QString>& row2) {
            return column->compare(row1[index], row2[index]);
        });
     database->wasChanged();
}

void Table::deleteRow(int index){
    rows.removeAt(index);
     database->wasChanged();
}

QString Table::getName(){
    return name;
}

bool Table::addRow(const QList<QString> &row){
    if (!checkPK(row)) return false;
    rows.append(row);
    database->wasChanged();
    return true;
}

void Table::setCell(int row, int column, const QString& value){
    rows[row][column] = value;
    database->wasChanged();
}


void Table::setName(const QString& new_name){
    name = new_name;
    database->wasChanged();
}

QList<QString> Table::getRow(int index){
    return rows[index];
}

bool Table::checkPK(const QList<QString> & newRow){
    QList<int> pkList = columns->getPKindex();
    if (pkList.size() == 0) return true;
    for (auto row : rows){
        bool ok = true;
        for (int x : pkList)
            if (row[x] != newRow[x]) {ok = false; break;}
        if (ok) return false;
    }
    return true;
}

void Table::write(QDataStream &stream){
    int nCol = columns->size(), nRow = rows.size();
    stream << name << nCol << nRow;
    columns->write(stream);

    for (int i = 0; i < rows.size(); ++i)
        for (int j = 0; j < columns->size(); ++j)
            stream << rows[i][j];
}


Table::~Table(){
    delete columns;
}
