#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <winsock2.h>
#include <algorithm>


// Функция обработки клиента в отдельном потоке
void handleClient(SOCKET clientSocket, std::mutex& mtx, std::vector<SOCKET>& clients) {
    while (true) {
        char buffer[1];
        int result = recv(clientSocket, buffer, sizeof(buffer), 0);
        std::cout << result << "\n";
        if (result > 0) {
            // Обработка принятого сообщения (в данном примере просто отправляем его всем клиентам)
            std::lock_guard<std::mutex> lock(mtx);
            for (SOCKET& client : clients) {
                if (client != clientSocket) {
                    send(client, buffer, result, 0);
                }
            }
        } else if (result == 0) {
            std::lock_guard<std::mutex> lock(mtx);
            closesocket(clientSocket);
            clients.erase(std::remove(clients.begin(), clients.end(), clientSocket), clients.end());
            break;
        } else {
            std::cerr << "Error receiving data from client: " << WSAGetLastError() << std::endl;
            break;
        }
    }
}

int main() {
    // Инициализация Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        return 1;
    }

    // Создание сокета
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Error creating socket: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // Настройка адреса сервера
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(1234);

    // Привязка сокета к адресу и порту
    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed with error: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Прослушивание сокета на подключения
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed with error: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::vector<SOCKET> clients;
    std::mutex mtx;

    while (true) {
        // Принятие нового клиента
        SOCKET clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Accept failed with error: " << WSAGetLastError() << std::endl;
            closesocket(serverSocket);
            WSACleanup();
            return 1;
        }
        else {
            std::cout << "Got new client!\n";
        }

        // Добавление клиента в список
        std::lock_guard<std::mutex> lock(mtx);
        clients.push_back(clientSocket);

        // Создание нового потока для обработки клиента
        std::thread(handleClient, clientSocket, std::ref(mtx), std::ref(clients)).detach();
    }

    // Очистка и выход
    closesocket(serverSocket);
    WSACleanup();
    return 0;
}
