#include<iostream>
using namespace std;

class Queue
{
private:
    int data[20];
    int front, rear;
    int minValue, maxValue;

public:
    Queue()
    {
        front = 0;
        rear = 0;
        minValue = INT_MAX;
        maxValue = INT_MIN;
    }

    void push(int x)
    {
        if (rear - front < 20) // 确保队列未满
        {
            data[rear % 20] = x;
            rear++;
            // 更新最大值和最小值
            if (x > maxValue) maxValue = x;
            if (x < minValue) minValue = x;
        }
        else
        {
            cout << "Queue is full" << endl;
        }
    }

    void pop()
    {
        if (front == rear)
        {
            cout << "Error" << endl;
        }
        else
        {
            cout << data[front % 20] << endl;
            // 如果出队的元素是最大或最小值，需要重新计算
            if (data[front % 20] == maxValue || data[front % 20] == minValue)
            {
                recalculateMinMax();
            }
            front++;
        }
    }

    void max()
    {
        if (front == rear)
        {
            cout << "Error" << endl;
        }
        else
        {
            cout << maxValue << endl;
        }
    }

    void min()
    {
        if (front == rear)
        {
            cout << "Error" << endl;
        }
        else
        {
            cout << minValue << endl;
        }
    }

    void searchX(int x)
    {
        for (int i = front; i < rear; i++)
        {
            if (data[i % 20] == x)
            {
                cout << "true" << endl;
                return;
            }
        }
        cout << "false" << endl;
    }

private:
    void recalculateMinMax()
    {
        minValue = INT_MAX;
        maxValue = INT_MIN;
        for (int i = front; i < rear; i++)
        {
            if (data[i % 20] < minValue) minValue = data[i % 20];
            if (data[i % 20] > maxValue) maxValue = data[i % 20];
        }
    }
};

int main()
{
    Queue q;
    string command;
    int x;

    while (true)
    {
        cin >> command;
        if (command == "push")
        {
            cin >> x;
            q.push(x);
        }
        else if (command == "pop")
        {
            q.pop();
        }
        else if (command == "max")
        {
            q.max();
        }
        else if (command == "min")
        {
            q.min();
        }
        else if (command == "search")
        {
            cin >> x;
            q.searchX(x);
        }
        else if (command == "quit")
        {
            break;
        }
        else
        {
            cout << "Invalid command" << endl;
        }
    }

    return 0;
}
