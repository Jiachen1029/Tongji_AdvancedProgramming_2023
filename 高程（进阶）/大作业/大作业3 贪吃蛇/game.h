#pragma once
#include "Snake.h"
#include "Food.h"
#include "History.h"
#include <ctime>
#include <vector>
#include <queue> 
#include <conio.h>
#include <windows.h>
#include <graphics.h> 
using namespace std;

const int GRID_SIZE = 20;
const int GRID_WIDTH = 24;
const int GRID_HEIGHT = 24;
const int INFO_WIDTH = 200;
const int WINDOW_WIDTH = GRID_WIDTH * GRID_SIZE + INFO_WIDTH;
const int WINDOW_HEIGHT = GRID_HEIGHT * GRID_SIZE;

enum class GameMode 
{
    BASIC,
    INTERMEDIATE,
    ADVANCED
};

class Game 
{
public:
    Game(GameMode mode, const string& username)
        : snake(3, 3, 3), history(username), username(username),
        score(0), highScore(0), lives(mode == GameMode::ADVANCED ? 5 : 0), gameOver(false), mode(mode), specialFoodActive(false), evilFoodActive(false), wallCollisionCount(0), paused(false)
    {
        startTime = time(nullptr);
        initgraph(WINDOW_WIDTH, WINDOW_HEIGHT); 
        loadHighScore(); //历史最高分
        generateFood(); //初始食物
    }

    void start() 
    {
        while (!gameOver)
        {
            handleInput();
            if (!paused) 
            {
                update();
                render();
            }
            Sleep(100); //控制速度
        }
        saveRecord(); //保存游戏记录
        closegraph(); //关闭图形窗口
    }

    void update()
    {
        snake.move(snake.getDirection());
        if (snake.checkCollision() || snake.checkBoundaryCollision(GRID_WIDTH, GRID_HEIGHT) || checkWallCollision())
        {
            handleSnakeDeath();
        }
        for (auto it = foods.begin(); it != foods.end();) 
        {
            if (snake.checkFoodCollision(it->getX(), it->getY())) 
            {
                snake.grow();
                updateScore(10);
                it = foods.erase(it);
            }
            else {

                ++it;
            }
        }
        if (foods.empty()) 
        {
            generateFood();
        }
        if (specialFoodActive && snake.checkFoodCollision(specialFood.getX(), specialFood.getY())) 
        {
            for (int i = 0; i < 5; ++i) 
            {
                snake.grow();
            }
            updateScore(50);
            specialFoodActive = false;
        }
        if (specialFoodActive && difftime(time(nullptr), specialFoodStartTime) >= 10)
        {
            specialFoodActive = false;
        }
        if (evilFoodActive && snake.checkFoodCollision(evilFood.getX(), evilFood.getY()))
        {
            snake.shrink();
            updateScore(-100);
            evilFoodActive = false;
        }
        if (evilFoodActive && difftime(time(nullptr), evilFoodStartTime) >= 10)
        {
            evilFoodActive = false;
        }
        updateGameTime();
    }

