#ifndef PARSE_TREE_H
#define PARSE_TREE_H

#include <map>
#include <string>
#include <iostream>
#include <stdexcept>
#include "./tree_node.h"

using namespace std;

// Base class for integer expressions
class IntegerExpression {
    public:
        virtual ~IntegerExpression() = default;
        // Pure virtual function to evaluate the expression
        virtual int evaluateExpression(std::map<std::string, int>& symTab, std::map<std::string, std::string>& strTab) = 0;
};

// Represents a constant integer value
class IntConstant : public IntegerExpression {
    public:
        explicit IntConstant(int val) : savedVal(val) {}
        int evaluateExpression(std::map<std::string, int>& symTab, std::map<std::string, std::string>& strTab) override {
            return savedVal;
        }

    private:
        int savedVal; // The constant value
};

// Base class for binary integer expressions
class BinaryExpression : public IntegerExpression {
    public:
        BinaryExpression(IntegerExpression* left, IntegerExpression* right)
            : left(left), right(right) {}

    protected:
        IntegerExpression* left;  // Left operand
        IntegerExpression* right; // Right operand
};

// Represents addition of two integer expressions
class PlusExpr : public BinaryExpression {
    public:
        using BinaryExpression::BinaryExpression;
        int evaluateExpression(std::map<std::string, int>& symTab, std::map<std::string, std::string>& strTab) override {
            return left->evaluateExpression(symTab, strTab) + right->evaluateExpression(symTab, strTab);
        }
};

// Base class for string expressions
class StringExpression {
    public:
        virtual ~StringExpression() = default;
        // Pure virtual function to evaluate the expression
        virtual string evaluateExpression(std::map<std::string, int>& symTab, std::map<std::string, std::string>& strTab) = 0;
};

// Represents a constant string value
class StringConstant : public StringExpression {
    public:
        explicit StringConstant(string val) : savedVal(val) {}
        string evaluateExpression(std::map<std::string, int>& symTab, std::map<std::string, std::string>& strTab) override {
            return savedVal;
        }

    private:
        string savedVal; // The constant value
};

class StringIntConcatenation: public StringExpression{
    public:
        StringIntConcatenation(StringExpression* strExpr, IntegerExpression* intExpr, bool isStrFirst)
            : strExpr(strExpr), intExpr(intExpr), isStrFirst(isStrFirst) {}

        ~StringIntConcatenation() = default;

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
class Statement {
    public:
        virtual ~Statement() = default;
        // Pure virtual function to evaluate the statement
        virtual void evaluateStatement(std::map<std::string, int>& symTab, std::map<std::string, std::string>& strTab) = 0;
};
// Represents a compound statement consisting of multiple statements
class CompoundStatement : public Statement {
    public:
        CompoundStatement(Statement* first, CompoundStatement* rest)
            : firstStatement(first), restStatements(rest) {}

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

// Represents an assignment between a StringVariable and a StringConstant
class StringAssignment : public Statement {
    public:
        StringAssignment(const string& variable_name, StringExpression* constant)
            : variable_name(variable_name), constant(constant) {}

        ~StringAssignment() override = default;

        void evaluateStatement(std::map<std::string, int>& symTab, std::map<std::string, std::string>& strTab) override {
            strTab[variable_name] = constant->evaluateExpression(symTab, strTab);
        } 

        string ID(){
            return variable_name;
        }

    private:
        string variable_name; // The variable to assign to
        StringExpression* constant; // The constant value to assign
};

// Represents an assignment between a Variable and an IntConstant
class IntAssignment : public Statement {
    public:
        IntAssignment(const string& variable_name, IntConstant* constant)
            : variable_name(variable_name), constant(constant) {}

        ~IntAssignment() override = default;

        void evaluateStatement(std::map<std::string, int>& symTab, std::map<std::string, std::string>& strTab) override {
            symTab[variable_name] = constant->evaluateExpression(symTab, strTab);
        }

        string ID(){
            return variable_name;
        }

    private:
        string variable_name; // The variable to assign to
        IntConstant* constant; // The constant value to assign
};

class buildNode {
    public:
        buildNode(const string& name, int weight, const string& parent)
            : name(name), weight(weight), parent(parent) {}

        void evaluateStatement(std::map<std::string, int>& symTab, std::map<std::string, std::string>& strTab, std::map<std::string, TreeNode*>& nodeTab) {
            cout << "Name: " << name << ", Weight: " << weight << ", Parent: " << parent << endl;
            nodeTab[name] = new TreeNode(name, weight, nullptr);
        }
        
        string ID(){
            return name;
        }

    private:
        string name;
        int weight;
        string parent;
};

#endif
