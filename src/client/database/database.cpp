//
// Created by Shon on 06.05.2024.
//

#include "database.h"

#include "scripts/tables.h"

void Database::connect() {
    qDebug() << "Database:" << "Connecting to db:" << dbPath;
    if (!QFile(dbPath).exists()) {
        qDebug() << "Database:" << "File doesn't exist";
        restore();
    }
    else open();
}

bool Database::restore() {
    qDebug() << "Database:" << "Restoring file";
    if (open()) return createTables();

    qCritical() << "Database:" << "Can't restore file" << db.lastError().text();
    return false;
}

bool Database::open() {
    qDebug() << "Database:" << "Opening";
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);
    return db.open();
}

bool Database::createTables() {
    qDebug() << "Database:" << "Creating tables";

    QSqlQuery query;
    for (const auto& table : TABLES_INIT) {
        if(!query.exec(table)) {
            qDebug() << "Database:" << "Can't create tables" << db.lastError().text();
            return false;
        }
    }
    return true;
}
