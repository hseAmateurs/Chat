//
// Created by Shon on 07.05.2024.
//

#ifndef CHAT_CACHER_H
#define CHAT_CACHER_H

#include <QString>

#include "database.h"

class Cacher {
public:
    Cacher(Cacher const &) = delete;

    Cacher &operator=(Cacher const &) = delete;

    static Cacher &instance() {
        static Cacher cacher;
        return cacher;
    }

    void loadConfig(const QString &exePath);

    cfg::auth isUserValid(const QString &login, const QString &password);

    // data = (id, login, pass)
    bool auth(const QVector<QString> &data) { return db.addAuth(data); }

    void actualizeData();

    bool getSubFolders(int currentId, QVector<QPair<int, QString>> &subFolders);

    bool getOnlineUsers(QVector<QPair<int, QString>> &users);

    bool addUsersToFolder(const QVector<int> &invitedUsersIds, int folderId);

    bool registerUser(const QString& login, const QString& password);

    QString getUserName();

    bool deleteFolder(int folderId);

    bool createFolder(int parentId, const QString &folderName);

private:
    int userId;
    Database db;

private:
    Cacher() { };

    ~Cacher() { };
};


#endif //CHAT_CACHER_H
