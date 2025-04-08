#include "./parse_tree.h"
#include "./tree_node.h"
#include <map>


int main() {
    std::map<std::string, int> symTab;
    std::map<std::string, std::string> strTab;
    std::map<std::string, TreeNode*> nodeTab;

    // Example: Assign a string literal to a variable
    StringAssignment* stringAssign = new StringAssignment("var1", new StringConstant("A"));
    stringAssign->evaluateStatement(symTab, strTab);
    std::cout << "var1: " << strTab[stringAssign->ID()] << std::endl;

    // Example: Concatenate a string literal with an integer
    StringAssignment* concatenatedAssign = new StringAssignment("var2", new StringIntConcatenation(new StringConstant("A"), new IntConstant(1), true));
    concatenatedAssign->evaluateStatement(symTab, strTab);
    std::cout << "var2: " << strTab[concatenatedAssign->ID()] << std::endl;

    // Example: Assign an integer to a variable
    IntAssignment* intAssign = new IntAssignment("weight", new IntConstant(10));
    intAssign->evaluateStatement(symTab, strTab);
    std::cout << "weight: " << symTab[intAssign->ID()] << std::endl;

    // Example: Build a node using values from the symbol and string table
    buildNode* node = new buildNode(strTab[stringAssign->ID()], symTab[intAssign->ID()], strTab[concatenatedAssign->ID()]);
    node->evaluateStatement(symTab, strTab, nodeTab);

    nodeTab[node->ID()]->print();

    return 0;
}
