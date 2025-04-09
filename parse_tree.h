#ifndef PARSE_TREE_H
#define PARSE_TREE_H

#include <map>
#include <string>
#include <iostream>
#include <stdexcept>
#include "./tree_node.h"

using namespace std;

// Base class for integer expressions
// This serves as an abstract class for all integer-based expressions
class IntegerExpression {
    public:
        virtual ~IntegerExpression() = default;
        // Pure virtual function to evaluate the expression
        // Takes symbol tables for integers and strings as input
        virtual int evaluateExpression(std::map<std::string, int>& symTab, std::map<std::string, std::string>& strTab) = 0;
};

// Represents a constant integer value
// This class holds a single integer value and always evaluates to it
class IntConstant : public IntegerExpression {
    public:
        // Constructor to initialize the constant value
        explicit IntConstant(int val) : savedVal(val) {}

        // Evaluates the constant expression by returning the saved value
        int evaluateExpression(std::map<std::string, int>& symTab, std::map<std::string, std::string>& strTab) override {
            return savedVal;
        }

    private:
        int savedVal; // The constant integer value
};

// Base class for binary integer expressions
// This serves as a base for operations involving two integer expressions
class BinaryExpression : public IntegerExpression {
    public:
        // Constructor to initialize the left and right operands
        BinaryExpression(IntegerExpression* left, IntegerExpression* right)
            : left(left), right(right) {}

    protected:
        IntegerExpression* left;  // Left operand of the binary expression
        IntegerExpression* right; // Right operand of the binary expression
};

// Represents addition of two integer expressions
// This class evaluates the sum of two integer expressions
class PlusExpr : public BinaryExpression {
    public:
        // Inherits the constructor from BinaryExpression
        using BinaryExpression::BinaryExpression;

        // Evaluates the addition of the left and right expressions
        int evaluateExpression(std::map<std::string, int>& symTab, std::map<std::string, std::string>& strTab) override {
            return left->evaluateExpression(symTab, strTab) + right->evaluateExpression(symTab, strTab);
        }
};

// Base class for string expressions
// This serves as an abstract class for all string-based expressions
class StringExpression {
    public:
        virtual ~StringExpression() = default;
        // Pure virtual function to evaluate the expression
        // Takes symbol tables for integers and strings as input
        virtual string evaluateExpression(std::map<std::string, int>& symTab, std::map<std::string, std::string>& strTab) = 0;
};

// Represents a constant string value
// This class holds a single string value and always evaluates to it
class StringConstant : public StringExpression {
    public:
        // Constructor to initialize the constant string value
        explicit StringConstant(string val) : savedVal(val) {}

        // Evaluates the constant expression by returning the saved string value
        string evaluateExpression(std::map<std::string, int>& symTab, std::map<std::string, std::string>& strTab) override {
            return savedVal;
        }

    private:
        string savedVal; // The constant string value
};

// Represents concatenation of a string expression and an integer expression
// Allows concatenation in either order (string first or integer first)
class StringIntConcatenation : public StringExpression {
    public:
        // Constructor to initialize the string and integer expressions and the order of concatenation
        StringIntConcatenation(StringExpression* strExpr, IntegerExpression* intExpr, bool isStrFirst)
            : strExpr(strExpr), intExpr(intExpr), isStrFirst(isStrFirst) {}

        ~StringIntConcatenation() = default;

        // Evaluates the concatenation of the string and integer expressions
        string evaluateExpression(std::map<std::string, int>& symTab, std::map<std::string, std::string>& strTab) override {
            string strValue = strExpr->evaluateExpression(symTab, strTab);
            int intValue = intExpr->evaluateExpression(symTab, strTab);
            if (isStrFirst) {
                return strValue + std::to_string(intValue);
            } else {
                return std::to_string(intValue) + strValue;
            }
        }

    private:
        StringExpression* strExpr;  // The string expression
        IntegerExpression* intExpr; // The integer expression
        bool isStrFirst;            // Determines the order of concatenation
};

