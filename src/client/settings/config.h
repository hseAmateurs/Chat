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
        const int columnCount = 5;
        const int space = 20;
    }
}

#endif //CHAT_CONFIG_H
