#include "realcolumn.h"
#include "databasewindow.h"

#include<QLineEdit>
#include<QMessageBox>

RealColumn::RealColumn(const QString &Name, bool pk, bool notNull) :
    Column(Name, pk, notNull){
}

bool RealColumn::checkandPrepValue(QString &str, QString &errorH, QString &errorT) {
    bool ok;
    if (str == "" && notNull) {
        errorH = "Empty data error";
        errorT = "Column " + name + " can not be empty.";
        return false;
    }
    else if (str == "") return true;
    double value = str.toDouble(&ok);
    if (!ok) {
        errorH = "Format error";
        errorT = "Value in column " + name + " is not a real number.";
        return false;
    }
    str = QString::number(value);
    return true;
}

QString RealColumn::getType(){
     return "Real";
}

bool RealColumn::compare(const QString &one, const QString& two){
    return (one.toDouble()) < (two.toDouble());
}
