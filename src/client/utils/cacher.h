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

    bool sendMsg(int folderId, const QString &text) { return db.addMsg(userId, folderId, text); };

    bool getLastMsgs(int folderId, QVector<QPair<int, QString>> &msgs, QString &lastMsgTime) {
        return db.getMsgs(folderId, msgs, lastMsgTime);
    };

    int getUserId() { return userId; }

private:
    int userId;
    Database db;

private:
    Cacher() { };

    ~Cacher() { };
};


#endif //CHAT_CACHER_H
