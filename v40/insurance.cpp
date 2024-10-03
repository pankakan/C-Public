#include <iostream>
using namespace std;
int car_yearbought;
int year_today;
int carage;
const int veteraninsurance = 25;
const int lowinsurancelevel = 5;

int main() {
    cout << "When was your car bought?: ";
    cin >> car_yearbought;
    cout << "What year is it now?: ";
    cin >> year_today;
    carage = year_today - car_yearbought;
    if (carage >=  veteraninsurance) {
        cout << "Get a veteran insurance.";
    } else if (carage >= lowinsurancelevel){
        cout << "Get a half insurance.";
    } else {
        cout << "Get a whole insurcance";
    }
    }