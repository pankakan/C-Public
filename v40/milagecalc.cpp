#include <iostream>
using namespace std;

int main() {
    int milagety;
    int milagelasty;
    int milagesincely;
    cout << "Milage meter today?: ";
    cin >> milagety;
    cout << "Milage meter one year ago?: ";
    cin >> milagelasty;
    milagesincely = milagety - milagelasty;
    cout << "Since last year your car has driven " <<  milagesincely << " miles.";
    }