/*Created by Kavanaugh Frank and Alec Martell for Project 2*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

#ifndef TREE_NODE_H
#define TREE_NODE_H

class TreeNode {
    public:
        TreeNode(string name, int weight, TreeNode* parent = nullptr) {
            this->name = name;
            this->weight = weight;
            this->parent = parent;
        }

        void addChild(TreeNode* child) {
            childList.push_back(child);
        }

        void print() {
            cout << name;
            if(childList.size() > 0){
                cout << " [";
                for (int i = 0; i < childList.size(); i++) {
                    childList[i]->print();
                    if (i < childList.size() - 1) {
                        cout << ", ";
                    }
                }
                cout << "]";
            }
        }

    private:
        string name;
        int weight;
        TreeNode* parent;
        vector<TreeNode*> childList;
};

#endif