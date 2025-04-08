#include "./parse_tree.h"
#include "./tree_node.h"
#include <map>


int main() {
    std::map<std::string, int> symTab;
    std::map<std::string, std::string> strTab;
    std::map<std::string, TreeNode*> nodeTab;

    // Example: Assign a string literal to a variable
    // Represents : name = "A"
    StringAssignment* stringAssign = new StringAssignment("name", new StringConstant("A"));
    stringAssign->evaluateStatement(symTab, strTab);
    std::cout << "var1: " << strTab[stringAssign->ID()] << std::endl;

    // Example: Concatenate a string literal with an integer
    // Represents : ischildof = "A" + 1
    StringAssignment* concatenatedAssign = new StringAssignment("ischildof", new StringIntConcatenation(new StringConstant("A"), new IntConstant(1), true));
    concatenatedAssign->evaluateStatement(symTab, strTab);
    std::cout << "var2: " << strTab[concatenatedAssign->ID()] << std::endl;

    // Example: Assign an integer to a variable
    // Represents : weight = 10
    IntAssignment* intAssign = new IntAssignment("weight", new IntConstant(10));
    intAssign->evaluateStatement(symTab, strTab);
    std::cout << "weight: " << symTab[intAssign->ID()] << std::endl;

    // Example: Build a node using values from the symbol and string table
    // This uses the class to build a new node with the parent of A1
    // There is no functionality to add this node to the parent node of A1 just yet
    buildNode* node = new buildNode(strTab[stringAssign->ID()], symTab[intAssign->ID()], strTab[concatenatedAssign->ID()]);
    node->evaluateStatement(symTab, strTab, nodeTab);

    // using the nodeTab and the ID method we can find the node and call its print function
    // which results in: A []
    nodeTab[node->ID()]->print();

    return 0;
}
