#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

using namespace std;

// Enum class that represents choices with a number.
enum class Choice { ROCK, PAPER, SCISSOR, INVALID, STOP };

// Global variabels to hold scores.
int userScore = 0;
int aiScore = 0;
int userWins = 0;
int aiWins = 0;

// Function to get user input.
Choice askUser() {
  // Define string-var for user answer and define Choice-var that holds choice.
  string answer;
  Choice userChoice = Choice::INVALID;

  // Run while no valid choice has been set to Choice-var.
  while (userChoice == Choice::INVALID) {
    cout << "\nRock, paper or scissor?: ";
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
    } else if (answer == "stop") {
      userChoice = Choice::STOP;
    } else {
      cout << "Invalid input, try again. \n";
    }
  }
  return userChoice;
}

// Function to generate ai choice.
Choice randChoice() {
  int randomChoice = rand() % 3;  // Return a random value between 0-2.

  // Switch to  convert random choice to Choice-value
  switch (randomChoice) {
    case 0:
      return Choice::ROCK;
    case 1:
      return Choice::SCISSOR;
    default:
      return Choice::PAPER;
  }
}

// Function to compare ai and user choice and print result.
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

  // Print choices
  cout << "\nYour choice: " << userStr << endl;
  cout << "Computers choice: " << aiStr << endl;

  // Compare users input with random generated choice from coputer and print
  // results.
  if (userChoice == aiChoice) {
    cout << "\nIt's a tie.\n";
  } else if ((userChoice == Choice::ROCK && aiChoice == Choice::SCISSOR) ||
             (userChoice == Choice::SCISSOR && aiChoice == Choice::PAPER) ||
             (userChoice == Choice::PAPER && aiChoice == Choice::ROCK)) {
    cout << "\nYou won this round :D\n";
    userScore++;
  } else {
    cout << "\nComputer won this round :(\n";
    aiScore++;
  }
}

// Function to run game.
void game() {
  userScore = 0;
  aiScore = 0;
  int numberOfGames = 3;

  cout << "\nEnter \"Stop\" to give up this round.\n";
  cout << "You will be playing against a computer, first to score "
       << numberOfGames << " points will win the round." << endl;
  while (userScore < numberOfGames && aiScore < numberOfGames) {
    // Get choices from user and computer.
    Choice userChoice = askUser();

    // Check if user want to give up.
    if (userChoice == Choice::STOP) {
      cout << "The game has ended.\n";
      return;
    }
    Choice aiChoice = randChoice();
    // Compare and print result.
    printWinner(userChoice, aiChoice);

    cout << "\nThe score: You " << userScore << " - Computer " << aiScore
         << endl;
  }

  // Print winner of the game after either user och ai reach 3 points.
  if (userScore == 3) {
    cout << "You won the game :D\n";
    userWins++;
  } else {
    cout << "Computer won the game :(\n";
    aiWins++;
  }
}

// Function to print score.
void printScore() {
  cout << "\n--- Statistics ---\n";
  cout << "Player wins: " << userWins << "\n";
  cout << "Computer wins: " << aiWins << "\n";
  cout << "-------------------\n";
}

// Function to print menu.
void printMenu() {
  cout << "\n --- Menu ---\n";
  cout << "1. Start a new game\n";
  cout << "2. Print statistics\n";
  cout << "3. Exit the game\n";
  cout << "Enter your choice [1-3]: ";
}

// Function to print menu and exectute user command.
void menu() {
  int menuChoice;
  // Print menu as long as user dont choose to exit
  do {
    printMenu();
    // cin >> menuChoice; <-- Old code.
    while (!(cin >> menuChoice)) {
      cin.clear();
      cin.ignore(10000, '\n');
      cout << "\nInvalid input, try again.\n";
      printMenu();
    }

    switch (menuChoice) {
      case 1:
        game();
        break;
      case 2:
        printScore();
        break;
      case 3:
        cout << "Exiting the game..\n";
        break;
      default:
        cout << "Invalid input, try again!\n";
    }
  } while (menuChoice != 3);
}

// Main function.
int main() {
  // Generate a random seed for rand-function.
  srand(time(0)); // Should probably move to game-function.
  menu();

  return 0;
}

/*
Functions to implement later

* Add the possibility for the user to determine how many rounds one game is.

* Add visual graphics in ascii

* Extend program to be used with raspberry pi pico and 3 input buttons for rock
paper scissor and lights to determine winner and led to show score.

* Store scores in struct.

* Build a function for advanced statistics (Choices made Rounds won etc.)

*/
