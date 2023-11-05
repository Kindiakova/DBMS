#include "stringcolumn.h"
#include "databasewindow.h"
#include <QLineEdit>
#include <QMessageBox>
StringColumn::StringColumn(const QString &Name, bool pk, bool notNull) :
    Column(Name, pk, notNull){
}
bool StringColumn::checkandPrepValue(QString &str, QString &errorH, QString &errorT) {
    if (str == "" && notNull) {
        errorH = "Empty data error";
        errorT = "Column " + name + " can not be empty.";
        return false;
    }

    return true;
}

bool StringColumn::compare(const QString &one, const QString& two){
    return one < two;
}

QString StringColumn::getType(){
    return "String";
}
