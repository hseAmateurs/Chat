//
// Created by Shon on 06.05.2024.
//

#ifndef CHAT_CONFIG_H
#define CHAT_CONFIG_H

#include <QString>

namespace cfg {
    namespace database {
        const QString FILENAME = "cache.sqlite3";
    }
    enum auth {
        OK,
        BAD_PASS,
        NOT_FOUND,
        UNKNOWN
    };

    namespace foldersView {
        const int rowCount = 4;
        const int columnCount = 4;
        const int space = 20;
    }

    const int ROOT_OFFSET = 1000;

    namespace network {
        const QByteArray HELLO_CODE = "A";
    }
}

#endif //CHAT_CONFIG_H
