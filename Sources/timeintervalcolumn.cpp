#include "timeintervalcolumn.h"
#include <QTimeEdit>
#include <QHBoxLayout>
TimeIntervalColumn::TimeIntervalColumn(const QString &Name, bool pk, bool notNull) :
    Column(Name, pk, notNull){
}

bool TimeIntervalColumn::checkandPrepValue(QString &str, QString &errorH, QString &errorT) {
    if (str == "" && notNull) {
            errorH = "Empty data error";
            errorT = "Column " + name + " can not be empty.";
            return false;
    }
    else if (str == "") return true;
    QStringList timeParts = str.split(" - ");
    if (timeParts.size() != 2){
        errorH = "Format error";
        errorT = "Data in column"+ name + " must correspond to the Time Interval format (hh:mm:ss - hh:mm::ss).";
        return false;
    }

    QTime s = QTime::fromString(timeParts[0], "hh:mm:ss");
    QTime e = QTime::fromString(timeParts[1], "hh:mm:ss");
    if (!s.isValid() || !e.isValid()) {
        errorH = "Format error";
        errorT = "Data in column " + name + " must correspond to the TIME format (hh::mm::ss).";
        return false;
    }
    return true;
    return true;
}

bool TimeIntervalColumn::compare(const QString &one, const QString& two){
    if (one == "") return false;
    if (two == "") return true;
    QStringList timeParts_one = one.split(" - ");
    QStringList timeParts_two = two.split(" - ");
    QTime one_s = QTime::fromString(timeParts_one[0], "hh:mm:ss");
    QTime one_e = QTime::fromString(timeParts_one[1], "hh:mm:ss");

    QTime two_s = QTime::fromString(timeParts_two[0], "hh:mm:ss");
    QTime two_e = QTime::fromString(timeParts_two[0], "hh:mm:ss");

    if (one_s < two_s || (one_s == two_s && one_e < two_e)) return true;
    else return false;
}

QString TimeIntervalColumn::getType(){
    return "TimeInterval";
};
