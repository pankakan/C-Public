#include <iostream>
#include <cmath>
using namespace std;
int milageTY;
int milageLY;
int milageSinceLY;
float usedGas;
float gasperMile;

int main() {
    cout << "Milage meter today?: ";
    cin >> milageTY;
    cout << "Milage meter one year ago?: ";
    cin >> milageLY;
    milageSinceLY = milageTY - milageLY;
    cout << "Since last year your car has been driven " <<  milageSinceLY << " miles.\n";
    cout << "How many liters of gas was bought?: ";
    cin >> usedGas;
    gasperMile = round((usedGas/milageSinceLY)*100)/100;
    cout << "During last year the car used " << gasperMile << " liters of gas per mile.";
}