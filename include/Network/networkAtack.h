#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>

namespace networkAtack{
    struct versionAtack{
        std::vector<std::string> atackMitm = {"1)Анализ сетевого трафика (сниффинг)", "2)Подмена доверенного объекта (спуфинг)", "3)Внедрение ложного объекта", "4)Отказ в обслуживании (DoS/DDoS)", "5)Атака на уязвимости протоколов", "6)Ближайший сосед (через Wi-Fi)"};
        //следуя принципам SRP
        //Вывод существующих атак в консоль
        void display();
    };
}