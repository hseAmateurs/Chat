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

#include "config.h"

class Database {
public:
    explicit Database() { };

    void connect(const QString &dirPath);

    ~Database() { db.close(); }

    bool getAuth(const QString &login, QString &password, int &userId);

    // Регистрирует нового пользователя в БД
    bool addAuth(const QString &login, const QString &pass, int &userId);

    bool getUserName(int userId, QString &username);

    bool getOnlineUsers(QVector<QPair<int, QString>> &users);

    bool addMsg(int userId, int folderId, const QString &text);

    bool getMsgs(int folderId, QVector<QPair<int, QString>> &msgs, QString &lastMsgTime);

    // Возвращает подпапки, вложенные в данную папку
    bool getSubFolders(int userId, int currentDirId, bool tree, QVector<QPair<int, QString>> &subFolders);

    bool updateData(int id, const QString &key, const QVariant &value, const QString &tableName);

    // Создаёт новую папку
    bool addFolder(int userId, int parentId, const QString &name);

    // Добавляет все связи (включая связи с подпапками)
    bool addFolderChain(int parentUserId, int newUserId, int folderId);

    // Удаляет все связи (включая связи с подпапками)/сообщения/папки, если userId == -1, то userId не учитывается
    bool multiRemoving(int userId, const QString &tableName, const QVector<QPair<int, QString>> &folders);

    // Возвращает пользователей, для которых папка явялется корневой
    bool getRootFolderUsers(int currentDirId, QVector<QPair<int, QString>> &users);

    bool isChainExist(int userId, int folderId);

    int getNextFolderId();


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
