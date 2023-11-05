#ifndef COLUMN_H
#define COLUMN_H

#include<QString>
#include<QWidget>
#include<QDataStream>
class Table;


class Column
{
protected:
    QString name;
    bool PK;
    bool notNull;

public:
    Column(const QString &Name, bool pk, bool notNull);
    QString getName();
    bool isNotNull();
    bool isPK();
    virtual bool checkandPrepValue(QString &str, QString &errorH, QString &errorT) = 0;
    virtual bool compare(const QString &one, const QString& two) = 0;
    virtual QString getType() = 0;
    virtual ~Column() = default;
};

#endif // COLUMN_H
