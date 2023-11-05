#include "charcolumn.h"
#include "table.h"
#include <QLineEdit>
#include <QTableWidget>


CharColumn::CharColumn(const QString &Name, bool pk, bool notNull) :
    Column(Name, pk, notNull){
}

bool CharColumn::checkandPrepValue(QString &str, QString &errorH, QString &errorT) {
    if (str == "" && notNull) {
        errorH = "Empty data error";
        errorT = "Column " + name + " can not be empty.";
        return false;
    }
    str = str.mid(0, 1);
    return true;
}

bool CharColumn::compare(const QString &one, const QString& two){
    return one < two;
}

QString CharColumn::getType(){
    return "Char";
}
