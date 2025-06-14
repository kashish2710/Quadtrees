//this is main.cpp where program initiates and operates

#include <iostream>
#include <string>
#include "Quadtree.h"
using namespace std;

QuadtreeNode* tree = nullptr;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Enter a function (subdivide / insertPoint / searchPoint / deletePoint):\n";
        return 1;
    }

    string command = argv[1];

    if (command == "subdivide") {
        if (argc != 7) {
            cout << "Incorrect number of arguments for subdivide\n";
            return 1;
        }

        int maxW = stoi(argv[2]);
        int maxH = stoi(argv[3]);
        int minW = stoi(argv[4]);
        int minH = stoi(argv[5]);
        int scale = stoi(argv[6]);

        Vertex root(0, 0, maxW, maxH, 0);
        tree = new QuadtreeNode(root);
        QuadtreeNode::leafNodes.clear();

        QuadtreeNode::subdivide(tree, minW, minH, scale);
        cout << "Tree created. Insert points and search enabled.\n";
        QuadtreeNode::printLeaves();

        while (true) {
            cout << "\nEnter command: insertPoint x y  |  searchPoint x y  | deletePoint x y | pathtoroot x y | exit\n";
            string subcmd;
            cin >> subcmd;

            if (subcmd == "exit") break;

            int px, py;
            cin >> px >> py;

            if (subcmd == "insertPoint") {
                QuadtreeNode::insertPoint(px, py);
                QuadtreeNode::printLeaves();
            } else if (subcmd == "searchPoint") {
                QuadtreeNode::searchPoint(px, py);
            } else if (subcmd == "pathtoroot") {
                QuadtreeNode::pathtoroot(px, py);
            } else if (subcmd == "deletePoint") {
                QuadtreeNode::deletePoint(px, py, tree);
            } else {
                cout << "Invalid command.\n";
            }
        }
    }

    else if (command == "insertPoint") {
        if (argc != 4) {
            cout << "Incorrect number of arguments for insertPoint\n";
            return 1;
        }

        int px = stoi(argv[2]);
        int py = stoi(argv[3]);
        QuadtreeNode::insertPoint(px, py);
    }

    else if (command == "searchPoint") {
        if (argc != 4) {
            cout << "Incorrect number of arguments for searchPoint\n";
            return 1;
        }

        int px = stoi(argv[2]);
        int py = stoi(argv[3]);
        QuadtreeNode::searchPoint(px, py);
    }

    else {
        cout << "Unknown command: " << command << "\n";
        return 1;
    }

    return 0;
}
