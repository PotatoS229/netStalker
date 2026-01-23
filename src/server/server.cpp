//Сетевые библиотеки 
#include <sys/socket.h> // Нужен для создагия сокета 
#include <sys/types.h> // Содержит оптимизатор типов и тыпы для системных вызывово
#include <netinet/in.h> // Содержит структуры для интернет адресов
#include <arpa/inet.h> // Помогает в конвертации адреса 

//Базовые библиотеки 
#include <string.h> // Для работы со строками 
#include <iostream> // ввод и вывод
#include <iomanip> // манипулятор вывода
#include <unistd.h> // Системные вызовы(close, read, write) 
#include <stdlib.h> // Стандартные функции(exit) 

//Дополнительные библиотеки
#include <fcntl.h> // Управление файловыми дискрипторами 
#include <sstream> // Потоковые строки
#include <fstream> // работа с файлами 

//Константы
#define SERVER_IP "127.0.0.1" // локальный хост 
#define SERVER_PORT 9020 // Порт 
#define BUFFER_SIZE 4096 // Размер буфера для чтения запроса 
#define WEB_ROOT "web/src/" // Корневая директория веб-сайта 

// Пространство имен 
using namespace std;






//Основная функция 
int main(){
    //Создаем сокет
    int server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(server_socket == -1){
        cerr << "Ошибка создания сокета";
        exit(1);
    }    
    //Создаем адрес
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);
    server_address.sin_addr.s_addr = inet_addr(SERVER_IP);
    if (server_address.sin_addr.s_addr == INADDR_NONE) {
        cerr << "Неверный IP адрес" << endl;
        exit(1);
    }
    //Проверяем и соединяем адрес и сокет
    if(bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address)) == -1){
        cerr << "Ошибка соединения сокета и адреса" << endl;
        close(server_socket);
        exit(1);
    }
    //Запускаем процесс listen
    if(listen(server_socket, 5) == -1){
        cerr << "Процесс listen ошибка" << endl;
        close(server_socket);
        exit(1);
    }
    cout << "Сервер запущен и ожидает подключений на " << SERVER_IP << ":" << SERVER_PORT << endl;

    //В цикле обрабатываем сорединение между клиентом и сервером
    while(true){
        //Создаем клиентский сокет и принимаем соединение
        // accept - принимает соединение, создает новый сокет для клиента 
        int client_socket = accept(server_socket, NULL, NULL);
        if(client_socket == -1){
            cerr << "Ошибка принятия сокета" << endl;
        }
        //Отправляем юзеру сообщение    
        char message[256] = "You have reached the server!";
        if(!(send(client_socket,  message, sizeof(message), 0))){
            cerr << "Ошибка отправки сообщения" << endl;
        }
        close(client_socket);
    }
    //Закрываем сокет и выходим из программы 
    close(server_socket);
    return 0;
}