    void render()
    {
        cleardevice();
        // 绘制分数、历史最高分、生命数和游戏时间
        settextstyle(20, 0, _T("等线"));
        TCHAR scoreText[50];
        _stprintf_s(scoreText, _T("Score: %d"), score);
        outtextxy(GRID_WIDTH * GRID_SIZE + 10, 10, scoreText);

        TCHAR highScoreText[50];
        _stprintf_s(highScoreText, _T("Highest Score: %d"), highScore);
        outtextxy(GRID_WIDTH * GRID_SIZE + 10, 40, highScoreText);

        if (mode == GameMode::ADVANCED)
        {
            TCHAR livesText[50];
            _stprintf_s(livesText, _T("Lives: %d"), lives);
            outtextxy(GRID_WIDTH * GRID_SIZE + 10, 70, livesText);
        }

        TCHAR timeText[50];
        _stprintf_s(timeText, _T("Time: %ds"), static_cast<int>(difftime(time(nullptr), startTime)));
        outtextxy(GRID_WIDTH * GRID_SIZE + 10, 100, timeText);

        // 添加提示信息
        outtextxy(GRID_WIDTH * GRID_SIZE + 10, 130, _T("按空格键暂停/继续"));
        outtextxy(GRID_WIDTH * GRID_SIZE + 10, 160, _T("按ESC键回到主页"));

        // 绘制红色方块提示
        setfillcolor(RGB(255, 0, 0));
        solidrectangle(GRID_WIDTH * GRID_SIZE + 10, 190, GRID_WIDTH * GRID_SIZE + 30, 210);
        outtextxy(GRID_WIDTH * GRID_SIZE + 40, 190, _T("好果子+10分"));

        // 绘制绿色方块提示
        setfillcolor(RGB(0, 255, 0));
        solidrectangle(GRID_WIDTH * GRID_SIZE + 10, 220, GRID_WIDTH * GRID_SIZE + 30, 240);
        outtextxy(GRID_WIDTH * GRID_SIZE + 40, 220, _T("金果子+50分"));

        // 绘制蓝色方块提示
        setfillcolor(RGB(0, 0, 255));
        solidrectangle(GRID_WIDTH * GRID_SIZE + 10, 250, GRID_WIDTH * GRID_SIZE + 30, 270);
        outtextxy(GRID_WIDTH * GRID_SIZE + 40, 250, _T("坏果子-100分"));

        // 绘制蛇
        int positions[500];
        int length;
        snake.getPositions(positions, length);
        for (int i = 0; i < length; ++i)
        {
            rectangle(positions[i * 2] * GRID_SIZE, positions[i * 2 + 1] * GRID_SIZE, (positions[i * 2] + 1) * GRID_SIZE, (positions[i * 2 + 1] + 1) * GRID_SIZE);
        }

        // 绘制食物
        setfillcolor(RGB(255, 0, 0));
        for (const auto& food : foods)
        {
            solidrectangle(food.getX() * GRID_SIZE, food.getY() * GRID_SIZE, (food.getX() + 1) * GRID_SIZE, (food.getY() + 1) * GRID_SIZE);
        }

        //特殊食物
        if (specialFoodActive) 
        {
            setfillcolor(RGB(0, 255, 0));
            solidrectangle(specialFood.getX() * GRID_SIZE, specialFood.getY() * GRID_SIZE, (specialFood.getX() + 1) * GRID_SIZE, (specialFood.getY() + 1) * GRID_SIZE);
        }

        //恶毒食物
        if (evilFoodActive)
        {
            setfillcolor(RGB(0, 0, 255));
            solidrectangle(evilFood.getX() * GRID_SIZE, evilFood.getY() * GRID_SIZE, (evilFood.getX() + 1) * GRID_SIZE, (evilFood.getY() + 1) * GRID_SIZE);
        }

        // 绘制墙
        for (const auto& wall : walls)
        {
            setfillcolor(RGB(128, 128, 128));
            solidrectangle(wall.first * GRID_SIZE, wall.second * GRID_SIZE, (wall.first + 1) * GRID_SIZE, (wall.second + 1) * GRID_SIZE);
        }

        // 绘制边界
        setlinecolor(WHITE);
        rectangle(0, 0, GRID_WIDTH * GRID_SIZE, GRID_HEIGHT * GRID_SIZE);

        // 刷新屏幕
        FlushBatchDraw();
    }

    void handleInput() 
    {
        if (GetAsyncKeyState(VK_UP) & 0x8000) {
            if (snake.getDirection() != 'D') snake.setDirection('U');
        }
        else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            if (snake.getDirection() != 'U') snake.setDirection('D');
        }
        else if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            if (snake.getDirection() != 'R') snake.setDirection('L');
        }
        else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            if (snake.getDirection() != 'L') snake.setDirection('R');
        }
        else if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
            paused = !paused; // 切换暂停状态
            Sleep(200); // 防止快速切换
        }
        else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            closegraph();
            extern int main();
            main();
        }
    }

    bool isGameOver() const 
    {
        return gameOver;
    }

    void displayHistory() const 
    {
        history.displayRecords();
    }

    void handleHistoryInput() 
    {
        cout << "输入R重置记录，输入其他键返回主菜单..." << endl;
        char ch = _getch();
        if (ch == 'R' || ch == 'r') 
        {
            history.resetRecords();
            cout << "历史记录已重置。" << endl;
        }
    }

    History& getHistory() 
    {
        return history;
    }

