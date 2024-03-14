#include "grid.h"
#include "A_star.h"
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>


typedef std::pair<int, int> point;
typedef std::vector<std::pair<point , point>> point_vector;


// 定义颜色映射
sf::Color colors[] = {
        sf::Color::White,
        sf::Color::Black,
        sf::Color::Red,
        sf::Color::Yellow,
        sf::Color::Magenta,
        sf::Color::Green,
        sf::Color::Cyan
};

// 生成多个起点和目标点
point_vector generateStartAndGoal(const GridMap& map, int numAgents) {
    point_vector startAndGoal;

    int rows = map.getRows();
    int cols = map.getCols();

    for (int i = 0; i < numAgents; ++i) {
        int startRow, startCol, goalRow, goalCol;
        do {
            startRow = rand() % rows;
            startCol = rand() % cols;
        } while (map.getField()[startRow][startCol] == 1);
        do {
            goalRow = rand() % rows;
            goalCol = rand() % cols;
        } while (map.getField()[goalRow][goalCol] == 1 || (startRow == goalRow && startCol == goalCol));
        startAndGoal.push_back({{startRow, startCol}, {goalRow, goalCol}});
    }
    return startAndGoal;
}


int main() {
    int rows = 20;
    int cols = 20;

    int pixel_size = 30;

    GridMap map(rows, cols);
    point_vector startAndGoal = generateStartAndGoal(map, 5);
    //单起点，单终点
//    point start = {0, 2};
//    point goal = {(rows*cols-2)/cols, (rows*cols-2)%cols};
//
//    std::vector<std::pair<int, int>> path = AStar(map, start, goal);
    //多起点，多终点
    std::vector<std::vector<std::pair<int, int>>> all_paths;
    for (const auto &pair : startAndGoal) {
        all_paths.insert(all_paths.end(), AStar(map,pair.first,pair.second));
    }
    int c = 0;
    for (const auto &pair: all_paths) {
        std::cout << c++<<":";
        for (const auto &index:pair) {
            std::cout <<"("<< index.first << "," << index.second <<"),";
        }
        std::cout << std::endl;
    }

    // 创建窗口
    sf::RenderWindow window(sf::VideoMode(cols * pixel_size, rows * pixel_size), "Grid Map");
    int printf_flag = 0;
    // 添加起点和终点的文本标签
    sf::Font font;
    if (!font.loadFromFile("E:\\Files\\code_files\\path_planning\\Arial.ttf")) {
        // 如果加载字体失败，可以使用默认字体或者其他字体
        // 可以输出错误信息以便调试
        std::cerr << "Failed to load font file!" << std::endl;
    }
    // 主循环
    while (window.isOpen()) {
        // 处理事件
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // 清除窗口
        window.clear();

        // 绘制栅格地图
        const auto& field = map.getField();
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                sf::RectangleShape rectangle(sf::Vector2f(pixel_size, pixel_size));
                rectangle.setPosition(j * pixel_size, i * pixel_size);
                rectangle.setFillColor(colors[field[i][j]]);
                window.draw(rectangle);
            }
        }
        // 绘制多个起点和目标点
        size_t i = 1;
        for (const auto& pair : startAndGoal) {
            int startRow = pair.first.first;
            int startCol = pair.first.second;
            int goalRow = pair.second.first;
            int goalCol = pair.second.second;

            sf::CircleShape startShape((pixel_size/2));
            startShape.setFillColor(sf::Color::Blue);
            startShape.setPosition(startCol * pixel_size , startRow * pixel_size);
            window.draw(startShape);

            sf::CircleShape goalShape((pixel_size/2));
            goalShape.setFillColor(sf::Color::Green);
            goalShape.setPosition(goalCol * pixel_size , goalRow * pixel_size);
            window.draw(goalShape);

            sf::Text startText("S"+std::to_string(i), font); // 创建文本对象，第三个参数是字体大小
            startText.setCharacterSize(15); // 设置字体大小
            startText.setFillColor(sf::Color::Magenta); // 设置文本颜色
            startText.setPosition(startCol * pixel_size+5, startRow * pixel_size+5); // 设置文本位置
            window.draw(startText);

            sf::Text goalText("E"+std::to_string(i), font);
            goalText.setCharacterSize(15); // 设置字体大小
            goalText.setFillColor(sf::Color::Magenta);
            goalText.setPosition(goalCol * pixel_size+5, goalRow * pixel_size+5);
            window.draw(goalText);
            i++;

//            if(printf_flag == 0) {
//                std::cout << i++ << ":(" << startRow << "," << startCol << "),(" << goalRow << "," << goalCol << ")"
//                          << std::endl;
//            }
        }
        //绘制多到多的路径

        if(!all_paths.empty()){
            for (const auto &path: all_paths) {
                if (!path.empty()){
                    for (size_t j = 0; j < path.size() - 1; ++j) {
                        sf::Vertex line[] = {
                                sf::Vertex(sf::Vector2f(path[j].second * 30 + 15, path[j].first * 30 + 15),
                                           sf::Color::Red),
                                sf::Vertex(sf::Vector2f(path[j + 1].second * 30 + 15, path[j + 1].first * 30 + 15),
                                           sf::Color::Red)
                        };
                        window.draw(line, 2, sf::Lines);
                    }
                }
            }
        }
        printf_flag = 1;
        // 绘制路径
//        if (!path.empty()) {
//            for (size_t i = 0; i < path.size() - 1; ++i) {
//                sf::Vertex line[] = {
//                        sf::Vertex(sf::Vector2f(path[i].second * 30 + 15, path[i].first * 30 + 15), sf::Color::Red),
//                        sf::Vertex(sf::Vector2f(path[i + 1].second * 30 + 15, path[i + 1].first * 30 + 15), sf::Color::Red)
//                };
//                window.draw(line, 2, sf::Lines);
//            }
//        }
        // 显示窗口内容
        window.display();
    }

    return 0;
}
