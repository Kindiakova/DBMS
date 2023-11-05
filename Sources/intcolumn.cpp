#include "intcolumn.h"
#include "databasewindow.h"
#include <QLineEdit>
#include <QMessageBox>
IntColumn::IntColumn(const QString &Name, bool pk, bool notNull) :
    Column(Name, pk, notNull){
}


bool IntColumn::checkandPrepValue(QString &str, QString &errorH, QString &errorT) {
    bool ok;
    if (str == "" && notNull) {
        errorH = "Empty data error";
        errorT = "Column " + name + " can not be empty.";
        return false;
    }
    else if (str == "") return true;
    int value = str.toInt(&ok);
    if (!ok) {
        errorH = "Format error";
        errorT = "Value in column " + name + " is not an integer number.";
        return false;
    }
    str = QString::number(value);
    return true;
}

bool IntColumn::compare(const QString &one, const QString& two){
    return (one.toInt()) < (two.toInt());
}
QString IntColumn::getType(){
     return "Integer";
}
