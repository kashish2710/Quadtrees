//this is a header file where only declaration of methods of class QudatreeNode takes place
#ifndef QUADTREE_NODE_H
#define QUADTREE_NODE_H

#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>

using namespace std;

struct Vertex {
    int x, y;
    int width, height;
    int level;

    Vertex(int x, int y, int w, int h, int lvl)
        : x(x), y(y), width(w), height(h), level(lvl) {}
};

class QuadtreeNode {
public:
    Vertex region;
    vector<QuadtreeNode*> children;
    vector<pair<int, int>> points;
    int id;
    QuadtreeNode* parent = nullptr;

    static int currentID;
    static vector<QuadtreeNode*> leafNodes;

    QuadtreeNode(Vertex r);

    static void subdivide(QuadtreeNode* node, int minW, int minH, int scale);
    static void insertPoint(int px, int py);
    static void deletePoint(int px, int py, QuadtreeNode* root = nullptr);
    static void searchPoint(int px, int py);
    static void pathtoroot(int px, int py);
    static void printPathFromLeafToRoot(QuadtreeNode* node);
    static void removeFromParent(QuadtreeNode* current, QuadtreeNode* target);
    static void printLeaves();
    static bool inBoundary(QuadtreeNode* node, int px, int py);
};

#endif
