#define _CRT_SECURE_NO_WARNINGS  
#include <stdio.h>  
#include <locale.h>  
#include <string>  
#include <iomanip>
#include <iostream>
#include <vector>
#include <iostream>
#include <stack>
#include <set>
#include "RBTree.h"

using namespace std;

template<typename T = int>
class MySet {
public:
    RBTree<T>tree;

    // дефолтный конструктор
    MySet() = default;

    // конструктор по заданному вектору чисел
    MySet(vector<int> const &elems) {
        for (auto el : elems) {
            tree.insert(el);
        }
    }

    // конструктор копирования
    MySet(MySet<T>& other) {
        tree.copy(tree, other.tree.root);
    }

    // конструктор переноса
    MySet(MySet<T>&& other) noexcept{
        tree.clear(tree.root);
        tree.copy(tree, other.tree.root);
       /* delete other.tree.root;
        other.tree.root = nullptr;*/
        other.tree.clear(other.tree.root);
    }

    // оператор присваивания
    MySet& operator = (const MySet<T>& other) {
        tree.clear(tree.root);
        tree.copy(tree, other.tree.root);
        return *this;
    }

    // оператор перемещения
    MySet& operator = (const MySet<T>&& other) {
        if (this != &other) {
            tree.clear(tree.root);
            tree.copy(tree, other.tree.root);
            /*delete other.tree.root;
            other.tree.root = nullptr;*/
            other.tree.clear(other.tree.root);
        }
        return *this;
    }

    // вставка в set
    void insert(T elem) {
        this->tree.insert(elem);
    }

    // удаление по ключу
    void erase(T elem) {
        this->tree.remove(elem);
    }

    // поиск 
    std::pair<RBTNode<T>*, bool> find(const T& key) {
        RBTNode<T>* elem = tree.search(tree.root, key);
        if (elem == NULL) {
            return { elem, false };
        }
        return {elem, true};
    }

    // swap
    void swap(MySet<T>& other) {
        MySet<T> tmp = *this;
        *this = other;
        other = tmp;
    }

    // begin()
    RBTNode<T>* begin() {
        return tree.begin();
    }

    // end()
    RBTNode<T>* end() {
        return tree.end();
    }

    // clear() 
    void clear() {
        tree.clear(tree.root);
    }

    int size() {
        return tree.size(tree.root);
    }

    // вывод
    void Print() {
        // 0 - черная вершина
        // 1 - красная вершина
        this->tree.print();
    }

};

template<typename T = int>
void swap(MySet<T>& a, MySet<T>& b) {
    MySet<T> tmp = a;
    a = b;
    b = tmp;
}


int main() {
    setlocale(LC_ALL, "Russian");
    //-----------------------------  ТЕСТЫ ДЛЯ КОНТЕЙНЕРА SET ---------------------------------------------
  
    // тест конструктора по списку чисел
    cout << "Создаем сет по списку чисел:\n";
    vector<int>elems1 = { 1,2,3,4,5 };
    MySet<int> s1(elems1);
    s1.Print();

    vector<int>elems2 = { 6,7,7,1,3 };
    MySet<int> s2(elems2);
    s2.Print();

    // тест метода find
    cout << "\nМетод find:\n";
    cout << "Ищем элемент 1:\n";
    cout << s1.find(1).first->key << endl;
    cout << s1.find(1).second << endl;

    // тест метода swap
    cout << "\nИспользуем swap для 2ух set:\n";
    s1.swap(s2);
    cout << "Так выглядит 1ый set:\n";
    s1.Print();
    cout << "Так выглядит 2ой set:\n";
    s2.Print();

    // тест для begin и end
    cout << "\nТест для begin и end:\n";
    cout << "возвращаем значение по итератору begin:\n";
    cout << s1.begin()->key << endl;
    cout << "возвращаем значение по итератору end:\n";
    cout << s1.end()->key << endl;

    // тест для clear и size
    cout << "\nТест для clear и size:\n";
    cout << "очистим 2ой set:\n";
    s2.clear();
    cout << "вернем число элементов в 1ом set:\n";
    cout << s1.size() << endl;

    // тест для метода erase
    cout << "\nТест для метода erase:\n";
    cout << "удалим элемент по ключу 7:\n";
    s1.erase(7);
    cout << "теперь дерево по которому построен set 1 вышлядит так:\n";
    s1.Print();

    // тест конструктора премещения
    cout << "\nТест конструктора перемещения:\n";
    MySet<int> s3(std::move(s1));
    s3.Print();

    // тест оператора присваивания
    cout << "\nТест оператора присваивания:\n";
    MySet<int> s4 = s3;
    s4.Print();
    //-----------------------------  ТЕСТЫ ДЛЯ КОНТЕЙНЕРА SET ---------------------------------------------

     //-----------------------------    ТЕСТЫ ДЛЯ КЧ ДЕРЕВА   ---------------------------------------------
     // Пока что не стал их писать так как тесты для set и так все методы кч дерева используют

    return 0;
}