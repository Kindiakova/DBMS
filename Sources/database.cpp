#include "database.h"
#include<QByteArray>
DataBase::DataBase(const QString & Name){
    name = Name;
    saved = false;
}

DataBase::DataBase(QFile &file){
    int nTable;
    filename = file.fileName();
    QDataStream stream(&file);
    stream.setVersion(QDataStream::Qt_5_15);
    stream >> name >> nTable;

    for (int i = 0; i < nTable; ++i){
       Table* table = new Table(this, stream);
       tables.append(table);
    }

    saved = true;
}

QString DataBase::getFilePath(){
    return filename;
}

QString DataBase::getName(){
    return name;
}

void DataBase::setName(const QString  &new_name){
    name = new_name;
    saved = false;
}

void DataBase::addTable(Table *table){
    tables.append(table);
    saved = false;
}

int DataBase::countTables(){
    return tables.size();
}

Table* DataBase::getTable(int index){
    return tables[index];
}

Table* DataBase::getTable(const QString &table_name){
    for (Table *table : tables) {
        if (table->getName() == table_name) return table;
    }
    return nullptr;
}


void DataBase::deleteTable(Table* table){

    tables.removeOne(table);
    delete table;
    saved = false;
}

bool DataBase::isSaved(){
    return saved;
}

void DataBase::wasChanged(){
    saved = false;
}

void DataBase::save(QFile &file)
{

    if (filename != file.fileName()){
           saved = false;
           filename = file.fileName();
    }

    if (saved) return;
    QDataStream stream(&file);
    int nTables = tables.size();
    stream << name << nTables;

    for (int i = 0; i < tables.size(); ++i)
        tables[i]->write(stream);

    saved = true;
}

bool DataBase::deleteFile(){
    saved = true;
    if (filename == "") return true;
    return (QFile::remove(filename));
}

DataBase::~DataBase(){
    for (int i = 0; i < tables.size(); ++i)
       delete tables[i];
}

