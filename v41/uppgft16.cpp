#include <iostream>
using namespace std;

int main() {
  // Sorted array
  int f[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int n = 10;
  int tal, k;

  // Ask for number to find
  cout << "Vilket tal letar du efter? ";
  cin >> tal;

  // Loop through array and stop at end of array or if number is found
  for (k = 0; k < n && f[k] < tal; k++);

  // Print if loop reached end of array and end of array is not the droid we are
  // looking for.
  if (k == n || f[k] != tal) cout << "Talet finns ej" << endl;
  // Print numbers position if found.
  else
    cout << "Talet finns pa plats: " << k << endl;
}