#include <iostream>
#include <string>
#include <vector>
#include "library.cpp"


int displayMenu() {
  int choice;
  std::cout << "\n ===Library System===\n";
  std::cout << "1.  Create a new book or magazine.\n";
  std::cout << "2.  Register a new user.\n";
  std::cout << "3.  List all items\n";
  std::cout << "4.  List all availible items.\n";
  std::cout << "5.  List all unavailible items.\n";
  std::cout << "6.  Borrow an item to user.\n";
  std::cout << "7.  Return an item from user.\n";
  std::cout << "8.  List all users.\n";
  std::cout << "9. List all users with borrowed items.\n";
  std::cout << "10. Save and Exit\n";
  std::cout << "======================\n";
  std::cout << "\nChoose an option: ";
  std::cin >> choice;
  return choice;
}

void createNewItem(Library& library) {
  std::string type, title, author;
  int year, extra;
  std::cout << "Enter type (Book/Magazine): ";
  std::cin >> type;
  std::cin.ignore();

  if (type != "Book" && type != "Magazine") {
    std::cout << "Invalid type. Returning to menu";
    return;
  }

  std::cout << "Enter title: ";
  std::getline(std::cin, title);
  std::cout << "Enter author: ";
  std::getline(std::cin, author);
  std::cout << "Enter year: ";
  std::cin >> year;
  std::cin.ignore();
  if (type == "Book") {
    std::cout << "Enter number of pages: ";
  } else if (type == "Magazine") {
    std::cout << "Enter issue number: ";
  }
  std::cin >> extra;
  std::cin.ignore();

  Item* newItem = library.createItem(type, title, author, year, extra);
  if (newItem) {
    std::cout << type << " was created succesfully!\n\n";
    newItem->displayInfo();
  } else {
    std::cout << "Failed to create item. Returning to menu.\n";
    return;
  }
}

void registerUser(Library& library) {
  std::string name;
  std::cout << "Enter the name of library user: ";
  std::cin.ignore();
  std::getline(std::cin, name);
  LibraryUser* newUser = library.createUser(name);
  if (newUser) {
    std::cout << name << "was created successfully!\n\n";
  } else {
    std::cout << "Failed to create user. Returning to menu.\n\n";
    return;
  }
}

void listAllItems(const Library& library) {
  std::cout << "\n=== List of ALL items ===\n";
  library.listItems();
}

void listAvailableItems(const Library& library) {
  std::cout << "\n=== List of available items ===\n";
  library.listAvailableItems();
}

void listUnavailableItems(const Library& library) {
  std::cout << "\n=== List of unavailable items ===\n";
  library.listBorrowedItems();
}

void borrowItem(Library& library) {
  int userID, isbn;

  std::cout << "Enter user ID of borrower: ";
  std::cin >> userID;
  LibraryUser* user = library.getUserById(userID);
  if (!user) {
    std::cout << "User not found.\n";
    return;
  }

  std::cout << "Enter item ISBN to borrow: ";
  std::cin >> isbn;
  std::cin.ignore();

  Item* item = library.getItemByIsbn(isbn);
  if (!item) {
    std::cout << "Item not found.\n";
    return;
  }
  if (item->isBorrowed()) {
    std::cout << item->getTitle()
              << " was already borrowed by: " << item->getBorrower() << ".\n";
    return;
  }
  user->borrow(item);
  std::cout << item->getTitle()
            << " was borrowed by successfully by: " << user->getName() << ".\n";
}

void returnItem(Library& library) {
  int userID, isbn;
  std::cout << "Enter user ID of borrower: ";
  std::cin >> userID;
  std::cout << "Enter item ISBN to borrow: ";
  std::cin >> isbn;
  std::cin.ignore();
  LibraryUser* user = library.getUserById(userID);
  Item* item = library.getItemByIsbn(isbn);
  if (item && user) {
    user->returnItem(item);
    std::cout << item->getTitle() << " was returned to the library.\n";
  } else {
    std::cout << "Invalid ISBN or User ID.\n";
  }
}

void listAllUsers(Library& library) {
  std::cout << "\n=== List of All Users ===\n";
  library.listUsers();
}

void listUsersWithBorrowedItems(Library& library) {
  std::cout << "\n=== Users with Borrowed Items ===\n";
  const auto& users = library.getUsers();
  for (const auto& user : users) {
    if (user->getBorrowedItems().size() > 0) {
      user->listBorrowedItems();
      std::cout << divider;
    }
  }
}

void saveAndExit(Library& library) {
  library.saveData("library_data.json", library);
  std::cout << "Data saved successfully.\n";
}

int main() {
  Library library;
  library.loadData("library_data.json", library);

  while (true) {
    int choice = displayMenu();
    switch (choice) {
      case 1:
        createNewItem(library);
        break;
      case 2:
        registerUser(library);
        break;
      case 3:
        library.listItems();
        break;
      case 4:
        library.listAvailableItems();
        break;
      case 5:
        library.listBorrowedItems();
        break;
      case 6:
        borrowItem(library);
        break;
      case 7:
        returnItem(library);
        break;
      case 8:
        listAllUsers(library);
        break;
      case 9:
        listUsersWithBorrowedItems(library);
        break;
      case 10:
        saveAndExit(library);
        return 0;
      default:
        std::cout << "Invalid option. Please try again.\n";
        break;
    }
  }
  return 0;
}