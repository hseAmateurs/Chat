//
// Created by Shon on 06.05.2024.
//

#ifndef CHAT_TABLES_H
#define CHAT_TABLES_H

#include <QString>
#include <QVector>

const QString USER = "CREATE TABLE User ("
                     "id INTEGER PRIMARY KEY,"
                     "login TEXT UNIQUE,"
                     "password TEXT,"
                     "isOnline INTEGER DEFAULT 0"
                     ");";

const QString PERSON = "CREATE TABLE Person ("
                       "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                       "userId INTEGER REFERENCES User(id),"
                       "name TEXT NOT NULL"
                       ");";

const QString FOLDER = "CREATE TABLE Folder ("
                       "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                       "parentId INTEGER REFERENCES Folder(id),"
                       "name TEXT NOT NULL"
                       ");";

const QString FOLDER_USER = "CREATE TABLE FolderUser ("
                            "userId INTEGER REFERENCES User(id),"
                            "id INTEGER REFERENCES Folder(id)"
                            ");";

const QString MESSAGE = "CREATE TABLE Message ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "userId INTEGER REFERENCES User(id),"
                        "chatId INTEGER REFERENCES Folder(id),"
                        "status INTEGER,"
                        "text TEXT NOT NULL,"
                        "sendTime DATETIME DEFAULT CURRENT_TIMESTAMP"
                        ");";

const QVector<QString> TABLES_INIT = {USER, PERSON, FOLDER, FOLDER_USER, MESSAGE};


#endif //CHAT_TABLES_H
