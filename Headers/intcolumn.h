#ifndef INTCOLUMN_H
#define INTCOLUMN_H

#include "column.h"

class IntColumn : public Column
{
    int value;
public:
    IntColumn(const QString &Name, bool pk, bool notNull);
     bool checkandPrepValue(QString &str, QString &errorH, QString &errorT) override;
     bool compare(const QString &one, const QString& two) override;
     QString getType() override;
};

#endif // INTCOLUMN_H
