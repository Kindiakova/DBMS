#include "column.h"

Column::Column(const QString &Name, bool pk, bool NotNull)
{
    name = Name;
    PK = pk;
    notNull = NotNull;
}

QString Column::getName(){
    return name;
}

bool Column::isNotNull(){
    return notNull;
}

bool Column::isPK(){
    return PK;
}

