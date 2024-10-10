#include <cstring>
#include <iostream>
using namespace std;

// Method to find a substring in a string
// takes 2 constant pointers and returns starting index of substring t1 in string t2.
int findSubtringIn(const char* t1, const char* t2) {
  const char* found = strstr(t2, t1);
  if (found != nullptr) {
    return found - t2;
  } else {
    return -1;
  }
}

int main() {
  // Cstrings that can contain 100 characters.
  char t1[100], t2[100];

  // Get data from user
  cout << "Please enter a line of text: ";
  cin.getline(t2, 100);
  cout << "Enter a word or line of thext to find in above: ";
  cin.getline(t1, 100);

  // Search for t1 in t2 and present result.
  int result = findSubtringIn(t1, t2);
  cout << "The text you searched for starts at position: " << result
       << " in the string \"" << t2 << "\"" << endl;
}