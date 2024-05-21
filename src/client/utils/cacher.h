//
// Created by Shon on 07.05.2024.
//

#ifndef CHAT_CACHER_H
#define CHAT_CACHER_H

#include <QString>

#include "database.h"

/*
 * Класс для управления данными приложения.
 * Связывает интерфейс с локальной БД
 */
class Cacher {
public:
    // Поскольку класс является standalone, то должен существовать только единственный экземпляр,
    // для этого удаляем конструкторы копирования и оператор присваивания, а также делаем
    // конструктор инициализации приватным
    Cacher(Cacher const &) = delete;

    Cacher &operator=(Cacher const &) = delete;

    static Cacher &instance() {
        static Cacher cacher;
        return cacher;
    }

    void loadConfig(const QString &exePath);

    bool setOnlineStatus(bool isOnline) { return db.updateData(userId, "isOnline", isOnline, "User"); };

    // Проверка корректности данных авторизации, при успехе записывает userId текущего пользователя
    cfg::auth isUserValid(const QString &login, const QString &password);

    bool getSubFolders(int currentId, QVector<QPair<int, QString>> &subFolders);

    // Получение участников текущей папки (возвращает только тех, для кого это корень)
    bool getUserOwners(int currentId, QVector<QPair<int, QString>> &users);

    bool getOnlineUsers(QVector<QPair<int, QString>> &users);

    bool addUsersToFolder(const QVector<int> &invitedUsersIds, int folderId);

    bool registerUser(const QString &login, const QString &password);

    QString getUserName();

    bool deleteFolder(int folderId);

    bool createFolder(int parentId, const QString &folderName);

    bool deleteUser(int userId, int folderId);

    bool sendMsg(bool isPersonal, int folderId, const QString &text) {
        if (!isPersonal) return db.addMsg(userId, folderId, text);
        else return db.addMsg(userId, ((folderId * 13) ^ (userId * 13)), text);
    };

    bool getLastMsgs(bool isPersonal, int folderId, QVector<QPair<int, QString>> &msgs, QString &lastMsgTime) {
        if (!isPersonal) return db.getMsgs(isPersonal, folderId, msgs, lastMsgTime);
        return db.getMsgs(isPersonal, ((folderId * 13) ^ (userId * 13)), msgs, lastMsgTime);
    };

    int getUserId() const { return userId; }

    bool isChainExist(int folderId) { return db.isChainExist(userId, folderId); }

private:
    int userId;
    Database db;

private:
    Cacher() { };

    ~Cacher() { };
};


#endif //CHAT_CACHER_H
