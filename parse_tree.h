#ifndef PARSE_TREE_H
#define PARSE_TREE_H

#include <map>
#include <string>
#include <iostream>
#include <stdexcept>
#include "./tree_node.h"

class integer_expression {
    public:
        virtual int evaluate_expression(const std::map<std::string, int>& int_sym_tab) = 0;
};
    
class string_expression {
    public:
        virtual std::string evaluate_expression(const std::map<std::string, std::string>& str_sym_tab) = 0;
};

class int_literal : public integer_expression {
    private:
        int value;
    public:
        int_literal(int val) : value(val) {}
        int evaluate_expression(const std::map<std::string, int>&) override { return value; }
};

class str_literal : public string_expression {
    private:
        std::string value;
    public:
        str_literal(const std::string& val) : value(val) {}
        std::string evaluate_expression(const std::map<std::string, std::string>&) override { return value; }
};

class var_int_expr : public integer_expression {
    private:
        std::string var_name;
    public:
        var_int_expr(const std::string& name) : var_name(name) {}
        
        int evaluate_expression(const std::map<std::string, int>& int_sym_tab) override {
            auto it = int_sym_tab.find(var_name);
            if (it == int_sym_tab.end()) throw std::runtime_error("Undefined integer variable: " + var_name);
            return it->second;
        }
};

class var_str_expr : public string_expression {
    private:
        std::string var_name;
    public:
        var_str_expr(const std::string& name) : var_name(name) {}
        
        std::string evaluate_expression(const std::map<std::string, std::string>& str_sym_tab) override {
            auto it = str_sym_tab.find(var_name);
            if (it == str_sym_tab.end()) throw std::runtime_error("Undefined string variable: " + var_name);
            return it->second;
        }
};

class plus_expr : public integer_expression {
    private:
        integer_expression* l;
        integer_expression* r;
    public:
        plus_expr(integer_expression* left, integer_expression* right) : l(left), r(right) {}
        
        int evaluate_expression(const std::map<std::string, int>& int_sym_tab) override {
            return l->evaluate_expression(int_sym_tab) + r->evaluate_expression(int_sym_tab);
        }
};


class string_plus_expr : public string_expression {
    private:
        string_expression* l;
        string_expression* r;
    public:
        string_plus_expr(string_expression* left, string_expression* right) : l(left), r(right) {}
        
        std::string evaluate_expression(const std::map<std::string, std::string>& str_sym_tab) override {
            return l->evaluate_expression(str_sym_tab) + r->evaluate_expression(str_sym_tab);
        }
};

class build_node {
    private:
        string_expression* name;
        integer_expression* weight;
        string_expression* ischildof;

    public:
        build_node(string_expression* name, 
                integer_expression* weight, 
                string_expression* ischildof)
            : name(name), weight(weight), ischildof(ischildof) {}

        void execute(std::map<std::string, TreeNode*>& nodeTab,
                    const std::map<std::string, int>& int_sym_tab,
                    const std::map<std::string, std::string>& str_sym_tab) {
            
            std::string node_name = name->evaluate_expression(str_sym_tab);
            int node_weight = weight->evaluate_expression(int_sym_tab);
            std::string parent_name = ischildof->evaluate_expression(str_sym_tab);

            TreeNode* parent = nullptr;
            if (nodeTab.find(parent_name) != nodeTab.end()) {
                parent = nodeTab[parent_name];
            }

            TreeNode* new_node = new TreeNode(node_name, node_weight, parent);
            if (parent) parent->addChild(new_node);
            nodeTab[node_name] = new_node;
        }
};

class for_loop {
    private:
        str_literal* var_name;
        int_literal* start;
        int_literal* stop;
        std::vector<build_node*> body;
    public:

        for_loop(str_literal* var, int_literal* start, int_literal* stop, std::vector<build_node*> body)
            : var_name(var), start(start), stop(stop), body(body) {}

        void execute(std::map<std::string, TreeNode*>& nodeTab) {
            std::map<std::string, int> int_sym_tab;
            std::map<std::string, std::string> str_sym_tab;

            int start_val = start->evaluate_expression(int_sym_tab);
            int end_val = stop->evaluate_expression(int_sym_tab);

            std::string loop_var = var_name->evaluate_expression(str_sym_tab);

            for (int_sym_tab[loop_var] = start_val; int_sym_tab[loop_var] <= end_val; ++int_sym_tab[loop_var]) {
                std::string var_string = std::to_string(int_sym_tab[loop_var]); // to give the string for the name and ischildof
                str_sym_tab[loop_var] = var_string;

                for (int i = 0; i < body.size(); i++) {
                    body[i]->execute(nodeTab, int_sym_tab, str_sym_tab);
                }
            }
        }
};


class for_each_loop {
    private:
        str_literal* var_name;
        std::vector<str_literal*> string_literals;
        std::vector<build_node*> body;
    public:

        for_each_loop(str_literal* var, std::vector<str_literal*> string_literals, std::vector<build_node*> body)
            : var_name(var), string_literals(string_literals), body(body) {}

        void execute(std::map<std::string, TreeNode*>& nodeTab) {
            std::map<std::string, int> int_sym_tab;
            std::map<std::string, std::string> str_sym_tab;

            std::string loop_var = var_name->evaluate_expression(str_sym_tab);

            for(int i = 0; i < string_literals.size(); i++){
                str_sym_tab[loop_var] = string_literals[i]->evaluate_expression(str_sym_tab);

                for (int j = 0; j < body.size(); j++) {
                    body[j]->execute(nodeTab, int_sym_tab, str_sym_tab);
                }
            }
        }
};

#endif
