// Начинаем разработку tcp-сервера
#include <sys/socket.h> // 
#include <sys/types.h> //
#include <netinet/in.h> //
#include <arpa/inet.h> //
#include <unistd.h> //содержит классические ментоды, на подобии close или read()

#include <iostream>

using namespace std;
//Точка входа 
int main(){
    //Создаем серверный сокет, TCP
    //Расмотрим поподробнее
    /*функция socket() содержится в библиотеки sys/socket.h
    при создаении требуется указать домен - то есть пространство в котором будит рабоатьт сокет 
    у нас это IPv4, тип то есть как у нас будет происходить работа, а так же протакоол в нашем случае это TCP*/
    int server_socket = socket(AF_INET, SOCK_STREAM , IPPROTO_TCP);
    cout << server_socket << endl; //server_socket возвращает нам дескриптор 
    
}