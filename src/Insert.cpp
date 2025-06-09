#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

struct QuadtreeNode {
    int id;
    vector<QuadtreeNode*> children;
    QuadtreeNode* parent;

    QuadtreeNode(int id) : id(id), parent(nullptr) {}
};

unordered_set<QuadtreeNode*> deletedNodes;




void printRemainingNodes(QuadtreeNode* node) {
    if (!node || deletedNodes.count(node)) return;
   
    cout << "Node " << node->id <<endl;

    for (auto child : node->children) {
        printRemainingNodes(child);
    }
}
vector<QuadtreeNode*> getChildren(QuadtreeNode* node) {
    if (!node) return {};
    return node->children;
}

int main() {
   
    QuadtreeNode* root = new QuadtreeNode(0);
   

    for (int i = 1; i <= 4; ++i) {
        QuadtreeNode* child = new QuadtreeNode(i);
        child->parent = root;
        root->children.push_back(child);
        cout<<"the node with id :"<<child->id <<"is inserted"<<endl;
    }
   
 printRemainingNodes(root);
    


    return 0;
}
