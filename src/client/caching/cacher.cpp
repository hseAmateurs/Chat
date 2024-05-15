//
// Created by Shon on 07.05.2024.
//

#include "cacher.h"


void Cacher::loadConfig(const QString &exePath) {
    db.connect(exePath);
// ---
    QString dbPass;
    db.getAuth("aqwer", dbPass, userId);
//    db.addAuth({"1005", "aqwer", "pass_1"});
// ---
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

void Cacher::actualizeData() {
    QString lastMsgTime = db.getLastMsgTime(userId);

    // Отправка серверу запроса на получение всей актуальной информации

    qDebug() << lastMsgTime;
}

bool Cacher::getSubFolders(int currentId, QVector<QPair<int, QString>> &subFolders) {
    return db.getSubFolders(userId, currentId, false, subFolders);
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
    int userServerId = 190;
    bool res = db.addAuth({QString::number(userServerId), login, password});
    if (res) userId = userServerId;
    return res;
}

QString Cacher::getUserName() {
    QString name;
    if (db.getUserName(userId, name)) return name;
    return "Undefined";
}

bool Cacher::deleteFolder(int folderId) {
    return db.deleteFolder(folderId);
}

bool Cacher::createFolder(int parentId, const QString &folderName) {
    return db.addFolder(userId, parentId, folderName);
}
