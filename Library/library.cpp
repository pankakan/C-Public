#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "json.hpp"


using json = nlohmann::json;

std::string divider = "------------------------";

class LibraryUser;
// Parent class Item
class Item {
 protected:
  std::string title;
  std::string author;
  int year;
  int isbn;
  std::string dueDate;
  LibraryUser* borrower = nullptr;
  static int nextISBN;

 public:
  // Constructor for loaded item with isbn
  Item(const std::string& title, const std::string& author, int year,
       int isbn) {
    this->title = title;
    this->author = author;
    this->year = year;
    this->isbn = isbn;
    if (isbn >= nextISBN) {
      nextISBN = isbn + 1;
    }
  }
  // Constructror for new item without isbn
  Item(const std::string& title, const std::string& author, int year) {
    this->title = title;
    this->author = author;
    this->year = year;
    this->isbn = nextISBN++;
  }

  // Abstract methods
  virtual void displayInfo() const = 0;
  virtual int getPagesOrIssue() const = 0;

  // Get/Setters
  bool isBorrowed() const { return this->borrower != nullptr; }
  std::string getDueDate() const { return this->dueDate; }
  void setDueDate(const std::string& date) { this->dueDate = date; }
  void setBorrower(LibraryUser* user) { this->borrower = user; }
  LibraryUser* getBorrower() const { return this->borrower; }
  std::string getTitle() const { return this->title; }
  std::string getAuthor() const { return this->author; }
  int getYear() const { return this->year; }
  int getISBN() const { return this->isbn; }

  // Flags item as borrowed and sets a duedate 30days from today.
  void setBorrowed(LibraryUser* user) {
    if (!user) {
      std::cerr << "Error: user don not exist.\n";
      return;
    }
    this->borrower = user;

    // Set due date 30 days from now
    auto now = std::chrono::system_clock::now();
    auto dueTime = now + std::chrono::hours(24 * 30);
    std::time_t dueTime_t = std::chrono::system_clock::to_time_t(dueTime);
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&dueTime_t), "%Y-%m-%d");
    this->dueDate = oss.str();
  }

  // Clear borrowed-flags
  void clearBorrowed() {
    this->borrower = nullptr;
    this->dueDate.clear();
  }

  int calculateFines(const std::string& currentDate) const {
    // Check if duedate is empty or not overdue and return 0 fine.
    if (this->dueDate.empty() || currentDate <= this->dueDate) return 0;

    // Create time-objects for due and now
    std::tm due = {};
    std::tm now = {};
    // Convert dueDate and currentDate-strings to tm-objects with correct
    // format.
    std::istringstream(this->dueDate) >> std::get_time(&due, "%Y-%m-%d");
    std::istringstream(currentDate) >> std::get_time(&now, "%Y-%m-%d");

    // Using mktime to convert tm-object to time_t then cast to
    auto dueTime = std::chrono::system_clock::from_time_t(std::mktime(&due));
    auto nowTime = std::chrono::system_clock::from_time_t(std::mktime(&now));

    // Calculate differnce in seconds and calculate days
    auto overdueDays =
        std::chrono::duration_cast<std::chrono::hours>(nowTime - dueTime)
            .count() /
        24;
    // Return the overdueDays * 5kr for each day its overdue.
    return overdueDays * 5;
  }
};
// Subclass Book
class Book : public Item {
 private:
  int pages;

 public:
  // Constructor for new book
  Book(const std::string& title, const std::string& author, int year, int pages)
      : Item(title, author, year) {
    this->pages = pages;
  }
  // Constructor from loaded book
  Book(const std::string& title, const std::string& author, int year, int isbn,
       int pages)
      : Item(title, author, year, isbn) {
    this->pages = pages;
  }

  void displayInfo() const override {
    std::cout << "Book (ISBN: " << this->getISBN() << "): " << this->getTitle()
              << " by " << this->getAuthor() << "\nYear: " << this->getYear()
              << "\nPages: " << this->pages << std::endl;
  }
  int getPagesOrIssue() const override { return this->pages; }
};

// Subclass Magazine
class Magazine : public Item {
 private:
  int issue;

 public:
  // Constructor for new magazine
  Magazine(const std::string& title, const std::string& author, int year,
           int issue)
      : Item(title, author, year) {
    this->issue = issue;
  }
  // Constructor from loaded magazine
  Magazine(const std::string& title, const std::string& author, int year,
           int isbn, int issue)
      : Item(title, author, year, isbn) {
    this->issue = issue;
  }

