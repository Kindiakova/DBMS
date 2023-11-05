#include "timecolumn.h"
#include <QTimeEdit>
TimeColumn::TimeColumn(const QString &Name, bool pk, bool notNull) :
    Column(Name, pk, notNull){
}

bool TimeColumn::checkandPrepValue(QString &str, QString &errorH, QString &errorT) {
    if (str == "" && notNull) {
            errorH = "Empty data error";
            errorT = "Column " + name + " can not be empty.";
            return false;
    }
    else if (str == "") return true;
    QTime x = QTime::fromString(str, "hh:mm:ss");
    if (!x.isValid()) {
        errorH = "Format error";
        errorT = "Data in column "+ name + " must correspond to the Time format (hh:mm:ss).";
        return false;
    }
    return true;
}

bool TimeColumn::compare(const QString &one, const QString& two){
    if (one == "") return false;
    if (two == "") return true;
    QTime x = QTime::fromString(one, "hh:mm:ss");
    QTime y = QTime::fromString(two, "hh:mm:ss");
    return x < y;
}

QString TimeColumn::getType(){
    return "Time";
};
