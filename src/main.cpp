#include <iostream>
#include <iomanip>
#include <vector>
// для работы со временем
#include <chrono>
// для работы с потоками
#include <thread>
#include "../include/network/networkAttack.h"
#include "../include/network/networkInfo.h"
#include "../include/network/stressTest.h"
#include "../include/network/configNetwork.h"
using namespace networkAtack;
using namespace networkInfo;
using namespace stressTest;
using namespace configNetwork;
// пространство имен std
using namespace std;
using namespace std::chrono_literals;
using namespace std::this_thread;

// объявляем функцию для выбора действия
void choosingOption();

int main() {;
    const string WHITE_TEXT = "\033[37m";
    const string RESET = "\033[0m";
    const string WHITE = "\033[97m";
    const string BLACK = "\033[40m";
    
    // создаем переменную timeout используя (chrono) в которой будет храниться интервал
    auto timeout = 1s;
                                      
    cout << BLACK << WHITE_TEXT << "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿" << RESET << endl;
    sleep_for(timeout);
    cout << BLACK << WHITE_TEXT << "⣿⣿⣿⣿⣿⣿⣿⣿ Hello my friend, this program is only ⣿⣿⣿⣿⣿⣿⣿⣿⣿" << RESET << endl;
    sleep_for(timeout);               
    cout << BLACK << WHITE_TEXT << "⣿⣿⣿⣿⣿ intended for legal pentesting, so I am not ⣿⣿⣿⣿⣿⣿⣿" << RESET << endl;
    sleep_for(timeout);               
    cout << BLACK << WHITE_TEXT << "⣿⣿⣿⣿⣿⣿ responsible for your activities. You are ⣿⣿⣿⣿⣿⣿⣿⣿" << RESET << endl;
    sleep_for(timeout);               
    cout << BLACK << WHITE_TEXT << "⣿⣿⣿⣿⣿⣿⣿⣿⣿ responsible for your own decisions ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿" << RESET << endl;
    sleep_for(timeout);
    cout << BLACK << WHITE_TEXT << "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿" << RESET << endl;
    sleep_for(timeout);
    cout << BLACK << WHITE <<  "⣿⣿⣿⣿⣿⡿⠿⠿⠿⠿⠿⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿" << RESET << endl;
    cout << BLACK << WHITE <<  "⣿⣿⣿⣿⣿⣿⠿⠒⠒⠒⠲⢶⣤⣄⠀⠀⠈⠛⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿" << RESET << endl;
    cout << BLACK << WHITE <<  "⣿⣿⣿⣿⡟⠁⠀⠀⠀⠀⠀⣀⠈⠻⣿⣦⡀⠀⠀⠙⠋⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿" << RESET << endl;
    cout << BLACK << WHITE <<  "⣿⣿⣿⣿⡇⠀⠀⠀⠀⠔⠺⣿⠷⠀⢹⣿⣿⡧⠀⠀⠀⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿" << RESET << endl;
    cout << BLACK << WHITE <<  "⣿⣿⣿⣿⠇⠀⠀⠀⢸⠀⠀⣽⠀⡆⠀⣿⡿⠃⢀⠀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿" << RESET << endl;
    cout << BLACK << WHITE <<  "⣿⣿⣿⣷⣤⣤⡀⠀⠀⠁⠷⠷⠎⠀⣸⡿⠇⠀⣸⣷⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿" << RESET << endl;   
    cout << BLACK << WHITE <<  "⣿⣿⣿⣿⣿⣿⡟⠀⠀⠀⠀⠀⠀⠊⠉⠀⣄⣴⣿⣿⣿⣿⣿⣿"<< BLACK << "     N E T S T A L K E R   " << WHITE <<"⣿⣿⣿⣿⣿" << RESET << endl; 
    cout << BLACK << WHITE <<  "⣿⣿⣿⣿⣿⣿⠁⠀⠀⠀⠀⠀⠀⠀⠐⠈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿" << RESET << endl;
    cout << BLACK << WHITE <<  "⣿⣿⣿⣿⣿⣿⡀⠀⠀⠠⢀⠀⠀⠀⠀⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿" << RESET << endl;
    cout << BLACK << WHITE <<  "⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿" << RESET << endl;
    cout << BLACK << WHITE <<  "⣿⣿⣿⣿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿" << RESET << endl;
    cout << BLACK << WHITE <<  "⣿⣿⣿⣶⣤⣀⠀⠀⠀⠀⠀⠀⠀⣤⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿" << RESET << endl;
    cout << BLACK << WHITE <<  "⣿⣿⣿⣿⣿⣿⣷⣶⣦⣤⣤⣴⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿" << RESET << endl;
    sleep_for(3s);
    
    // Запускаем Функцию выбора действий
    choosingOption();
    return 0;
}

