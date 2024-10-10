#include <iostream>
#include <string>
using namespace std;

// Method to find a substring in a string
// takes 2 constant references and returns starting index of subtring t1 in string t2.
int findSubtringIn(const string& t1, const string& t2) {
  size_t found = t2.find(t1);
  if (found != string::npos) {
    return found;
  } else {
    return -1;
  }
}

int main() {
  // Strings that can contain 100 characters.
  string t1, t2;

  // Get data from user
  cout << "Please enter a line of text: ";
  getline(cin, t2);
  cout << "Enter a word or line of thext to find in above: ";
  getline(cin, t1);

  // Search for t1 in t2 and present result.
  int result = findSubtringIn(t1, t2);
  if (result != -1) {
    cout << "The text you searched for starts at position: " << result
         << " in the string \"" << t2 << "\"" << endl;
  } else {
    cout << "Could not find " << t1 << " in \"" << t2 << "\".";
  }
}