//
// Created by 31818 on 2024/3/13.
//

#ifndef PATH_PLANNING_A_STAR_H
#define PATH_PLANNING_A_STAR_H

#include <iostream>
#include <vector>
#include <queue>
#include "grid.h"
// 定义A*节点
struct Node {
    int row;
    int col;
    int g; // 从起点到该点的实际代价
    int h; // 从该点到终点的估计代价
    int f; // f = g + h
    Node* parent;

    Node(int r, int c, int gVal, int hVal, Node* p) : row(r), col(c), g(gVal), h(hVal), f(gVal + hVal), parent(p) {}
};

// 比较节点的优先级，用于优先队列
struct CompareNode {
    bool operator()(const Node* n1, const Node* n2) const {
        return n1->f > n2->f;
    }
};


std::vector<std::pair<int, int>> AStar(const GridMap& map, const std::pair<int, int>& start, const std::pair<int, int>& goal);

#endif //PATH_PLANNING_A_STAR_H
