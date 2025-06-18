#include <iostream>
#include <vector>
#include <string>
#include <boost/graph/adjacency_list.hpp>


using namespace std;
using namespace boost;


struct Partition {
    string name;
    int x1, y1, x2, y2;
};


bool verticalRangesOverlap(int y1a, int y2a, int y1b, int y2b) {
    return max(y1a, y1b) < min(y2a, y2b);
}

bool isHorizontallyTouching(const Partition& a, const Partition& b) {
    return (
        (a.x2 == b.x1 || a.x1 == b.x2) &&
        verticalRangesOverlap(a.y1, a.y2, b.y1, b.y2)
    );
}

typedef adjacency_list<vecS, vecS, undirectedS> Graph;

int main() {
   
    vector<Partition> partitions = {
        {"P1", 0 ,0,50,100},
        {"P2", 50, 0, 75, 50},
        {"P3", 50, 50, 75, 100},
        {"P4", 75, 0, 100, 100}
    };

    size_t n = partitions.size();
    Graph g(n);

    vector<vector<int>> adjacencyMatrix(n, vector<int>(n, 0));

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i + 1; j < n; ++j) {
            if (isHorizontallyTouching(partitions[i], partitions[j])) {
                add_edge(i, j, g);
                adjacencyMatrix[i][j] = 1;
                adjacencyMatrix[j][i] = 1;
            }
        }
    }


    cout << "\nChannel_graph:\n\t";
    for (size_t i = 0; i < n; ++i)
        cout << partitions[i].name << "\t";
    cout << endl;

    for (size_t i = 0; i < n; ++i) {
        cout << partitions[i].name << "\t";
        for (size_t j = 0; j < n; ++j) {
            cout << adjacencyMatrix[i][j] << "\t";
        }
        cout << endl;
    }

    return 0;
}

