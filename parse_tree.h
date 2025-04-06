//****************************************************************
// File: parse_tree.h
// Author: David W. Juedes
//
// Copyright 2007, All rights reserved.
// Purpose: This .h file includes a hierarchy
// of classes that define possible
// instructions in the pfig language
//
// In general, there are statements,
// boolean expressions, and integer_expressions
//
//******************************************************************

#ifndef PARSE_TREE_H
#define PARSE_TREE_H

#include <map>
#include <string>
#include <iostream>

using namespace std;

class IntegerExpression {
    public:
        virtual ~IntegerExpression() = default;
        // Pure virtual function to evaluate the expression
        virtual int evaluateExpression(std::map<std::string, int>& symTab) = 0;
};

class IntConstant : public IntegerExpression {
    public:
        explicit IntConstant(int val) : savedVal(val) {}
        // Returns the constant value
        int evaluateExpression(std::map<std::string, int>& symTab) override {
            return savedVal;
        }

    private:
        int savedVal; // The constant value
};

class StringExpression {
    public:
        virtual ~StringExpression() = default;
        // Pure virtual function to evaluate the expression
        virtual string evaluateExpression(std::map<std::string, string>& symTab) = 0;
};

class StringConstant : public StringExpression {
    public:
        explicit StringConstant(string val) : savedVal(val) {}
        // Returns the constant value
        string evaluateExpression(std::map<std::string, string>& symTab) override {
            return savedVal;
    }

    private:
        string savedVal; // The constant value
};

class StringVariable : public StringExpression {
    public:
        explicit StringVariable(const std::string& inVal) : savedVal(inVal) {}
        ~StringVariable() override = default;
        // Looks up the variable in the symbol table and returns its value
        string evaluateExpression(std::map<std::string, string>& symTab) override {
            auto it = symTab.find(savedVal);
            if (it != symTab.end()) {
                return it->second;
            } else {
                // Error handling: variable not found
                throw std::runtime_error("Variable not found: " + savedVal);
            }
        }
        string ID(){
            return savedVal;
        }
    private:
        std::string savedVal; // The variable name
};

// Represents a variable
class Variable : public IntegerExpression {
    public:
        explicit Variable(const std::string& inVal) : savedVal(inVal) {}
        // Looks up the variable in the symbol table and returns its value
        int evaluateExpression(std::map<std::string, int>& symTab) override {
            auto it = symTab.find(savedVal);
            if (it != symTab.end()) {
                return it->second;
            } else {
                // Error handling: variable not found
                throw std::runtime_error("Variable not found: " + savedVal);
            }
        }
    private:
        std::string savedVal; // The variable name
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
        int evaluateExpression(std::map<std::string, int>& symTab) override {
            return left->evaluateExpression(symTab) + right->evaluateExpression(symTab);
        }
};
// Base class for statements
class Statement {
    public:
        virtual ~Statement() = default;
        // Pure virtual function to evaluate the statement
        virtual void evaluateStatement(std::map<std::string, int>& symTab, std::map<std::string, std::string>& strTab) = 0;
};

// Represents an assignment between a StringVariable and a StringConstant
class StringAssignment : public Statement {
    public:
        StringAssignment(const string& variable_name, StringConstant* constant)
            : variable_name(variable_name), constant(constant) {}

        ~StringAssignment() override = default;

        void evaluateStatement(std::map<std::string, int>& symTab, std::map<std::string, std::string>& strTab) override {
            strTab[variable_name] = constant->evaluateExpression(strTab);
        }

    private:
        string variable_name; // The variable to assign to
        StringConstant* constant; // The constant value to assign
};

#endif // PARSE_TREE_H