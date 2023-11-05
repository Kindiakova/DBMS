#ifndef STRINGCOLUMN_H
#define STRINGCOLUMN_H

#include "column.h"

class StringColumn : public Column
{
public:
    StringColumn(const QString &Name, bool pk, bool notNull);
     bool checkandPrepValue(QString &str, QString &errorH, QString &errorT) override;
     bool compare(const QString &one, const QString& two) override;
     QString getType() override;
};

#endif // STRINGCOLUMN_H
