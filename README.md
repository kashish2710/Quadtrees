#  Quadtree Visualization in C++

Efficient spatial partitioning using the **Quadtree** data structure, implemented in **C++**. This project supports insertion, deletion (with conditions), and recursive traversal, making it perfect for use cases like:

-  Image compression
-  Game collision detection
-  GIS and mapping
-  AI pathfinding on 2D grids

---

##  What is a Quadtree?

A **Quadtree** recursively subdivides a 2D space into 4 equal quadrants. It's ideal for representing 2D spatial data, especially when dealing with regions that are sparsely populated.

Example structure: 

        Root
     /  |  |  \
    NW  NE SW  SE

    # Directories
    quadtree-visualization-cpp/
    │
    ├── src/
    │   ├── Insert.cpp
    │   ├── Delete.cpp
    │   ├── Construct.cpp
    │
    ├── assets/
    │   └── images
    │
    ├── README.md
# Quadtree Subdivision Visualizer (C++ CLI Project)

This is a C++ implementation of an **MX-Quadtree**, which subdivides a given 2D space into smaller uniform regions recursively. The project supports dynamic insertion, search, deletion, and root-to-leaf path tracing of points within the subdivided regions.

## 🔧 Features

- Recursive subdivision using scale factor
- Insert and locate points inside leaf nodes
- Search for a point's region (ID, level, size)
- Delete regions logically (only leaf deletions allowed)
- Print path from a leaf node to root
- CLI (command line interface) based usage

---

## 📁 Project Structure

├── Quadtree.h # Header file containing class definition and functions
├── Quadtree.cpp # Contains helper function logic (optional, if split)
├── main.cpp # CLI runner file with int main()

yaml
Copy
Edit


##  How to Compile & Run

### 1. **Compile using g++**

```bash
g++ main.cpp -o quadtree
If you're using separate files:

bash
Copy
Edit
g++ main.cpp Quadtree.cpp -o quadtree
This will create an executable named quadtree.

▶ How to Use
Subdivide a region

./quadtree subdivide 1000 1000 2 2 2
Arguments:

1000 1000: width and height of root

2 2: minimum width and height allowed before stopping

2: scale (2x2 division)

After running, interactive commands will be available:

insertPoint x y       # Insert point in a region
searchPoint x y       # Search for point and its region
deletePoint x y       # Logically delete a leaf region
pathtoroot x y        # Show node ID path from leaf to root
exit                  # Exit CLI
# Sample Usage

./quadtree subdivide 100 100 25 25 2



insertPoint 30 40
searchPoint 30 40
pathtoroot 30 40
deletePoint 30 40
##  Requirements
C++11 or above

g++ compiler

Command-line terminal (Linux, macOS, or Windows with WSL/PowerShell)

 Notes
Only leaf nodes can be deleted.

pathtoroot will show the node hierarchy using assigned IDs.

Out-of-bound points will be rejected safely.





