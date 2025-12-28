
### netStalker:
*   Прошу внимания, проект еще не готов, создана база проекта, но функционал еще не доведен до ума.
##  Цель проекта
*   Создать инструмент, который объеденит всю базу по пинтесту сети в одном проекте
*   Решить проблему с огромным количеством программ, предназначенных для отдельной отладки и защиты сети
*   Сделать простой быстрый инструмент, который может работать как в браузере так и в консоле


# Структура проекта
netStalker/
├── CMakeLists.txt
├── Dockerfile
├── README.md
├── LICENSE.md
├── include/                    # Только заголовки
│   ├── network/
│   │   ├── configNetwork.h
│   │   ├── networkAttack.h    # Исправлено Atack -> Attack
│   │   ├── networkInfo.h
│   │   └── stressTest.h
│   └── server/
│       └── server.h
├── src/                       # Исходные файлы
│   ├── network/
│   │   ├── configNetwork.cpp
│   │   ├── networkAttack.cpp
│   │   ├── networkInfo.cpp
│   │   └── stressTest.cpp
│   ├── server/
│   │   └── server.cpp
│   └── main.cpp              # Бывший netStalker.cpp
├── web/                       # Веб-интерфейс отдельно
│   ├── src/
│   │   ├── index.html
│   │   ├── style.css
│   │   └── app.js
│   └── webpack.config.js
├── tests/                     # Тесты
│   ├── unit/
│   │   └── test.cpp
│   └── integration/
└── scripts/                   # Вспомогательные скрипты


1)Сборка production образа:
    docker build -t netstalker:latest .
2)Сборка development образа:
    docker build --target development -t netstalker-dev:latest .
3)Запуск через Docker Compose:
    docker-compose up -d
4)Запуск development окружения:
    make run-dev
5)Запуск production окружения:
    make run