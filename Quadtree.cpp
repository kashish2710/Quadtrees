//this is cpp file where functions are defined with proper logic
#include "Quadtree.h"

int QuadtreeNode::currentID = 1;
vector<QuadtreeNode*> QuadtreeNode::leafNodes;

QuadtreeNode::QuadtreeNode(Vertex r) : region(r), id(currentID++) {}

void QuadtreeNode::subdivide(QuadtreeNode* node, int minW, int minH, int scale) {
    int w = node->region.width;
    int h = node->region.height;

    if (w <= minW && h <= minH) {
        leafNodes.push_back(node);
        return;
    }

    int subW = (w + scale - 1) / scale;
    int subH = (h + scale - 1) / scale;
    int x = node->region.x, y = node->region.y;
    int nextLevel = node->region.level + 1;

    for (int i = 0; i < scale; ++i) {
        for (int j = 0; j < scale; ++j) {
            int newX = x + i * subW;
            int newY = y + j * subH;
            int actualW = min(subW, x + w - newX);
            int actualH = min(subH, y + h - newY);

            if (actualW > 0 && actualH > 0) {
                auto* child = new QuadtreeNode(Vertex(newX, newY, actualW, actualH, nextLevel));
                child->parent = node;
                node->children.push_back(child);
            }
        }
    }

    for (auto* child : node->children)
        subdivide(child, minW, minH, scale);
}

bool QuadtreeNode::inBoundary(QuadtreeNode* node, int px, int py) {
    return (px >= node->region.x &&
            px <= node->region.x + node->region.width - 1 &&
            py >= node->region.y &&
            py <= node->region.y + node->region.height - 1);
}

void QuadtreeNode::insertPoint(int px, int py) {
    for (auto* node : leafNodes) {
        if (inBoundary(node, px, py)) {
            node->points.emplace_back(px, py);
            cout << "Inserted point (" << px << "," << py << ") into region ("
                 << node->region.x << "," << node->region.y << ") of size "
                 << node->region.width << "x" << node->region.height
                 << ", ID: " << node->id << "\n";
            return;
        }
    }
    cout << "(" << px << "," << py << ") is outside quadtree bounds.\n";
}

void QuadtreeNode::pathtoroot(int px, int py) {
    for (auto* node : leafNodes) {
        if (inBoundary(node, px, py)) {
            cout << "Point (" << px << "," << py << ") is inside region:\n";
            cout << "Top-Left: (" << node->region.x << "," << node->region.y << ")\n";
            cout << "Size: " << node->region.width << "x" << node->region.height << "\n";
            cout << "Level: " << node->region.level << "\n";
            cout << "ID: " << node->id << "\n";

            vector<int> back_to_root;
            while (node != nullptr) {
                back_to_root.push_back(node->id);
                node = node->parent;
            }

            cout << "Path from node to root: ";
            for (int id : back_to_root) cout << id << " ";
            cout << "\n";
            return;
        }
    }

    cout << "Point (" << px << "," << py << ") is not inside any leaf node.\n";
}

void QuadtreeNode::printPathFromLeafToRoot(QuadtreeNode* node) {
    vector<int> path;
    while (node) {
        path.push_back(node->id);
        node = node->parent;
    }
    reverse(path.begin(), path.end());
    cout << "Path from root to this node: ";
    for (int id : path) cout << id << " ";
    cout << "\n";
}

void QuadtreeNode::removeFromParent(QuadtreeNode* current, QuadtreeNode* target) {
    if (current == nullptr || current->children.empty()) return;

    auto& ch = current->children;
    for (auto it = ch.begin(); it != ch.end(); ++it) {
        if (*it == target) {
            ch.erase(it);
            return;
        }
    }

    for (auto* child : ch)
        removeFromParent(child, target);
}

void QuadtreeNode::deletePoint(int px, int py, QuadtreeNode* root) {
    for (auto it = leafNodes.begin(); it != leafNodes.end(); ++it) {
        QuadtreeNode* node = *it;
        if (inBoundary(node, px, py)) {
            if (!node->children.empty()) {
                cout << "Region is not a leaf. Cannot delete.\n";
                return;
            }

            if (root) {
                removeFromParent(root, node);
            }

            leafNodes.erase(it);

            cout << "Logically deleted region containing (" << px << "," << py << ") with top-left (" 
                 << node->region.x << "," << node->region.y << ") and size " 
                 << node->region.width << "x" << node->region.height << "\n";
            printLeaves();
            return;
        }
    }
    cout << "Point (" << px << "," << py << ") is outside all leaf regions. Cannot delete.\n";
}

void QuadtreeNode::searchPoint(int px, int py) {
    for (auto* node : leafNodes) {
        if (inBoundary(node, px, py)) {
            cout << "Point (" << px << "," << py << ") is inside region:\n";
            cout << "Top-Left: (" << node->region.x << "," << node->region.y << ")\n";
            cout << "Size: " << node->region.width << "x" << node->region.height << "\n";
            cout << "Level: " << node->region.level << "\n";
            cout << "ID: " << node->id << "\n";
            printPathFromLeafToRoot(node);
            return;
        }
    }
    cout << "(" << px << "," << py << ") is outside quadtree bounds.\n";
}

void QuadtreeNode::printLeaves() {
    for (auto* node : leafNodes) {
        cout << "Leaf: (" << node->region.x << "," << node->region.y << "), "
             << "Size: " << node->region.width << "x" << node->region.height
             << ", Level: " << node->region.level << ", ID: " << node->id << "\n";
    }
    cout << "Total leaf nodes: " << leafNodes.size() << "\n";
}
