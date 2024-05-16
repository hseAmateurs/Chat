//
// Created by Shon on 06.05.2024.
//

#include <QQueue>

#include "database.h"

#include "scripts/tables.h"

void Database::connect(const QString &dirPath) {
    dbPath = dirPath + QDir::separator() + cfg::database::FILENAME;

    qDebug() << "Database:" << "Connecting to db:" << dbPath;
    if (!QFile(dbPath).exists()) {
        qDebug() << "Database:" << "File doesn't exist";
        restore();
    }
    else open();
}

bool Database::restore() {
    qDebug() << "Database:" << "Restoring file";
    if (open()) return createTables();

    qCritical() << "Database:" << "Can't restore file" << db.lastError().text();
    return false;
}

bool Database::open() {
    qDebug() << "Database:" << "Opening";
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);
    query = QSqlQuery(db);
    return db.open();
}

bool Database::createTables() {
    qDebug() << "Database:" << "Creating tables";

    for (const auto &table: TABLES_INIT) {
        if (!query.exec(table)) {
            qDebug() << "Database:" << "Can't create tables" << db.lastError().text();
            return false;
        }
    }
    return true;
}

bool Database::getAuth(const QString &login, QString &password, int &userId) {
    qDebug() << "Database:" << "Getting auth data";

    query.prepare("SELECT * FROM User WHERE login=:login");
    query.bindValue(":login", login);

    if (!query.exec()) {
        qDebug() << "Database:" << "Can't get auth data" << db.lastError();
        return false;
    }

    if (query.next()) {
        password = query.value("password").toString();
        userId = query.value("id").toInt();
    }
    return true;
}

// data = (id, login, pass)
bool Database::addAuth(const QVector<QString> &data) {
    qDebug() << "Database:" << "Adding auth data" << data;

    query.prepare("INSERT INTO User (id, login, password) VALUES (?, ?, ?)");
    for (int i = 0; i < 3; ++i)
        query.addBindValue(data[i]);

    if (!query.exec()) {
        qDebug() << "Database:" << "Can't insert auth data" << db.lastError().text();
        return false;
    }

    query.prepare("INSERT INTO Person (userId, name) VALUES (?, ?)");
    for (int i = 0; i < 2; ++i)
        query.addBindValue(data[i]);

    if (!query.exec()) {
        qDebug() << "Database:" << "Can't insert person data" << db.lastError().text();
        return false;
    }

    return true;
}

QString Database::getLastMsgTime(const int userId) {
    qDebug() << "Database:" << "Getting last sendTime from Message for" << userId;
    query.prepare("SELECT * FROM Message WHERE userId=:userId ORDER BY updateTime DESC LIMIT 1");
    query.bindValue(":userId", userId);

    if (!query.exec()) {
        qDebug() << "Database:" << "Can't get sendTime" << db.lastError().text();
        return "";
    }

    return query.next() ? query.value("sendTime").toString() : "";
}

bool Database::addFolder(const int userId, const int parentId, const QString &name) {
    qDebug() << "Database:" << "Adding folder for" << userId << "-" << name << "-" << parentId;

    query.prepare("INSERT INTO Folder (parentId, name) VALUES (:parentId, :name)");
    query.bindValue(":parentId", parentId);
    query.bindValue(":name", name);

    if (!query.exec()) {
        qDebug() << "Database:" << "Can't add folder" << db.lastError().text();
        return false;
    }

    if (!query.lastInsertId().isValid()) {
        qDebug() << "Database:" << "Can't get new folder id" << db.lastError().text();
        return false;
    }
    addFolderChain(userId, userId, query.lastInsertId().toInt());

    return true;
}

// При добавлении связи с папкой с подпапками тоже устанавливается связь
bool Database::addFolderChain(int parentUserId, int newUserId, int folderId) {
    qDebug() << "Database:" << "Adding folder chain between" << newUserId << "-" << folderId << "for" << parentUserId;

    QVector<QPair<int, QString>> folders;
    getSubFolders(parentUserId, folderId, true, folders);

    const QString queryStr = "INSERT INTO FolderUser (userId, folderId) "
                             "SELECT :userId, :folderId "
                             "WHERE NOT EXISTS (SELECT 1 FROM FolderUser WHERE userId=:userId AND folderId=:folderId)";

    for (const auto &folder: folders) {
        query.prepare(queryStr);
        query.bindValue(":userId", newUserId);
        query.bindValue(":folderId", folder.first);

        if (!query.exec()) {
            qDebug() << "Database:" << "Can't add folder chains" << db.lastError().text();
            return false;
        }
    }
    return true;
}

// Удаляет объекты из таблицы по ids
bool Database::multiRemoving(int userId, const QString &tableName, const QVector<QPair<int, QString>> &folders) {
    qDebug() << "Database:" << "Deleting folder chain between" << userId << "-"
             << "\nIds:" << folders;

    QString idName;
    if (tableName == "Folder") idName = "id";
    else idName = "folderId";

    QString queryStr = QString("DELETE FROM %1 WHERE %2 IN (").arg(tableName, idName);
    QStringList idList;
    for (const auto &folder: folders)
        idList.append(QString::number(folder.first));

    queryStr += idList.join(", ");
    queryStr += ")";

    if (userId != -1)
        queryStr += QString("AND userId='%1'").arg(userId);

    if (!query.exec(queryStr)) {
        qDebug() << "Database:" << "Can't delete objs" << db.lastError().text();
        return false;
    }

    return true;
}

