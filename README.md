# 🌳 Quadtree Visualization in C++

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


