#include <iostream>
using namespace std;

// Bubble sort algorithm, takes an array and number of elements to be sorted.
void bubbleSort(int array[], int size) {
  for (int i = 0; i < size - 1; i++) {
    bool swapped = false;
    for (int j = 0; j < size - i - 1; j++) {
      // Compare each element of the array with the element that comes after
      if (array[j] > array[j + 1]) {
        // Swap places if not in order.
        int temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
        swapped = true;
      }
    }
    // Makes sure if last iteration contained no swap, eg. the array was already
    // sorted, the loop will stop.
    if (!swapped) {
      break;
    }
  }
}

int main() {

  const int MAX_TAL = 100; // Max inputs.
  int f[MAX_TAL];
  int tal, antal = 0;

  cout << "Mata in heltal och tryck ctrl+z, eller d beroende på OS, följt av "
          "[Enter] för att avsluta och se dina heltal sorterade:"
       << endl;

  while (antal < MAX_TAL) {
    if (cin >> tal) {
      // If input is correct, keep going.
      f[antal] = tal;
      antal++;
    } else {
      if (cin.eof()) {
        // If user stops with ctrl-z/d, break.
        cout << "Tack för dina tal, de sorteras nu." << endl;
        break;
      } else {
        // If input is not correct, clear buffer and repeat.
        cout << "Felaktig indata, försök igen." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
      }
    }
  }

  if (antal == 0) {
    // Exit program if no numbers were input.
    cout << "Inga tal att sortera." << endl;
    return 1;
  }

  // Sort array.
  bubbleSort(f, antal);

  // Print result.
  cout << endl << "Dina sorterade tal är: " << endl << endl;
  for (int i = 0; i < antal; i++) {
    cout << f[i] << endl;
  }
  return 0;
}