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

    // ��������� �����������
    MySet() = default;

    // ����������� �� ��������� ������� �����
    MySet(vector<int> const &elems) {
        for (auto el : elems) {
            tree.insert(el);
        }
    }

    // ����������� �����������
    MySet(MySet<T>& other) {
        tree.copy(tree, other.tree.root);
    }

    // ����������� ��������
    MySet(MySet<T>&& other) noexcept{
        tree.clear(tree.root);
        tree.copy(tree, other.tree.root);
       /* delete other.tree.root;
        other.tree.root = nullptr;*/
        other.tree.clear(other.tree.root);
    }

    // �������� ������������
    MySet& operator = (const MySet<T>& other) {
        tree.clear(tree.root);
        tree.copy(tree, other.tree.root);
        return *this;
    }

    // �������� �����������
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

    // ������� � set
    void insert(T elem) {
        this->tree.insert(elem);
    }

    // �������� �� �����
    void erase(T elem) {
        this->tree.remove(elem);
    }

    // ����� 
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

    // �����
    void Print() {
        // 0 - ������ �������
        // 1 - ������� �������
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
    //-----------------------------  ����� ��� ���������� SET ---------------------------------------------
  
    // ���� ������������ �� ������ �����
    cout << "������� ��� �� ������ �����:\n";
    vector<int>elems1 = { 1,2,3,4,5 };
    MySet<int> s1(elems1);
    s1.Print();

    vector<int>elems2 = { 6,7,7,1,3 };
    MySet<int> s2(elems2);
    s2.Print();

    // ���� ������ find
    cout << "\n����� find:\n";
    cout << "���� ������� 1:\n";
    cout << s1.find(1).first->key << endl;
    cout << s1.find(1).second << endl;

    // ���� ������ swap
    cout << "\n���������� swap ��� 2�� set:\n";
    s1.swap(s2);
    cout << "��� �������� 1�� set:\n";
    s1.Print();
    cout << "��� �������� 2�� set:\n";
    s2.Print();

    // ���� ��� begin � end
    cout << "\n���� ��� begin � end:\n";
    cout << "���������� �������� �� ��������� begin:\n";
    cout << s1.begin()->key << endl;
    cout << "���������� �������� �� ��������� end:\n";
    cout << s1.end()->key << endl;

    // ���� ��� clear � size
    cout << "\n���� ��� clear � size:\n";
    cout << "������� 2�� set:\n";
    s2.clear();
    cout << "������ ����� ��������� � 1�� set:\n";
    cout << s1.size() << endl;

    // ���� ��� ������ erase
    cout << "\n���� ��� ������ erase:\n";
    cout << "������ ������� �� ����� 7:\n";
    s1.erase(7);
    cout << "������ ������ �� �������� �������� set 1 �������� ���:\n";
    s1.Print();

    // ���� ������������ ����������
    cout << "\n���� ������������ �����������:\n";
    MySet<int> s3(std::move(s1));
    s3.Print();

    // ���� ��������� ������������
    cout << "\n���� ��������� ������������:\n";
    MySet<int> s4 = s3;
    s4.Print();
    //-----------------------------  ����� ��� ���������� SET ---------------------------------------------

     //-----------------------------    ����� ��� �� ������   ---------------------------------------------
     // ���� ��� �� ���� �� ������ ��� ��� ����� ��� set � ��� ��� ������ �� ������ ����������

    return 0;
}