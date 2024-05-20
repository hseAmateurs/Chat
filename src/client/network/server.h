//
// Created by Shon on 21.05.2024.
//

#ifndef CHAT_SERVER_H
#define CHAT_SERVER_H

#include <QObject>
#include <QTcpSocket>

class Server : public QObject {
Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr) : QObject(parent), socket(new QTcpSocket(this)) {
        connect(socket, &QTcpSocket::readyRead, this, &Server::readMessage);
    }

    void connectToServer(const QString &hostName, quint16 port) {
        socket->connectToHost(hostName, port);
        if (!socket->waitForConnected()) {
            qDebug() << "Error: " << socket->errorString();
        }
    }

public slots:

    void sendMessage() {
        if (socket->state() == QAbstractSocket::ConnectedState) {
            socket->write("A");
        }
        else {
            qDebug() << "Error: Not connected to server";
        }
    }

signals:

    void messageReceived();

private slots:

    void readMessage() {
        QByteArray data = socket->readAll();
        emit messageReceived();
    }

private:
    QTcpSocket *socket;
};


#endif //CHAT_SERVER_H
