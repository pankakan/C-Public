#include <iostream> 
#include <cmath>
#include <iomanip>
using namespace std;

int main() 
{
int hours_f, minutes_f, seconds_f, totalSeconds_f;
int hours_s, minutes_s, seconds_s, totalSeconds_s;
int hours_dif, minutes_dif, seconds_dif;
int hours_total, minutes_total, seconds_total;
int differenceInSecondsTotal;
    cout << "Enter lapse-time for first lapse [hh mm ss]";
    cin >> hours_f >> minutes_f >> seconds_f;
    totalSeconds_f = (hours_f * 3600) + (minutes_f * 60) + seconds_f;
    cout << "Enter lapse-time for second lapse [hh mm ss]";
    cin >> hours_s >> minutes_s >> seconds_s;
    totalSeconds_s = (hours_s * 3600) + (minutes_s * 60) + seconds_s;
    hours_total = hours_f + hours_s;
    minutes_total = minutes_f + minutes_s;
    seconds_total = seconds_f + seconds_s;
    differenceInSecondsTotal = totalSeconds_f - totalSeconds_s;
    if (differenceInSecondsTotal < 0) {
        differenceInSecondsTotal *= -1;
    }
    hours_dif = differenceInSecondsTotal/3600;
    minutes_dif = (differenceInSecondsTotal%3600)/60;
    seconds_dif = differenceInSecondsTotal % 60;
    cout << "Your total time for both lapse was: " <<  setw(2) << setfill('0') << hours_total << ":" <<  setw(2) << setfill('0') << minutes_total << ":" <<  setw(2) << setfill('0') << seconds_total << "." << endl;
    cout << "And the difference were: " << setw(2) << setfill('0') << hours_dif << ":" << setw(2) << setfill('0') << minutes_dif << ":" << setw(2) << setfill('0') << seconds_dif << "." << endl ;
};
