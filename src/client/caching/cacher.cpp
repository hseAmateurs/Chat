//
// Created by Shon on 07.05.2024.
//

#include "cacher.h"


void Cacher::loadConfig(const QString &exePath) {
    db.connect(exePath);
//    /db.addAuth({"1005", "aqwer", "pass_1"});
}

cfg::auth Cacher::isUserValid(const QString &login, const QString &password) {
    QString dbPass;
    if (!db.getAuth(login, dbPass)) return cfg::UNKNOWN;
    if (dbPass.isEmpty()) return cfg::NOT_FOUND;
    return (dbPass == password) ? cfg::OK : cfg::BAD_PASS;
}

void Cacher::updateData(const int userId) {
    const QVector<QString> tables{"Person", "FolderUser", "Message"};
    QVector<QString> updateTimes;
    for (const auto &table: tables)
        updateTimes.append(db.getLastUpdateTime(userId, table));

    qDebug() << updateTimes;
}