// Функция для выбора действия
void choosingOption() {
    int option;
    
    while (true) {
        // Очистка экрана (работает на большинстве систем)
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        
        cout << left
             << "\033[93m----------------------------------------------------------------------------------------------\033[0m" << endl
             << "\033[101m|NETWORK|\033[0m" << endl
             << "\033[102m|   1   |\033[0m" << endl
             << "\033[93m----------------------------------------------------------------------------------------------\033[0m" << endl
             << "Please choose one option (0 to exit): ";
        
        if (!(cin >> option)) {
            cin.clear(); // очищаем флаги ошибок
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // игнорируем неправильный ввод
            cout << "Invalid input! Please enter a number." << endl;
            sleep_for(2s);
            continue;
        }
        
        switch (option) {
            case 0: {
                cout << "Exiting program..." << endl;
                sleep_for(1s);
                return;
            }
            case 1: {
                int variant;
                while (true) {
                    #ifdef _WIN32
                        system("cls");
                    #else
                        system("clear");
                    #endif
                    cout << left
                        << "\033[93m----------------------------------------------------------------------------------------------\033[0m" << endl
                        << "\033[101m|NETWORK_ATACK|\033[0m" << "   "
                        << "\033[101m|NETWORK_INFO|\033[0m" << "   "
                        << "\033[101m|STRESS_TEST|\033[0m" << "   "
                        << "\033[101m|CONFIG_NETWORK|\033[0m" << "   " << endl
                        << "\033[102m|      1      |\033[0m" << "   "
                        << "\033[102m|     2      |\033[0m" << "   "
                        << "\033[102m|     3     |\033[0m" << "   "
                        << "\033[102m|      4       |\033[0m" << "   " << endl
                        << "\033[93m----------------------------------------------------------------------------------------------\033[0m" << endl
                        << "Please choose one option (0 to go back): ";
                    
                    if (!(cin >> variant)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input! Please enter a number." << endl;
                        sleep_for(2s);
                        continue;
                    }
                    
                    switch (variant) {
                        case 0:
                            return; // Возврат в главное меню
                        case 1: {
                            cout << "\n";
                            versionAtack myAtack;
                            myAtack.display();
                            cout << "\nPress Enter to continue...";
                            cin.ignore();
                            cin.get();
                            break;
                        }
                        case 2: {
                            cout << "\n";
                            informate info;
                            info.networkInfo();
                            cout << "\nPress Enter to continue...";
                            cin.ignore();
                            cin.get();
                            break;
                        }
                        case 3:{
                            cout << "\n";
                            testing test;
                            test.testNetwork();
                            cout << "\nPress Enter to continue...";
                            cin.ignore();
                            cin.get();
                            break;
                        }
                        case 4:{
                            cout << "\n";
                            configuration config;
                            config.configure();
                            cout << "\nPress Enter to continue...";
                            cin.ignore();
                            cin.get();
                            break;
                        }
                        default:
                            cout << "Invalid option! Please choose again." << endl;
                            sleep_for(2s);
                            break;
                    }
                }
                break;
            }
            default: {
                cout << "Invalid option! Please choose again." << endl;
                sleep_for(2s);
                break;
            }
        }
    }
}