#include "./parse_tree.h"
#include "./tree_node.h"
#include <iostream>


int main(){
    std::map<std::string, int> symTab;
    std::map<std::string, std::string> symTabStr;

    StringVariable* name = new StringVariable("name");
    StringConstant* nameVal = new StringConstant("root");

    StringAssignment* nameAssign = new StringAssignment(name, nameVal);

    nameAssign->evaluateStatement(symTab, symTabStr);

    // Print the values in symTabStr
    for (const auto& pair : symTabStr) {
        std::cout << pair.first << " = " << pair.second << std::endl;
    }

    // Clean up dynamically allocated memory
    delete name;
    delete nameVal;
    delete nameAssign;

    return 0;
}
