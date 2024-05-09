//
// Created by Shon on 06.05.2024.
//

#include "database.h"

#include "scripts/tables.h"

void Database::connect(const QString &dirPath) {
    dbPath = dirPath + QDir::separator() + cfg::database::FILENAME;

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
    query = QSqlQuery(db);
    return db.open();
}

bool Database::createTables() {
    qDebug() << "Database:" << "Creating tables";

    for (const auto &table: TABLES_INIT) {
        if (!query.exec(table)) {
            qDebug() << "Database:" << "Can't create tables" << db.lastError().text();
            return false;
        }
    }
    return true;
}

bool Database::getAuth(const QString &login, QString &password) {
    qDebug() << "Database:" << "Getting auth data";

    query.prepare("SELECT password FROM User WHERE login=:login");
    query.bindValue(":login", login);

    if (!query.exec()) {
        qDebug() << "Database:" << "Can't get auth data" << db.lastError();
        return false;
    }

    if (query.next())
        password = query.value("password").toString();
    return true;
}

// data = (id, login, pass)
bool Database::addAuth(const QVector<QString> &data) {
    qDebug() << "Database:" << "Adding auth data";

    query.prepare("INSERT INTO User (id, login, password) VALUES (?, ?, ?)");
    for (int i = 0; i < 3; ++i)
        query.addBindValue(data.at(i));

    if (!query.exec()) {
        qDebug() << "Database:" << "Can't insert auth data" << db.lastError().text();
        return false;
    }

    query.prepare("INSERT INTO Person (userId, name) VALUES (?, ?)");
    for (int i = 0; i < 2; ++i) {
        query.addBindValue(data.at(i));
    }

    if (!query.exec()) {
        qDebug() << "Database:" << "Can't insert person data" << db.lastError().text();
        return false;
    }

    return true;
}
