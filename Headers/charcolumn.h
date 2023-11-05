#ifndef CHARCOLUMN_H
#define CHARCOLUMN_H

#include "column.h"

class CharColumn : public Column
{
public:
    CharColumn(const QString &Name, bool pk, bool notNull);
    bool checkandPrepValue(QString &str, QString &errorH, QString &errorT) override;
    bool compare(const QString &one, const QString& two) override;
    QString getType() override;
};

#endif // CHARCOLUMN_H