bool Database::updateData(int id, const QString &key, const QString &value, const QString &tableName) {
    qDebug() << "Database:" << "Renaming for" << id << "-" << key << "-" << value
             << "-" << tableName;

    const QString queryStr = QString("UPDATE %1 SET %2 = :value WHERE id = :id").arg(tableName, key);
    query.prepare(queryStr);
    query.bindValue(":value", value);
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Database:" << "Can't update data" << db.lastError().text();
        return false;
    }

    return true;
}

bool Database::addMsg(int userId, int folderId, const QString &text) {
    qDebug() << "Database:" << "Adding message from" << userId << "to" << folderId;

    query.prepare("INSERT INTO Message (userId, folderId, text, status) VALUES (:userId, :folderId, :text, 0)");
    query.bindValue(":userId", userId);
    query.bindValue(":folderId", folderId);
    query.bindValue(":text", text);

    if (!query.exec()) {
        qDebug() << "Database:" << "Can't add msg" << db.lastError().text();
        return false;
    }

    return true;
}

bool Database::getMsgs(const int folderId, QVector<QVector<QString>> &msgs) {
    qDebug() << "Database:" << "Getting messages from folder" << folderId;

    QVector<QPair<int, QString>> folders;
    getSubFolders(-1, folderId, true, folders);

    QString queryStr = "SELECT * FROM Message WHERE chatId IN (";

    QStringList idList;
    for (const auto &folder: folders) {
        idList.append(QString::number(folder.first));
    }
    queryStr += idList.join(", ");
    queryStr += ")";

    if (!query.exec(queryStr)) {
        qDebug() << "Database:" << "Can't get messages" << db.lastError().text();
        return false;
    }

    while (query.next()) {
        // Handling
        // qDebug() << query.value();
    }

    return true;
}

bool Database::getSubFolders(const int userId, const int currentDirId, const bool tree,
                             QVector<QPair<int, QString>> &subFolders) {
    qDebug() << "Database:" << "Getting sub folders from" << currentDirId << "for" << userId << "with tree" << tree;
    if (tree) subFolders.append({currentDirId, ""});

    QQueue<int> q;
    q.enqueue(currentDirId);
    while (!q.isEmpty()) {
        if (userId != -1) {
            query.prepare("SELECT f.id, f.name "
                          "FROM Folder f "
                          "JOIN FolderUser fu ON f.id = fu.folderId "
                          "WHERE f.parentId = :parentId AND fu.userId = :userId");

            query.bindValue(":userId", userId);
        }
        else query.prepare("SELECT id, name FROM Folder WHERE parentId = :parentId");
        query.bindValue(":parentId", q.dequeue());

        if (!query.exec()) {
            qDebug() << "Database:" << "Can't get sub folders" << db.lastError().text();
            return false;
        }

        while (query.next()) {
            int id = query.value("id").toInt();
            QString name = query.value("name").toString();
            subFolders.append({id, name});
            if (tree)
                q.append(id);
        }
    }

    return true;
}

bool Database::getOnlineUsers(QVector<QPair<int, QString>> &users) {
    qDebug() << "Database:" << "Getting online users";
    query.prepare("SELECT person.userId, person.name "
                  "FROM Person person "
                  "JOIN User user ON person.userId = user.id "
                  "WHERE user.isOnline = 1");

    if (!query.exec()) {
        qDebug() << "Database:" << "Can't get users info" << db.lastError().text();
        return false;
    }

    while (query.next()) {
        int id = query.value("userId").toInt();
        QString name = query.value("name").toString();
        users.append({id, name});
    }
    return true;
}

bool Database::getUserName(int userId, QString &username) {
    qDebug() << "Database:" << "Getting username for" << userId;

    QSqlQuery t_query;
    t_query.prepare("SELECT name FROM Person WHERE userId=:userId");
    t_query.bindValue(":userId", userId);

    if (!t_query.exec()) {
        qDebug() << "Database:" << "Can't get username" << db.lastError();
        return false;
    }

    if (t_query.next()) username = t_query.value("name").toString();
    return true;
}

bool Database::getRootFolderUsers(int currentDirId, QVector<QPair<int, QString>> &users) {
    qDebug() << "Getting rootFolder users for folder" << currentDirId;

    query.prepare("SELECT parentId FROM Folder WHERE id = :folderId");
    query.bindValue(":folderId", currentDirId);
    if (!query.exec()) {
        qDebug() << "Database:" << "Can't get parentFolderId" << db.lastError().text();
        return false;
    }
    if (!query.next()) return true;

    int parentFolderId = query.value("parentId").toInt();
    qDebug() << "FolderParentID is" << parentFolderId;
    query.prepare("SELECT fu.userId "
                  "FROM FolderUser fu WHERE fu.userId NOT IN "
                  "(SELECT userId FROM FolderUser WHERE folderId = :parentId) "
                  "AND fu.folderId = :currentId");

    query.bindValue(":currentId", currentDirId);
    query.bindValue(":parentId", parentFolderId);

    if (!query.exec()) {
        qDebug() << "Database:" << "Can't get parentFolderId" << db.lastError().text();
        return false;
    }

    while (query.next()) {
        int id = query.value("userId").toInt();
        QString name;
        if (!getUserName(id, name))
            return false;
        users.append({id, name});
    }
    return true;
}
