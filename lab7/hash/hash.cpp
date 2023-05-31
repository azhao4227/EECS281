// Testing file provided for EECS 281 Lab 7

#include "hashtable.h"
#include <string>
#include <iostream>

int main() {

    // VERY BASIC EXAMPLE (will likely not compile with default/empty hashtable.h file)
    HashTable<std::string, int> midterm;
    std::cout << midterm.insert("sam", 50) << " ";
    std::cout << midterm.insert("fee", 100) << " ";
    std::cout << midterm.insert("milo", 95) << " ";
    std::cout << midterm.insert("gabe", 88) << " \n";
    midterm["gabe"] = 2;
    midterm["sabe"] = 5;
    std::cout << midterm["sam"] << " ";
    std::cout << midterm["fee"] << " ";
    std::cout << midterm["milo"] << " ";
    std::cout << midterm["sabe"] << " ";
    std::cout << midterm["gabe"] << " \n";
    std::cout << midterm.erase("kam") << " ";
    std::cout << midterm["sam"] << "\n";
    // ADD MORE TESTS OF YOUR OWN

    std::cout << midterm.insert("ram", 50) << " ";
    std::cout << midterm.insert("ree", 100) << " ";
    std::cout << midterm.insert("rilo", 95) << " ";
    std::cout << midterm.insert("rabe", 88) << " ";
    std::cout << midterm.insert("sar", 50) << " ";
    std::cout << midterm.insert("fer", 100) << " ";
    std::cout << midterm.insert("milo", 55) << " ";
    std::cout << midterm["milo"] << " ";
    std::cout << midterm.insert("gabe", 88) << " ";
    std::cout << midterm.insert("sarm", 50) << " ";
    std::cout << midterm.insert("feer", 100) << " ";
    std::cout << midterm.insert("milor", 95) << " ";
    std::cout << midterm.insert("gaber", 88) << " ";
    std::cout << midterm.insert("ferm", 100) << " ";
    std::cout << midterm.insert("milmo", 95) << " ";
    std::cout << midterm.insert("gabrm", 88) << " ";
    std::cout << midterm.insert("sarmm", 50) << " ";
    std::cout << midterm.insert("feerm", 200) << " ";
    std::cout << midterm.insert("milomr", 95) << " ";
    std::cout << midterm.insert("ferm", 100) << " ";
    std::cout << midterm.insert("milom", 95) << " ";
    std::cout << midterm.insert("gabrm", 88) << " ";
    std::cout << midterm.insert("sarmm", 50) << " ";
    std::cout << midterm.insert("feerm", 100) << " ";
    std::cout << midterm.erase("feerm") << "<-erase ";
    std::cout << midterm.erase("feerms") << "<-erase ";
    std::cout << midterm.erase("feerm") << "<-erase " << std::endl;
    std::cout << midterm.insert("milorm", 95) << " insert " << std::endl;
    std::cout << midterm["ferm"] << "\n";
    std::cout << midterm["feerm"] << "\n";
    std::cout << midterm.erase("milorm") << "<-erase \n";
    std::cout << midterm["feerm"] << "\n";
    std::cout << midterm["milorm"] << "\n";
    std::cout << midterm["gaber"] << " \n";

    HashTable<std::string, std::string> midterm2;
    std::cout << midterm2.insert("sam", "20") << " ";
    std::cout << midterm2.insert("fee", "20") << " ";
    std::cout << midterm2.insert("milo", "20") << " ";
    std::cout << midterm2.insert("gabe", "20") << " \n";
    midterm2["gabe"] = "500";
    midterm2["sabe"] = "25";
    std::cout << midterm2["sam"] << " ";
    std::cout << midterm2["fee"] << " ";
    std::cout << midterm2["milo"] << " ";
    std::cout << midterm2["sabe"] << " ";
    std::cout << midterm2["gabe"] << " \n";
    std::cout << midterm2.erase("sam") << " ";
    std::cout << midterm2["sam"] << " lol \n";
    std::cout << true << " " << false << std::endl;

    return 0;
}
