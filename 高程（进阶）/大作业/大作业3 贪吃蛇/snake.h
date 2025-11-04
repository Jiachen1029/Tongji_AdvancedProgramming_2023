#pragma once
#include <vector>
using namespace std;

class Snake
{
public:
    Snake(int startX, int startY, int initialLength)
        : length(initialLength), currentDirection('R') 
    {
        // 初始化蛇的位置
        for (int i = 0; i < initialLength; ++i) {
            positions.push_back({ startX - i, startY });
        }
    }

    void move(char direction)
    {
        // 更新方向
        if ((direction == 'U' && currentDirection != 'D') ||
            (direction == 'D' && currentDirection != 'U') ||
            (direction == 'L' && currentDirection != 'R') ||
            (direction == 'R' && currentDirection != 'L')) 
        {
            currentDirection = direction;
        }

        // 计算新头部位置
        int newX = positions.front().first;
        int newY = positions.front().second;
        switch (currentDirection) 
        {
        case 'U': newY--; break;
        case 'D': newY++; break;
        case 'L': newX--; break;
        case 'R': newX++; break;
        }

        // 更新蛇的位置
        positions.insert(positions.begin(), { newX, newY });
        if (positions.size() > length) 
        {
            positions.pop_back();
        }
    }

    void grow() 
    {
        // 增加蛇的长度
        length++;
    }

    void shrink()
    {
        // 减少蛇的长度
        length = (length + 1) / 2;
        if (positions.size() > length)
        {
            positions.resize(length);
        }
    }

    bool checkCollision() const 
    {
        // 检查蛇是否与自身碰撞
        for (size_t i = 1; i < positions.size(); ++i) 
        {
            if (positions[i] == positions.front()) 
            {
                return true;
            }
        }
        return false;
    }

    bool checkBoundaryCollision(int maxX, int maxY) const
    {
        // 检查蛇是否与边界碰撞
        int headX = positions.front().first;
        int headY = positions.front().second;
        return headX < 0 || headX >= maxX || headY < 0 || headY >= maxY;
    }

    bool checkFoodCollision(int foodX, int foodY) const 
    {
        // 检查蛇是否与食物碰撞
        return positions.front().first == foodX && positions.front().second == foodY;
    }

    void getPositions(int* posArray, int& len) const 
    {
        // 获取蛇的位置
        len = positions.size();
        for (size_t i = 0; i < positions.size(); ++i) 
        {
            posArray[i * 2] = positions[i].first;
            posArray[i * 2 + 1] = positions[i].second;
        }
    }

    int getLength() const 
    {
        return length;
    }

    char getDirection() const 
    {
        return currentDirection;
    }

    void setDirection(char direction)
    {
        currentDirection = direction;
    }

private:
    int length;
    char currentDirection;
    vector<pair<int, int>> positions; // 存储蛇的每个节点位置
};