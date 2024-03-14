//
// Created by 31818 on 2024/3/13.
//
#include "A_star.h"

/**
 * A*算法，寻找最优路径
 * @param map
 * @param start
 * @param goal
 * @return
 */
std::vector<std::pair<int, int>> AStar(const GridMap& map, const std::pair<int, int>& start, const std::pair<int, int>& goal) {
    std::vector<std::pair<int, int>> path;

    int rows = map.getRows();
    int cols = map.getCols();

    // 计算启发式函数值，这里采用曼哈顿距离
    auto heuristic = [&](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return std::abs(a.first - b.first) + std::abs(a.second - b.second);
    };

    // 定义优先队列和关闭集合
    std::priority_queue<Node*, std::vector<Node*>, CompareNode> openSet;
    std::vector<std::vector<bool>> closedSet(rows, std::vector<bool>(cols, false));

    // 起始节点
    Node* startNode = new Node(start.first, start.second, 0, heuristic(start, goal), nullptr);
    openSet.push(startNode);

    // A*搜索
    while (!openSet.empty()) {
        Node* current = openSet.top();
        openSet.pop();

        // 如果当前节点是目标节点，构建路径并返回
        if (current->row == goal.first && current->col == goal.second) {
            while (current != nullptr) {
                path.push_back({current->row, current->col});
                current = current->parent;
            }
            break;
        }

        // 将当前节点标记为已关闭
        closedSet[current->row][current->col] = true;

        // 探索当前节点的相邻节点
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        for (int i = 0; i < 4; ++i) {
            int newRow = current->row + dr[i];
            int newCol = current->col + dc[i];

            // 跳过超出边界或者是障碍物的节点
            if (newRow < 0 || newRow >= rows || newCol < 0 || newCol >= cols || map.getField()[newRow][newCol] == 1)
                continue;

            // 跳过已经在关闭集合中的节点
            if (closedSet[newRow][newCol])
                continue;

            // 计算相邻节点的代价
            int newG = current->g + 1; // 这里假设每个相邻节点的代价都是1

            // 如果相邻节点不在开放集合中，或者当前路径代价更小，则更新节点信息
            bool inOpenSet = false;
            for (std::priority_queue<Node*, std::vector<Node*>, CompareNode> temp = openSet; !temp.empty();) {
                Node* node = temp.top();
                temp.pop();
                if (node->row == newRow && node->col == newCol) {
                    inOpenSet = true;
                    if (newG < node->g) {
                        node->g = newG;
                        node->f = node->g + node->h;
                        node->parent = current;
                    }
                    break;
                }
            }

            if (!inOpenSet) {
                Node* newNode = new Node(newRow, newCol, newG, heuristic({newRow, newCol}, goal), current);
                openSet.push(newNode);
            }
        }
    }

    // 释放内存
    for (auto& row : closedSet) {
        row.clear();
    }

    while (!openSet.empty()) {
        delete openSet.top();
        openSet.pop();
    }

    return path;
}