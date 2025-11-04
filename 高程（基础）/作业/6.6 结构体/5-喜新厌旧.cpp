#include <iostream>
#include <string>
using namespace std;

struct Book {
    string name;
    string author;
    int pages;
    int lastRead;
};

Book shelf[10];
int bookCount = 0;
int times = 0;

int main() {
    string command;
    while (cin >> command) {
        if (command == "put") {
            string name, author;
            int pages;
            cin >> name >> author >> pages;
            if (bookCount == 10) {
                int oldest = 0;
                for (int i = 1; i < 10; ++i) {
                    if (shelf[i].lastRead < shelf[oldest].lastRead) {
                        oldest = i;
                    }
                }
                for (int i = oldest; i < 9; ++i) {
                    shelf[i] = shelf[i + 1];
                }
                shelf[9] = { name, author, pages, times };
            }
            else {
                shelf[bookCount++] = { name, author, pages, times };
            }
        }
        else if (command == "read") {
            string name;
            cin >> name;
            for (int i = 0; i < bookCount; ++i) {
                if (shelf[i].name == name) {
                    shelf[i].lastRead = times;
                    break;
                }
            }
        }
        else if (command == "quit") {
            break;
        }
        times++;
    }
    //Êä³ö
    for (int i = 0; i < bookCount; ++i) {
        cout  << shelf[i].name << shelf[i].author << shelf[i].pages << endl;
    }
    return 0;
}