  void displayInfo() const override {
    std::cout << "Magazine: (ISBN:  " << this->getISBN()
              << "): " << this->getTitle() << " by " << this->getAuthor()
              << "\nYear: " << this->getYear() << "\nPages: " << this->issue
              << std::endl;
  }
  int getPagesOrIssue() const override { return this->issue; }
};

// LibraryUser class
class LibraryUser {
 private:
  int id;
  std::string name;
  std::vector<Item*> borrowedItems;
  static int nextId;

 public:
  // Constructor for new user
  LibraryUser(const std::string& name) {
    this->id = nextId++;
    this->name = name;
  }
  // Constructor for loaded user

  LibraryUser(const std::string& name, int id) {
    this->name = name;
    this->id = id;
  }
  // Getters
  int getId() const { return this->id; }
  std::string getName() const { return this->name; }
  bool hasBorrowedItems() const { return !this->borrowedItems.empty(); }
  const std::vector<Item*>& getBorrowedItems() const { return borrowedItems; }

  // Check if item is availble, flag item as borrowed by ID and add to users
  // list of borrowed items
  void borrow(Item* item) {
    if (item && !item->isBorrowed()) {
      this->borrowedItems.push_back(item);
      item->setBorrowed(this);
    } else {
      std::cout << "Item is not available." << std::endl;
      return;
    }
  }
  // Check if item is borrowed, remove it form list of borrowed items and clear
  // borrowed-state from Item.
  void returnItem(Item* item) {
    auto found =
        std::find(this->borrowedItems.begin(), this->borrowedItems.end(), item);
    if (found != this->borrowedItems.end()) {
      this->borrowedItems.erase(found);
      item->clearBorrowed();
    }
  }
  // Display info function
  void displayInfo() const {
    std::cout << "User ID: " << id << ", Name: " << name << std::endl;
    if (borrowedItems.empty()) {
      std::cout << "No borrowed items." << std::endl;
    } else {
      std::cout << "Borrowed items:\n";
      for (const auto& item : borrowedItems) {
        std::cout << "  - " << item->getTitle() << std::endl;
      }
    }
  }
  // Call function displayInfo for every object in borrowedItems.
  void listBorrowedItems() const {
    std::cout << "Items borrowed by " << this->name << ":" << std::endl;
    if (borrowedItems.empty()) {
      std::cout << "No items borrowed." << std::endl;
      return;
    }
    for (const auto& item : this->borrowedItems) {
      item->displayInfo();
      std::cout << divider << std::endl;
    }
  }
};

// Library class
class Library {
 private:
  std::vector<Item*> items;
  std::vector<LibraryUser*> users;

 public:
  const std::vector<Item*>& getItems() const { return items; }
  const std::vector<LibraryUser*>& getUsers() const { return users; }

  // Add item
  Item* createItem(const std::string& type, const std::string& title,
                   const std::string& author, int year, int extra) {
    Item* newItem = nullptr;

    if (type == "Book") {
      newItem = new Book(title, author, year, extra);
    } else if (type == "Magazine") {
      newItem = new Magazine(title, author, year, extra);
    }
    if (newItem) {
      items.push_back(newItem);
    } else {
      std::cerr << "Could not create item.\n";
      return nullptr;
    }
    return newItem;
  }

  // Register user
  LibraryUser* createUser(const std::string& name) {
    LibraryUser* newUser = new LibraryUser(name);
    users.push_back(newUser);
    return newUser;
  }
  // Loop thouh vector of items and call displayInfo
  void listItems() const {
    for (const auto& item : this->items) {
      item->displayInfo();
      if (item->isBorrowed()) {
        std::cout << "Status: Unavailable.\n";
      } else {
        std::cout << "Status: Available.\n";
      }
      std::cout << divider << std::endl;
    }
  }

  // Returns a pointer to a user based on its ID
  LibraryUser* getUserById(int id) const {
    for (auto* user : this->users) {
      if (user->getId() == id) {
        return user;
      }
    }
    return nullptr;
  }
  // Return a pointter to a ITEM based on ISBN
  Item* getItemByIsbn(int isbn) const {
    for (const auto& item : items) {
      if (item->getISBN() == isbn) {
        return item;
      }
    }
    return nullptr;
  }
  // List all items in library that are flagged as borrowed.
  void listBorrowedItems() const {
    std::cout << "Borrowed items:\n";
    for (const auto& item : this->items) {
      if (item->isBorrowed()) {
        item->displayInfo();
        LibraryUser* borrower = item->getBorrower();
        std::cout << "\nBorrowed by ID: " << borrower->getId();
        std::cout << "\nDue Date: " << item->getDueDate() << std::endl;
      }
    }
  }
  // List all items in library that are not flagged as borrowed.
  void listAvailableItems() const {
    int counter = 0;
    for (const auto& item : items) {
      if (!item->isBorrowed()) {
        item->displayInfo();
        std::cout << divider << std::endl;
        counter++;
      }
    }
    if (counter == 0) std::cout << "No items available.\n";
  }

