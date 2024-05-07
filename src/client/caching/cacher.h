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

    bool auth(const QVector<QString> &data) { return db.addAuth(data); }

private:
    Database db;

private:
    Cacher() { };

    ~Cacher() { };
};


#endif //CHAT_CACHER_H
