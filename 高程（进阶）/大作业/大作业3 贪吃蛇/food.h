#pragma once
#include <cstdlib>
#include <ctime>
using namespace std;

class Food
{
public:
    Food() : x(-1), y(-1), maxX(0), maxY(0) {}
    Food(int maxX, int maxY) : maxX(maxX), maxY(maxY) 
    {
        generateNewPosition();
    }
    void generateNewPosition() 
    {
        x = rand() % maxX;
        y = rand() % maxY;
    }
    void setPosition(int newX, int newY)
    {
        x = newX;
        y = newY;
    }
    int getX() const 
    {
        return x;
    }
    int getY() const 
    {
        return y;
    }
private:
    int x, y;
    int maxX, maxY;
};