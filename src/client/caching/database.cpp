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

bool Database::getAuth(const QString &login, QString &password) {
    qDebug() << "Database:" << "Getting auth data";

    query.prepare("SELECT * FROM User WHERE login=:login");
    query.bindValue(":login", login);

    if (!query.exec()) {
        qDebug() << "Database:" << "Can't get auth data" << db.lastError();
        return false;
    }

    if (query.next())
        password = query.value("password").toString();
    return true;
}

// data = (id, login, pass)
bool Database::addAuth(const QVector<QString> &data) {
    qDebug() << "Database:" << "Adding auth data";

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

bool Database::addFolderChain(int userId, int folderId) {
    qDebug() << "Database:" << "Adding folder chain between" << userId << "—" << folderId;

    QVector<int> folderIds;
    getSubFolderTree(-1, folderId, folderIds);

    QString queryStr = "INSERT INTO FolderUser (userId, folderId) VALUES ";
    QStringList valueList;

    // Формирование списка значений для добавления
    for (const auto id : folderIds) {
        valueList.append(QString("('%1', %2)").arg(userId).arg(id));
    }
    queryStr += valueList.join(", ");

    if (!query.exec(queryStr)) {
        qDebug() << "Database:" << "Can't add folder chains" << db.lastError().text();
        return false;
    }

    return true;
}

// При добавлении связи с папкой с подпапками тоже устанавливается связь
bool Database::removeFolderChain(const int userId, const int folderId) {
    qDebug() << "Database:" << "Deleting folder chain between" << userId << "—" << folderId;

    QVector<int> folderIds;
    getSubFolderTree(userId, folderId, folderIds);

    QString queryStr = "DELETE FROM FolderUser WHERE userId=:userId AND folderId IN (";
    QStringList idList;
    for (const auto id: folderIds)
        idList.append(QString::number(id));

    queryStr += idList.join(", ");
    queryStr += ")";

    query.prepare(queryStr);
    query.bindValue(":userId", userId);

    if (!query.exec()) {
        qDebug() << "Database:" << "Can't delete chains" << db.lastError().text();
        return false;
    }

    return true;
}

// Поиск всех id папок, корневую, связанных с данной папкой и с юзером
bool Database::getSubFolderTree(const int userId, const int rootId, QVector<int> &folderTree) {
    QQueue<int> q;
    q.enqueue(rootId);

    while (!q.isEmpty()) {
        qDebug() << "Database:" << "Getting subTree for" << userId << "—" << q.head();
        folderTree.append(q.head());

        if (userId != -1) {
            query.prepare("SELECT f.id "
                          "FROM Folder f "
                          "JOIN FolderUser fu ON f.id = fu.folderId "
                          "WHERE f.parentId = :parentId AND fu.userId = :userId");

            query.bindValue(":userId", userId);
        }
        else query.prepare("SELECT id FROM Folder WHERE parentId = :parentId");

        query.bindValue(":parentId", q.dequeue());

        if (!query.exec()) {
            qDebug() << "Database:" << "Can't get subTree" << db.lastError().text();
            return false;
        }

        while (!query.next())
            q.append(query.value("id").toInt());

    }
    return true;
}
