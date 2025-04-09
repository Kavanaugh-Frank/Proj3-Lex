#include "./parse_tree.h"
#include "./tree_node.h"
#include <map>


int main() {
    std::map<std::string, int> symTab;
    std::map<std::string, std::string> strTab;
    std::map<std::string, TreeNode*> nodeTab;

    StringAssignment* root_stringAssign = new StringAssignment("name", new StringConstant("root"));
    root_stringAssign->evaluateStatement(symTab, strTab);
    std::cout << "var1: " << strTab[root_stringAssign->ID()] << std::endl;

    IntAssignment* root_intAssign = new IntAssignment("weight", new IntConstant(20));
    root_intAssign->evaluateStatement(symTab, strTab);
    std::cout << "weight: " << symTab[root_intAssign->ID()] << std::endl;

    BuildNode* root_node = new BuildNode(strTab[root_stringAssign->ID()], symTab[root_intAssign->ID()], "");
    root_node->evaluateStatement(symTab, strTab, nodeTab);

    
    // Example: Assign a string literal to a variable
    // Represents : name = "A"
    StringAssignment* stringAssign = new StringAssignment("name", new StringConstant("A"));
    stringAssign->evaluateStatement(symTab, strTab);
    std::cout << "var1: " << strTab[stringAssign->ID()] << std::endl;

    // Example: Concatenate a string literal with an integer
    // Represents : ischildof = "A" + 1
    StringAssignment* concatenatedAssign = new StringAssignment("ischildof", new StringConstant("root"));
    concatenatedAssign->evaluateStatement(symTab, strTab);
    std::cout << "var2: " << strTab[concatenatedAssign->ID()] << std::endl;

    // Example: Assign an integer to a variable
    // Represents : weight = 10
    IntAssignment* intAssign = new IntAssignment("weight", new IntConstant(10));
    intAssign->evaluateStatement(symTab, strTab);
    std::cout << "weight: " << symTab[intAssign->ID()] << std::endl;

    BuildNode* node = new BuildNode(strTab[stringAssign->ID()], symTab[intAssign->ID()], strTab[concatenatedAssign->ID()]);
    node->evaluateStatement(symTab, strTab, nodeTab);



    Print* print = new Print();
    print->evaluate(nodeTab, root_node);




    // // Example: Assign a string literal to a variable
    // // Represents : name = "A"
    // StringAssignment* stringAssign = new StringAssignment("name", new StringConstant("A"));
    // stringAssign->evaluateStatement(symTab, strTab);
    // std::cout << "var1: " << strTab[stringAssign->ID()] << std::endl;

    // // Example: Concatenate a string literal with an integer
    // // Represents : ischildof = "A" + 1
    // StringAssignment* concatenatedAssign = new StringAssignment("ischildof", new StringIntConcatenation(new StringConstant("A"), new IntConstant(1), true));
    // concatenatedAssign->evaluateStatement(symTab, strTab);
    // std::cout << "var2: " << strTab[concatenatedAssign->ID()] << std::endl;

    // // Example: Assign an integer to a variable
    // // Represents : weight = 10
    // IntAssignment* intAssign = new IntAssignment("weight", new IntConstant(10));
    // intAssign->evaluateStatement(symTab, strTab);
    // std::cout << "weight: " << symTab[intAssign->ID()] << std::endl;

    // Example: Build a node using values from the symbol and string table
    // This uses the class to build a new node with the parent of A1
    // There is no functionality to add this node to the parent node of A1 just yet

    // using the nodeTab and the ID method we can find the node and call its print function
    // which results in: A []
    // nodeTab[node->ID()]->print();

    // Clean up allocated memory
    delete stringAssign;
    delete concatenatedAssign;
    delete intAssign;
    delete node;

    // Clean up nodes in nodeTab
    for (auto& pair : nodeTab) {
        delete pair.second;
    }

    return 0;
}
