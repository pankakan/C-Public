#include <iostream>
#include <iomanip>
#include <limits>
#include <stdexcept>
using namespace std;

// Function that recieve 2d-array of values and calculates each values amount
void calc_change(int price, int payed, int change_table[6][2]) {
        int change = payed - price;

        // Values that are going to be used
        int listOfValues[] = {100,50,20,10,5,1};

        for (int i = 0; i < 6; i++) {
            change_table[i][0] = listOfValues[i]; // Set the value
            change_table[i][1] = change / listOfValues[i]; // Calculate how much of the value the change contains.
            change %= listOfValues[i]; // Set change to be the remaining values 
        }
    }

// Function to ask price from user and change the global variables.
void get_price(int &price) {
    while (true) {
        cout << "What is the price?: ";

        // Set price and validate
        if (cin >> price && price > 0) {
            break; // Break when if input is valid.
        }

        // Clear error state if price wasnt set correctly
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        // Print error
        cerr << "Invalid input for price. Please enter a valid price. \n";
 
    }
}

// Function to ask payed from user and change the global variables.
int get_payment(int &payed, int price) {
    while (true) {
        cout << "How much did you pay?: ";

        // Set payed and validate
        if (cin >> payed && payed > 0) {
            int status = payed - price;
            if (status == 0 ) {
                cerr << "You have broken even, there is no change, there is no spoon, there is only darkness.\n";
                return 0;
            } else if (status < 0) {
                cerr <<  "You are trying to pay less than the price, you shall not pass!\n";
                continue;
            } else {
                return 1;
            }
        }
        // Clear error state if payed wasnt set correctly
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        // Print error
        cerr << "Invalid input for payed. Please enter a valid value.\n";
    }
}

// Function to print a table of values and their amouunts.
void print_change(int price, int payed, int change_table[6][2]) {
    cout << "Price: " << price << "\n";
    cout << "Payed: " << payed << "\n";
    cout << "Your change:\n";
    cout << "100kr-bills : " << change_table[0][1] << endl;
    cout << "50kr-bills  : " << change_table[1][1] << endl;
    cout << "20kr-bills  : " << change_table[2][1] << endl;
    cout << "10kr-coins  : " << change_table[3][1] << endl;
    cout << "5kr-coins   : " << change_table[4][1] << endl;
    cout << "1kr-coins   : " << change_table[5][1] << endl;
    
}

int main() {
    int price, payed;

    // Ask user for price
    get_price(price);

    // Get payment from user and validate status. 
    int status = get_payment(payed,price);

    // If status says change is available; calculate and print the change-table.
    if (status == 1) {
        // Array to send to calc_change
        int change_table[6][2] = {0};
                
        // Send userdata and array to calculate-function
        calc_change(price, payed,change_table);

        // Print results
        print_change(price, payed, change_table);
    }
}