#include <iostream>
#include <vector>
#include <memory>
#include <string>
using namespace std;

class Animal {
public:
    Animal(const string& name) : name(name) {}
    virtual void makeSound() const = 0;
    virtual ~Animal() {}
    string getName() const { return name; }
protected:
    string name;
};

class Dog : public Animal {
public:
    /****************** TODO ******************/
    //基类的虚析构函数确保通过基类指针删除派生类对象时，会正确调用析构函数，释放派生类特有的资源
    //如果基类的析构函数不是虚函数，删除基类指针指向的派生类对象时，只会调用基类的析构函数，可导致资源泄漏
    Dog(const string& name) : Animal(name) {}
    void makeSound() const override
    {
        cout << name << " says: Woof! Woof!" << endl;
    }
    /**************** TODO-END ****************/
};

class Cat : public Animal {
public:
    /****************** TODO ******************/
    Cat(const string& name) : Animal(name) {}
    void makeSound() const override 
    {
        cout << name << " says: Meow!" << endl;
    }
    /**************** TODO-END ****************/
};

class Cow : public Animal {
public:
    /****************** TODO ******************/
    Cow(const string& name) : Animal(name) {}
    void makeSound() const override 
    {
        cout << name << " says: Moo!" << endl;
    }
    /**************** TODO-END ****************/
};

int main() {
    vector<unique_ptr<Animal>> animals;

    int choice;
    string animalName;
    cout << "Please enter the type of animal (1 for Dog, 2 for Cat, 3 for Cow). Enter 0 to stop." << endl;
    while (true) {
        cout << "Choice: ";
        cin >> choice;
        if (choice == 0) {
            break;
        }
        cout << "Enter the name of the animal: ";
        cin.ignore();
        getline(cin, animalName);
        switch (choice) {
            /****************** TODO ******************/
        case 1:
            animals.push_back(make_unique<Dog>(animalName));
            break;
        case 2:
            animals.push_back(make_unique<Cat>(animalName));
            break;
        case 3:
            animals.push_back(make_unique<Cow>(animalName));
            break;
            /**************** TODO-END ****************/
        default:
            cout << "Invalid choice." << endl;
        }
    }

    for (const auto& animal : animals) {
        animal->makeSound();
    }

    return 0;
}