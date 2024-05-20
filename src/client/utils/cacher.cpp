//
// Created by Shon on 07.05.2024.
//

#include "cacher.h"


void Cacher::loadConfig(const QString &exePath) {
    db.connect(exePath);
}

cfg::auth Cacher::isUserValid(const QString &login, const QString &password) {
    QString dbPass;
    if (!db.getAuth(login, dbPass, userId)) return cfg::UNKNOWN;
    if (dbPass.isEmpty()) return cfg::NOT_FOUND;
    if (dbPass == password) {
        return cfg::OK;
    }
    return cfg::BAD_PASS;
}

bool Cacher::getSubFolders(int currentId, QVector<QPair<int, QString>> &subFolders) {
    return db.getSubFolders(userId, currentId, false, subFolders);
}

bool Cacher::getUserOwners(int currentId, QVector<QPair<int, QString>> &users) {
    bool res = db.getRootFolderUsers(currentId, users);
    const size_t size = users.size();
    for (int i = 0; i < size; ++i) {
        if (users[i].first == userId) {
            users.remove(i);
            break;
        }
    }
    return res;
}

bool Cacher::getOnlineUsers(QVector<QPair<int, QString>> &users) {
    bool res = db.getOnlineUsers(users);
    const size_t size = users.size();
    for (int i = 0; i < size; ++i) {
        if (users[i].first == userId) {
            users.remove(i);
            break;
        }
    }
    return res;
}

bool Cacher::addUsersToFolder(const QVector<int> &invitedUsersIds, const int folderId) {
    for (const auto invitedUserId: invitedUsersIds) {
        if (!db.addFolderChain(userId, invitedUserId, folderId)) return false;
    }
    return true;
}

bool Cacher::registerUser(const QString &login, const QString &password) {
    bool res = db.addAuth(login, password, userId);
    return res;
}

QString Cacher::getUserName() {
    QString name;
    if (db.getUserName(userId, name)) return name;
    return "Undefined";
}

bool Cacher::deleteFolder(int folderId) {
    QVector<QPair<int, QString>> folders;
    db.getSubFolders(-1, folderId, true, folders);
    return db.multiRemoving(-1, "FolderUser", folders)
           && db.multiRemoving(-1, "Message", folders)
           && db.multiRemoving(-1, "Folder", folders);
}

bool Cacher::createFolder(int parentId, const QString &folderName) {
    return db.addFolder(userId, parentId, folderName);
}

bool Cacher::deleteUser(int userId, int folderId) {
    QVector<QPair<int, QString>> folders;
    db.getSubFolders(userId, folderId, true, folders);
    return db.multiRemoving(userId, "FolderUser", folders)
           && db.multiRemoving(userId, "Message", folders);
}
