// #include <cstring>
// #include <netinet/in.h>
// #include <sys/socket.h>
// #include <unistd.h>
// #include <iostream>
// #include <fstream>
// #include <sstream>

// int main() {
//     // 1. Создание сокета
//     int server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//     if (server_socket == -1) {
//         std::cerr << "Ошибка при создании сокета" << std::endl;
//         return 1;
//     }

//     // 2. Настройка адреса сервера
//     struct sockaddr_in server_addr;
//     memset(&server_addr, 0, sizeof(server_addr));
//     server_addr.sin_addr.s_addr = INADDR_ANY;
//     server_addr.sin_port = htons(8080);
//     server_addr.sin_family = AF_INET;

//     // 3. Привязка сокета к адресу
//     if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
//         std::cerr << "Ошибка привязки адреса к сокету" << std::endl;
//         close(server_socket);
//         return 1;
//     } else {
//         std::cout << "Сервер запущен на порту 8080" << std::endl;
//     }

//     // 4. Начало прослушивания
//     if (listen(server_socket, 5) == -1) {
//         std::cerr << "Ошибка прослушивания" << std::endl;
//         close(server_socket);
//         return 1;
//     } else {
//         std::cout << "Сервер ожидает подключений..." << std::endl;
//     }

//     // 5. Функция для чтения HTML-файла
//     auto read_html_file = [](const std::string& filename) -> std::string {
//         std::ifstream file(filename);
//         if (!file.is_open()) {
//             std::cerr << "Не удалось открыть файл: " << filename << std::endl;
//             return "";
//         }
        
//         std::stringstream buffer;
//         buffer << file.rdbuf();
//         return buffer.str();
//     };

//     // 6. Чтение HTML-файла один раз при запуске сервера
//     std::string html_content = read_html_file("index.html");
//     if (html_content.empty()) {
//         std::cerr << "Файл index.html пуст или не найден. Используется заглушка." << std::endl;
//         html_content = "<html><body><h1>Файл index.html не найден!</h1></body></html>";
//     }

//     // 7. Главный цикл сервера
//     while (true) {
//         struct sockaddr_in client_addr;
//         socklen_t client_len = sizeof(client_addr);

//         // 8. Принятие входящего соединения
//         int client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_len);
//         if (client_socket == -1) {
//             std::cerr << "Ошибка accept: " << strerror(errno) << std::endl;
//             continue; // Продолжаем работу, не завершая программу
//         }

//         // 9. Чтение запроса от клиента (опционально, для логирования)
//         char buffer[1024] = {0};
//         int bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
//         if (bytes_received > 0) {
//             buffer[bytes_received] = '\0';
//             std::cout << "Получен запрос от клиента:\n" << buffer << std::endl;
//         }

//         // 10. Формирование HTTP-ответа с содержимым HTML-файла
//         std::string response = "HTTP/1.1 200 OK\r\n";
//         response += "Content-Type: text/html; charset=UTF-8\r\n";
//         response += "Content-Length: " + std::to_string(html_content.length()) + "\r\n";
//         response += "Connection: close\r\n";
//         response += "\r\n"; // Пустая строка разделяет заголовки и тело
//         response += html_content;

//         // 11. Отправка ответа клиенту
//         int bytes_sent = send(client_socket, response.c_str(), response.length(), 0);
//         if (bytes_sent > 0) {
//             std::cout << "Ответ отправлен клиенту (" << bytes_sent << " байт)" << std::endl;
//         } else {
//             std::cerr << "Ошибка отправки ответа" << std::endl;
//         }

//         // 12. Закрытие соединения с клиентом
//         close(client_socket);
//         std::cout << "Соединение с клиентом закрыто.\n" << std::endl;
//     }

//     // 13. Закрытие серверного сокета (эта строка никогда не выполнится в данном примере)
//     close(server_socket);
//     return 0;
// }

#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <iostream>

int main(){
    int serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == -1){
        std::cerr << "Error" << std::endl;
    } else {
        std::cout << "Создание сокета прошла успешно" << std::endl;
    }

    struct sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.sin_addr.s_addr = INADDR_ANY;
    sockAddr.sin_port = htons(8080);
    sockAddr.sin_family = AF_INET;

    if (bind(serverSocket, (struct sockaddr*)&sockAddr, sizeof(serverSocket)) == -1) {
        std::cerr << "Ошибка конекта сокета и адреса" << std::endl;
    } else {
        std::cout << "Удачный конект адреса и сокета" << std::endl;
    }

    if (listen(serverSocket, 5) == -1) {
        std::cerr << "Ошибка прослушивания сокета" << std::endl;
    } else {
        std::cout << "Успешно прослушивается" << std::endl;
    }

}