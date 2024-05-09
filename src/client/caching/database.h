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
    explicit Database() { };

    void connect(const QString &dirPath);

    ~Database() { db.close(); }

    bool getAuth(const QString &login, QString& password);

    bool addAuth(const QVector<QString> &data);

    QString getLastMsgTime(int userId);

    // Перезаписывает таблицу
    bool forceUpdateTable(int userId, const QString& tableName) { };

    bool getData(int userId, const QString& tableName) { };

    // Вставляет или обновляет данные
    bool updateData(int userId, const QString& tableName) { };

    // Добавляет все связи (включая подпапки)
    bool addFolderChain(int userId, int folderId);

    // Удаляет все связи (включая подпапки)
    bool removeFolderChain(int userId, int folderId);

    // Получает поддерево для папки rootId, если userId == -1, то таблица FolderUser не учитывается
    bool getSubFolderTree(int userId, int rootId, QVector<int> &folderTree);


private:
    QSqlDatabase db;
    QString dbPath;
    QSqlQuery query;

private:
    bool restore();

    bool open();

    bool createTables();
};


#endif //CHAT_DATABASE_H