private:
    Snake snake;
    vector<Food> foods;
    Food specialFood;
    Food evilFood;
    bool specialFoodActive;
    bool evilFoodActive;
    time_t specialFoodStartTime;
    time_t evilFoodStartTime;
    History history;
    string username;
    int score;
    int highScore;
    int lives;
    int wallCollisionCount;
    time_t startTime;
    bool gameOver;
    bool paused;
    GameMode mode;
    vector<pair<int, int>> walls; // 墙的位置

    void updateScore(int points) 
    {
        score += points;
        updateHighScore();
    }

    void updateHighScore() 
    {
        if (score > highScore)
        {
            highScore = score;
        }
    }

    void updateGameTime()
    {
        //更新游戏时间
    }

    void handleSnakeDeath() {
        if (mode == GameMode::INTERMEDIATE)
        {
            // 将蛇的身体节点转换为墙节点
            int length;
            int positions[500]; // 假设蛇的最大长度为250
            snake.getPositions(positions, length);
            for (int i = 0; i < length; ++i) 
            {
                if (positions[i * 2] < GRID_WIDTH)
                { // 确保不在信息栏内
                    walls.push_back({ positions[i * 2], positions[i * 2 + 1] });
                }
            }
            // 重新生成蛇和食物
            snake = generateNewSnake();
            foods.clear();
            generateFood();
            if (walls.size() >= GRID_WIDTH * GRID_HEIGHT - 3 * 3)
            {
                gameOver = true;
                int result = MessageBox(GetHWnd(), _T("游戏结束！是否重新开始？"), _T("游戏结束"), MB_YESNO | MB_ICONQUESTION);
                if (result == IDYES)
                {
                    // 重新开始游戏
                    gameOver = false;
                    score = 0;
                    wallCollisionCount = 0;
                    snake = generateNewSnake();
                    foods.clear();
                    walls.clear();
                    generateFood();
                    startTime = time(nullptr); // 重新计时
                    start();
                }
                else 
                {
                    // 回到主页
                    closegraph();
                    extern int main();
                    main();
                }
            }
        }
        else if (mode == GameMode::ADVANCED)
        {
            // 将蛇的身体节点转换为食物
            int length;
            int positions[500]; // 假设蛇的最大长度为250
            snake.getPositions(positions, length);
            for (int i = 0; i < length; ++i) 
            {
                Food food(GRID_WIDTH - 1, GRID_HEIGHT - 1); // 确保食物不会生成在最右侧边界外面
                food.setPosition(positions[i * 2], positions[i * 2 + 1]);
                foods.push_back(food);
            }
            // 重新生成蛇和食物
            snake = generateNewSnake();
            generateFood();
            wallCollisionCount++;
            lives--;
            if (wallCollisionCount > 5 || walls.size() >= GRID_WIDTH * GRID_HEIGHT - 3 * 3 || lives <= 0)
            {
                gameOver = true;
                int result = MessageBox(GetHWnd(), _T("游戏结束！是否重新开始？"), _T("游戏结束"), MB_YESNO | MB_ICONQUESTION);
                if (result == IDYES) {
                    // 重新开始游戏
                    gameOver = false;
                    score = 0;
                    lives = 5;
                    wallCollisionCount = 0;
                    snake = generateNewSnake();
                    foods.clear();
                    walls.clear();
                    generateFood();
                    startTime = time(nullptr); // 重新计时
                    start();
                }
                else 
                {
                    // 回到主页
                    closegraph();
                    extern int main();
                    main();
                }
            }
        }
        else 
        {
            gameOver = true;
            int result = MessageBox(GetHWnd(), _T("游戏结束！是否重新开始？"), _T("游戏结束"), MB_YESNO | MB_ICONQUESTION);
            if (result == IDYES) {
                // 重新开始游戏
                gameOver = false;
                score = 0;
                wallCollisionCount = 0;
                snake = generateNewSnake();
                foods.clear();
                walls.clear();
                generateFood();
                startTime = time(nullptr); // 重新计时
                start();
            }
            else 
            {
                // 回到主页
                closegraph();
                extern int main();
                main();
            }
        }
    }

    Snake generateNewSnake() 
    {
        // 生成一个新的蛇，确保它不在墙内
        int startX, startY;
        do
        {
            startX = rand() % GRID_WIDTH;
            startY = rand() % GRID_HEIGHT;
        } while (isWall(startX, startY) || isSnake(startX, startY));

        return Snake(startX, startY, 3);
    }

    void saveRecord()
    {
        string version;
        switch (mode)
        {
        case GameMode::BASIC:
            version = "入门版";
            break;
        case GameMode::INTERMEDIATE:
            version = "进阶版";
            break;
        case GameMode::ADVANCED:
            version = "高级版";
            break;
        }

        // 获取当前时间戳
        time_t now = time(nullptr);
        struct tm timeinfo;
        localtime_s(&timeinfo, &now);
        char timestamp[20];
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &timeinfo);

        Record record(version, username, score, timestamp);
        history.addRecord(record);

        // 更新历史最高分
        if (score > highScore)
        {
            highScore = score;
        }
    }

    void loadHighScore() 
    {
        // 从历史记录中加载最高分
        for (const auto& record : history.getRecords()) 
        {
            if (record.version == getVersionString() && record.score > highScore) 
            {
                highScore = record.score;
            }
        }
    }

    string getVersionString() const 
    {
        switch (mode) 
        {
        case GameMode::BASIC:
            return "入门版";
        case GameMode::INTERMEDIATE:
            return "进阶版";
        case GameMode::ADVANCED:
            return "高级版";
        default:
            return "";
        }
    }

    void generateFood()
    {
        int foodCount = rand() % 5 + 1; // 随机生成 1-5 个食物
        for (int i = 0; i < foodCount; ++i) 
        {
            Food food(GRID_WIDTH - 1, GRID_HEIGHT - 1); // 确保食物不会生成在最右侧边界外面
            while (isFoodOnSnake(food) || isFoodOnOtherFoods(food) || isFoodInDeadEnd(food) || isWall(food.getX(), food.getY())) 
            {
                food.generateNewPosition();
            }
            foods.push_back(food);
        }
        if (rand() % 10 == 0) 
        { // 10% 概率生成特殊食物
            specialFood = Food(GRID_WIDTH - 1, GRID_HEIGHT - 1); // 确保特殊食物不会生成在最右侧边界外面
            while (isFoodOnSnake(specialFood) || isFoodOnOtherFoods(specialFood) || isFoodInDeadEnd(specialFood) || isWall(specialFood.getX(), specialFood.getY()))
            {
                specialFood.generateNewPosition();
            }
            specialFoodActive = true;
            specialFoodStartTime = time(nullptr);
        }
        if (rand() % 10 == 0)
        { // 10% 概率生成恶毒食物
            evilFood = Food(GRID_WIDTH - 1, GRID_HEIGHT - 1); // 确保恶毒食物不会生成在最右侧边界外面
            while (isFoodOnSnake(evilFood) || isFoodOnOtherFoods(evilFood) || isFoodInDeadEnd(evilFood) || isWall(evilFood.getX(), evilFood.getY()))
            {
                evilFood.generateNewPosition();
            }
            evilFoodActive = true;
            evilFoodStartTime = time(nullptr);
        }
    }

    bool isFoodOnSnake(const Food& food) const
    {
        int positions[500]; // 假设蛇的最大长度为250
        int length;
        snake.getPositions(positions, length);
        for (int i = 0; i < length; ++i) {
            if (positions[i * 2] == food.getX() && positions[i * 2 + 1] == food.getY())
            {
                return true;
            }
        }
        return false;
    }

    bool isFoodOnOtherFoods(const Food& food) const
    {
        for (const auto& f : foods) 
        {
            if (f.getX() == food.getX() && f.getY() == food.getY())
            {
                return true;
            }
        }
        return false;
    }

    bool isFoodInDeadEnd(const Food& food) const 
    {
        // 广度优先搜索（BFS）算法来检查食物是否在死胡同中
        vector<vector<bool>> visited(GRID_WIDTH, vector<bool>(GRID_HEIGHT, false));
        queue<pair<int, int>> q;
        q.push(make_pair(food.getX(), food.getY()));
        visited[food.getX()][food.getY()] = true;

        int directions[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
        int freeSpaces = 0;

        while (!q.empty())
        {
            pair<int, int> current = q.front();
            int x = current.first;
            int y = current.second;
            q.pop();
            freeSpaces++;

            for (auto& dir : directions)
            {
                int newX = x + dir[0];
                int newY = y + dir[1];

                if (newX >= 0 && newX < GRID_WIDTH && newY >= 0 && newY < GRID_HEIGHT &&
                    !visited[newX][newY] && !isWall(newX, newY) && !isSnake(newX, newY))
                {
                    q.push(make_pair(newX, newY));
                    visited[newX][newY] = true;
                }
            }
        }
        //判定死胡同？
        return freeSpaces < 10;
    }

    bool isWall(int x, int y) const 
    {
        for (const auto& wall : walls)
        {
            if (wall.first == x && wall.second == y)
            {
                return true;
            }
        }
        return false;
    }

    bool isSnake(int x, int y) const 
    {
        int positions[500];
        int length;
        snake.getPositions(positions, length);
        for (int i = 0; i < length; ++i) 
        {
            if (positions[i * 2] == x && positions[i * 2 + 1] == y) 
            {
                return true;
            }
        }
        return false;
    }

    bool checkWallCollision() const 
    {
        for (const auto& wall : walls) {
            if (snake.checkFoodCollision(wall.first, wall.second)) 
            {
                return true;
            }
        }
        return false;
    }
};