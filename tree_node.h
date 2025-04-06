#include <iostream>
#include <vector>
#include <string>

using namespace std;

class TreeNode{
    public:
        TreeNode(string name, int weight){
            this->name = name;
            this->weight = weight;
            this->parent = parent;
        }

        void addChild(TreeNode* child){
            childList.push_back(child);
        }

        void print() {
            cout << name << " [";
            for (int i = 0; i < childList.size(); i++) {
                childList[i]->print();
                if (i < childList.size() - 1) {
                    cout << ", ";
                }
            }
            cout << "]";
        }

    private:
        string name;
        int weight;
        TreeNode* parent;
        vector<TreeNode*> childList;
};