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


void deleteLeafNode(QuadtreeNode* node) {
    if (!node || !node->children.empty()) return;

    deletedNodes.insert(node);
    cout << "Leaf " << node->id << " marked as deleted.\n";
}

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
    }
   

    for (int i = 0; i < 4; ++i) {
        deleteLeafNode(root->children[i]);
    
      
    }

    cout<<"only present nodes after deletion"<<endl;
    printRemainingNodes(root);

    return 0;
}