  // List all users and their borrowed items
  void listUsers() const {
    if (users.empty()) std::cout << "No users available.\n";
    for (const auto& user : users) {
      user->displayInfo();
      std::cout << divider << std::endl;
    }
  }

  Item* getItem(size_t index) const {
    if (index >= items.size()) {
      std::cerr << "Error: Invalid index " << index << ".\n";
      return nullptr;
    }
    return items[index];
  }

  // List all users with borrowed items
  void listActiveUsers() const {
    std::cout << "Active library Users:\n";
    for (const auto& user : this->users) {
      if (user->hasBorrowedItems()) {
        std::cout << "User Id: " << user->getId() << std::endl;
        std::cout << "Name: " << user->getName() << std::endl;
        user->listBorrowedItems();
        std::cout << divider << std::endl;
      }
    }
  }
  // Database-fucntions
  void saveData(const std::string& filename, const Library& library) {
    json data;
    // Save Items to JSON
    for (const auto& item : library.getItems()) {
      json itemJson;
      itemJson["type"] = (dynamic_cast<Book*>(item) ? "Book" : "Magazine");
      itemJson["title"] = item->getTitle();
      itemJson["author"] = item->getAuthor();
      itemJson["year"] = item->getYear();
      itemJson["isbn"] = item->getISBN();

      if (auto* book = dynamic_cast<Book*>(item)) {
        itemJson["pages"] = book->getPagesOrIssue();
      } else if (auto* magazine = dynamic_cast<Magazine*>(item)) {
        itemJson["issue"] = magazine->getPagesOrIssue();
      }

      auto borrower = item->getBorrower();
      itemJson["borrowerId"] = borrower ? borrower->getId() : -1;
      itemJson["dueDate"] = item->getDueDate();

      data["items"].push_back(itemJson);
    }
    
    // Save users to JSON
    for (const auto& user : library.getUsers()) {
      json userJson;
      userJson["id"] = user->getId();
      userJson["name"] = user->getName();
      userJson["borrowedItems"] = json::array();

      for (const auto& borrowedItem : user->getBorrowedItems()) {
        userJson["borrowedItems"].push_back(borrowedItem->getISBN());
      }
      data["users"].push_back(userJson);
    }
    std::ofstream outFile(filename, std::ios::trunc);
    if (!outFile.is_open()) {
      std::cerr << "Error opening file for saving data.\n";
      return;
    }
    outFile << data.dump(4);
    outFile.close();
  }

  void loadData(const std::string& filename, Library& library) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
      std::cerr << "Error opening file: " << filename << std::endl;
      return;
    }

    json data;
    inFile >> data;
    inFile.close();

    // Load items
    for (const auto& itemJson : data["items"]) {
      Item* newItem = nullptr;

      if (itemJson["type"] == "Book") {
        newItem =
            new Book(itemJson["title"], itemJson["author"], itemJson["year"],
                     itemJson["isbn"], itemJson["pages"]);
      } else if (itemJson["type"] == "Magazine") {
        newItem =
            new Magazine(itemJson["title"], itemJson["author"],
                         itemJson["year"], itemJson["isbn"], itemJson["issue"]);
      }
      if (newItem) items.push_back(newItem);
    }
    // Load users
    for (const auto& userJson : data["users"]) {
      LibraryUser* newUser = new LibraryUser(userJson["name"], userJson["id"]);

      for (const auto& borrowedItemIsbn : userJson["borrowedItems"]) {
        Item* borrowedItem = getItemByIsbn(borrowedItemIsbn);
        if (borrowedItem) newUser->borrow(borrowedItem);
      }
      users.push_back(newUser);
    }
    std::cout << "Library loaded successfully.\n";
  }
  
  // Deconstructor
  ~Library() {
    for (auto* item : items) delete item;
    for (auto* user : users) delete user;
  }
};
int LibraryUser::nextId = 1;
int Item::nextISBN = 1;

