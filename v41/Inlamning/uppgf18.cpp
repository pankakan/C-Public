#include <iostream>
using namespace std;

// This is a the starting year.
const int FIRST_YEAR = 2000;

// Recursive function to calculate salary in a specied year.
double salaryCalc(int calcForYear) {
  // Calculate how many years since starting year.
  int years = calcForYear - FIRST_YEAR + 1;
  // First years payment.
  if (years == 1) {
    return 150000.0;
  } else {
    // Recursive calculation that adds raise.
    return salaryCalc(calcForYear - 1) * 1.04 + 400;
  }
}

int main() {
  // Ask user for year they would like to know salary for and keep asking until
  // correct input.
  int calcForYear;
  do {
    cout << "You started at this company in the year " << FIRST_YEAR
         << ". Enter a year in which you want to know your salary: ";
    cin >> calcForYear;

    // Check input is correct.
    if (cin.fail()) {
      cout << "Incorrect input, try again.\n";
      cin.clear();
      cin.ignore(10000, '\n');
      continue;
    }

    // Check the year user ask is actually after starting year.
    if (calcForYear < FIRST_YEAR) {
      cout << "Incorrect input, try again.\n";
    }
  } while (calcForYear < FIRST_YEAR);

  // Calcule how many years

  double salary = salaryCalc(calcForYear);
  cout << "In " << calcForYear << " you would have worked "
       << calcForYear - FIRST_YEAR + 1
       << " years in this company. Your salary would be: " << salary << " SEK."
       << endl;
}
