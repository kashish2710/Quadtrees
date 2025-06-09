#include <iostream>
#include <vector>
using namespace std;
//code for spliting 
struct Vertex {
    int x, y;         // Top-left corner
    int width, height;
    int level;

    Vertex(int x, int y, int w, int h, int lvl)
        : x(x), y(y), width(w), height(h), level(lvl) {}
};


struct QuadtreeNode {
    Vertex region;
    vector<QuadtreeNode*> children;

    QuadtreeNode(Vertex r) : region(r) {}
};


vector<QuadtreeNode*> leafNodes;

// Recursively divide 
void subdivide(QuadtreeNode* node) {
    int w = node->region.width;
    int h = node->region.height;

    if (w <= 25 && h <= 25) {
        leafNodes.push_back(node); 
        return;
    }

    int halfW = w / 2, halfH = h / 2;
    int x = node->region.x, y = node->region.y;
    int nextLevel = node->region.level + 1;

    node->children = {
        new QuadtreeNode(Vertex(x, y, halfW, halfH, nextLevel)),
        new QuadtreeNode(Vertex(x + halfW, y, halfW, halfH, nextLevel)),
        new QuadtreeNode(Vertex(x, y + halfH, halfW, halfH, nextLevel)),
        new QuadtreeNode(Vertex(x + halfW, y + halfH, halfW, halfH, nextLevel))
    };

    for (auto* child : node->children)
        subdivide(child);
}


void printLeaves() {
    for (auto* node : leafNodes) {
        cout << "Leaf: (" << node->region.x << "," << node->region.y << "), "
             << "Size: " << node->region.width << "x" << node->region.height
             << ", Level: " << node->region.level << "\n";
    }
}

int main() {
    Vertex root(0, 0, 100, 100, 0);
    QuadtreeNode* tree = new QuadtreeNode(root);

    subdivide(tree);

    cout << "All 25x25 Leaf Nodes:\n";
    printLeaves();

    return 0;
}