#include "./parse_tree.h"
#include "./tree_node.h"
#include <iostream>
#include <map>


int main() {
    // Symbol tables for integer and string variables
    std::map<std::string, int> symTab;
    std::map<std::string, std::string> strTab;

    // Create a StringVariable named "name"
    StringVariable* nameVar = new StringVariable("name");

    // Create a StringConstant with the value "root"
    StringConstant* rootConst = new StringConstant("root");

    // strTab["name"] = "root";
    // Create a StringAssignment to assign "root" to "name"
    StringAssignment* assign = new StringAssignment(nameVar->ID(), rootConst);

    // Evaluate the assignment
    assign->evaluateStatement(symTab, strTab);

    // Output the value of "name" from the string symbol table
    std::cout << "The value of 'name' is: " << strTab["name"] << std::endl;

    // Clean up dynamically allocated memory
    delete nameVar;
    delete rootConst;
    delete assign;

    return 0;
}
