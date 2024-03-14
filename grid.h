//
// Created by 31818 on 2024/3/12.
//

#ifndef PATH_PLANNING_GRID_H
#define PATH_PLANNING_GRID_H

#include <SFML/Graphics.hpp>
// 定义栅格地图类
class GridMap {
private:
    int rows;
    int cols;
    std::vector<std::vector<int>> field;

public:
    // 构造函数
    GridMap(int numRows, int numCols) : rows(numRows), cols(numCols) {
        // 初始化栅格地图全域
        field.resize(rows, std::vector<int>(cols, 0));

        // 随机生成障碍物
        srand(time(nullptr));
        double obsRate = 0.3; // 障碍物占比
        int obsNum = static_cast<int>(rows * cols * obsRate);
        for (int i = 0; i < obsNum; ++i) {
            int obsIndex = rand() % (rows * cols);
            int obsRow = obsIndex / cols;
            int obsCol = obsIndex % cols;
            field[obsRow][obsCol] = 1;
        }

//        // 设置起始点和目标点
//        int startPos = 2;
//        int goalPos = rows * cols - 2;
//        int startRow = startPos / cols;
//        int startCol = startPos % cols;
//        int goalRow = goalPos / cols;
//        int goalCol = goalPos % cols;
//        field[startRow][startCol] = 3;
//        field[goalRow][goalCol] = 4;
    }

    // 获取栅格地图数据
    const std::vector<std::vector<int>>& getField() const {
        return field;
    }

    // 获取行数
    int getRows() const {
        return rows;
    }

    // 获取列数
    int getCols() const {
        return cols;
    }
};

#endif //PATH_PLANNING_GRID_H
