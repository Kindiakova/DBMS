#ifndef TIMECOLUMN_H
#define TIMECOLUMN_H

#include "column.h"

class TimeColumn : public Column
{
public:
    TimeColumn(const QString &Name, bool pk, bool notNull);
    bool checkandPrepValue(QString &str, QString &errorH, QString &errorT) override;
    bool compare(const QString &one, const QString& two) override;
    QString getType() override;
};

#endif // TIMECOLUMN_H
