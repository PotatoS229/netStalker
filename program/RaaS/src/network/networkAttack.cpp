#include "../../include/network/networkAttack.h"
using namespace std;
namespace networkAtack{
    //вывод в консоль существующих атак 
    void versionAtack::display(){
        for(const auto& item:atackMitm){
            cout << item << endl;
        }
    }
}
