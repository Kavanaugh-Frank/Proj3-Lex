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

    // Create nodes in foreach loop
    std::vector<build_node*> commands = {
        new build_node(
            new string_plus_expr( new str_literal("Node_"), new var_str_expr("x")),
            new int_literal(5),
            new str_literal("Child0")
        )
    };
    
    std::vector<str_literal*> values = {
        new str_literal("s1"),
        new str_literal("s2"),
        new str_literal("s3")
    };
    
    for_each_loop loop1(
        new str_literal("x"),  // Loop variable
        values,                // ["s1", "s2", "s3"]
        commands               // Body commands
    );
        
    loop1.execute(nodeTab);

    // nodeTab["Root"]->print();
    print* print_obj = new print( new str_literal("Root") );

    print_obj->execute(nodeTab);

    // Cleanup
    for (auto& entry : nodeTab) delete entry.second;
}