#ifndef REALCOLUMN_H
#define REALCOLUMN_H

#include "column.h"

class RealColumn : public Column
{
public:
    RealColumn(const QString &Name, bool pk, bool notNull);
     bool checkandPrepValue(QString &str, QString &errorH, QString &errorT) override;
     bool compare(const QString &one, const QString& two) override;
     QString getType() override;
};

#endif // REALCOLUMN_H
