//
// Created by Shon on 06.05.2024.
//

#ifndef CHAT_DATABASE_H
#define CHAT_DATABASE_H

#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

#include <QFile>
#include <QDir>
#include <QString>
#include <QDebug>

#include "../settings/config.h"

class Database {
public:
    explicit Database(const QString &dirPath) : dbPath(dirPath + QDir::separator() + cfg::database::FILENAME) { };

    void connect();

    ~Database() { db.close(); }

private:
    QSqlDatabase db;
    const QString dbPath;

private:
    bool restore();

    bool open();

    bool createTables();
};


#endif //CHAT_DATABASE_H
