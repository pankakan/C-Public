#include <iostream> 
#include <cmath>
using namespace std;
int gallonPerMile;
float kmPerMile = 1.609;
float litrePerGallon = 3.785;


int main() 
{
    cout << "How many miles per gallon does your car do?";
    cin >> gallonPerMile;
    float literPerMil = round(((gallonPerMile * litrePerGallon)/kmPerMile*10)*100)/100;
    cout << "That is " << literPerMil <<" liter per metric mile.";
};