// Base class for statements
// This serves as an abstract class for all types of statements
class Statement {
    public:
        virtual ~Statement() = default;
        // Pure virtual function to evaluate the statement
        // Takes symbol tables for integers and strings as input
        virtual void evaluateStatement(std::map<std::string, int>& symTab, std::map<std::string, std::string>& strTab) = 0;
};

// Represents a compound statement consisting of multiple statements
// Allows sequential execution of multiple statements
class CompoundStatement : public Statement {
    public:
        // Constructor to initialize the first statement and the rest of the compound statements
        CompoundStatement(Statement* first, CompoundStatement* rest)
            : firstStatement(first), restStatements(rest) {}

        // Evaluates the compound statement by executing each statement in sequence
        void evaluateStatement(std::map<std::string, int>& symTab, std::map<std::string, std::string>& strTab) override {
            if (firstStatement != nullptr) {
                firstStatement->evaluateStatement(symTab, strTab);
            }
            if (restStatements != nullptr) {
                restStatements->evaluateStatement(symTab, strTab);
            }
        }

    private:
        Statement* firstStatement;         // The first statement in the compound
        CompoundStatement* restStatements; // The rest of the compound statements
};

// Represents an assignment between a string variable and a string expression
// Assigns the evaluated value of the string expression to the variable
class StringAssignment : public Statement {
    public:
        // Constructor to initialize the variable name and the string expression
        StringAssignment(const string& variable_name, StringExpression* constant)
            : variable_name(variable_name), constant(constant) {}

        ~StringAssignment() override = default;

        // Evaluates the assignment by updating the string symbol table
        void evaluateStatement(std::map<std::string, int>& symTab, std::map<std::string, std::string>& strTab) override {
            strTab[variable_name] = constant->evaluateExpression(symTab, strTab);
        } 

        // Returns the variable name
        string ID() {
            return variable_name;
        }

    private:
        string variable_name; // The variable to assign to
        StringExpression* constant; // The string expression to assign
};

// Represents an assignment between an integer variable and an integer constant
// Assigns the constant value to the variable
class IntAssignment : public Statement {
    public:
        // Constructor to initialize the variable name and the integer constant
        IntAssignment(const string& variable_name, IntConstant* constant)
            : variable_name(variable_name), constant(constant) {}

        ~IntAssignment() override = default;

        // Evaluates the assignment by updating the integer symbol table
        void evaluateStatement(std::map<std::string, int>& symTab, std::map<std::string, std::string>& strTab) override {
            symTab[variable_name] = constant->evaluateExpression(symTab, strTab);
        }

        // Returns the variable name
        string ID() {
            return variable_name;
        }

    private:
        string variable_name; // The variable to assign to
        IntConstant* constant; // The constant value to assign
};

// Represents the creation of a tree node
// This class is used to build a tree node with a name, weight, and parent
class BuildNode {
    public:
        // Constructor to initialize the node's name, weight, and parent
        BuildNode(const string& name, int weight, const string& parent)
            : name(name), weight(weight), parent(parent) {}

        // Evaluates the node creation by printing its details and adding it to the node table
        void evaluateStatement(std::map<std::string, int>& symTab, std::map<std::string, std::string>& strTab, std::map<std::string, TreeNode*>& nodeTab) {
            cout << "Name: " << name << ", Weight: " << weight << ", Parent: " << parent << endl;
            if(parent == ""){
            nodeTab[name] = new TreeNode(name, weight, nullptr);
            }else{
            if (!parent.empty() && nodeTab.find(parent) != nodeTab.end()) {
                nodeTab[name] = new TreeNode(name, weight, nodeTab[parent]);
                nodeTab[parent]->addChild(new TreeNode(name, weight, nodeTab[parent]));
            }else{
                throw std::runtime_error("Parent node '" + parent + "' not found in the node table.");
            }   
            }
        }
        
        // Returns the node's name
        string ID() {
            return name;
        }

    private:
        string name;   // The name of the node
        int weight;    // The weight of the node
        string parent; // The parent of the node
};


class Print {
    public:
        Print(){};

        void evaluate(std::map<std::string, TreeNode*>& nodeTab, BuildNode* rootnode){
            nodeTab[rootnode->ID()]->print();
            cout << std::endl;
        }
};

#endif
