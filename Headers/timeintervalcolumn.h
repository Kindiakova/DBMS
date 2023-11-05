#ifndef TIMEINTERVALCOLUMN_H
#define TIMEINTERVALCOLUMN_H

#include "column.h"

class TimeIntervalColumn : public Column
{
public:
    TimeIntervalColumn(const QString &Name, bool pk, bool notNull);
     bool checkandPrepValue(QString &str, QString &errorH, QString &errorT) override;
     bool compare(const QString &one, const QString& two) override;
     QString getType() override;
};

#endif // TIMEINTERVALCOLUMN_H
