#include "./parse_tree.h"
#include "./tree_node.h"
#include <map>


#include "parse_tree.h"
#include <iostream>

int main() {
    std::map<std::string, TreeNode*> nodeTab;

    // 1. Create root node
    build_node root(
        new str_literal("Root"),
        new int_literal(0),
        new str_literal("") // No parent
    );
    root.execute(nodeTab, {}, {}); // Execute to add root

    // 2. Create children in loop (0-2)
    std::vector<build_node*> loop_commands;
    loop_commands.push_back(new build_node(
        new string_plus_expr(new str_literal("Child"), new var_str_expr("i")), // Name: Child0, Child1, etc.
        new int_literal(1), // Weight
        new str_literal("Root") // Parent
    ));

    for_loop loop(
        new str_literal("i"), // Loop variable
        new int_literal(0),   // Start
        new int_literal(2),   // End
        loop_commands
    );
    loop.execute(nodeTab); // Creates Child0, Child1, Child2

    nodeTab["Root"]->print();

    // Cleanup
    for (auto& entry : nodeTab) delete entry.second;
}