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

    bool getAuth(const QString &login, QString &password);

    bool addAuth(const QVector<QString> &data);

    QString getLastMsgTime(int userId);

    // Перезаписывает таблицу
    // TODO
    bool rewriteTable(int userId, const QString &tableName) { return false; };

    bool addMsg(int userId, int folderId, const QString &text);

    // Возвращает все сообщения из текущей папки (включая подпапки)
    // TODO (структуру для сообщений)
    bool getMsgs(int folderId, QVector<QVector<QString>> &msgs);

    // Возвращает подпапки, вложенные в данную папку
    bool getSubFolders(int userId, int currentDirId, bool tree, QVector<QPair<int, QString>> &subFolders);

    bool updateData(int id, const QString &key, const QString &value, const QString &tableName);

    bool addFolder(int userId, int parentId, const QString &name);

    bool deleteFolder(int folderId);

    // Добавляет все связи (включая связи с подпапками)
    bool addFolderChain(int userId, int folderId);

    // Удаляет все связи (включая связи с подпапками)/сообщения/папки, если userId == -1, то userId не учитывается
    bool multiRemoving(int userId, const QString &tableName, const QVector<QPair<int, QString>> &folders);


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
