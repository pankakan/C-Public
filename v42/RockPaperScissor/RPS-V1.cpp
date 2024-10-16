#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

using namespace std;

// Enum class that represents choices with a number.
enum class Choice { ROCK, PAPER, SCISSOR, INVALID };

Choice askUser() {
  // Define string-var for user answer and define Choice-var that holds choice.
  string answer;
  Choice userChoice = Choice::INVALID;

  // Run while no valid choice has been set to Choice-var.
  while (userChoice == Choice::INVALID) {
    cout << "Rock, paper or scissor?: ";
    cin >> answer;

    // Use transform-function to set user input to all lower case.
    transform(answer.begin(), answer.end(), answer.begin(), ::tolower);

    // Handle user input and set to correct enum-Choice.

    if (answer == "rock") {
      userChoice = Choice::ROCK;
    } else if (answer == "scissor") {
      userChoice = Choice::SCISSOR;
    } else if (answer == "paper") {
      userChoice = Choice::PAPER;
    } else {
      cout << "Invalid input, try again. \n";
    }
  }
  return userChoice;
}

Choice randChoice() {
  int randomChoice = rand() % 3;  // Return a random value between 0-2.
  if (randomChoice == 0) return Choice::ROCK;
  if (randomChoice == 1) return Choice::SCISSOR;
  return Choice::PAPER;
}

void printWinner(Choice userChoice, Choice aiChoice) {
  // Convert Choice-vars to strings for output.
  string userStr;
  if (userChoice == Choice::ROCK)
    userStr = "Rock";
  else if (userChoice == Choice::SCISSOR)
    userStr = "Scissor";
  else
    userStr = "Paper";

  string aiStr;
  if (aiChoice == Choice::ROCK)
    aiStr = "Rock";
  else if (aiChoice == Choice::SCISSOR)
    aiStr = "Scissor";
  else
    aiStr = "Paper";

  // Compare users input with random generated choice from coputer and print
  // results.
  if (userChoice == aiChoice) {
    cout << "It's a tie.\n";
  } else if ((userChoice == Choice::ROCK && aiChoice == Choice::SCISSOR) ||
             (userChoice == Choice::SCISSOR && aiChoice == Choice::PAPER) ||
             (userChoice == Choice::PAPER && aiChoice == Choice::ROCK)) {
    cout << "You won!\n";
  } else {
    cout << "Computer won!\n";
  }
}

int main() {
  // Generate a random seed for rand-function.
  srand(time(0));

  // Get choices from user and computer.
  Choice userChoice = askUser();
  Choice aiChoce = randChoice();

  // Compare and print result.
  printWinner(userChoice, aiChoce);
  return 0;
}