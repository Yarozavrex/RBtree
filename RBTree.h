#pragma once

#include "RBTreeNode.h"
#include <iomanip>
#include <iostream>

using namespace std; 


template<class T>
class  RBTree
{
public:
	RBTNode<T>* root;	// корень дерева
	RBTree();			// пустой конструктор
	RBTree(RBTree<T>& node);	// конструтктор копирования
	~RBTree();					// деструктор

	void copy(RBTree<T>& tree, RBTNode<T>* other);  // копирование дерева
	void insert(T key);    // Вставка вершины, ключ это значение ключа, внешний интерфейс
	void remove(T key); // Удаление вершины, внешний интерфейс
	RBTNode<T>* search(T key); // поиск ноды по ключу

	void print();			// вывод дерева внешний интерфейс
	void preTraversal();    // перед обходом дерева внешний интерфейс
	void innerTraversal();    // Основной обход дерева внешний интерфейс
	void postTraversal();    // после обхода дерева внешний интерфейс



	void leftRotate(RBTNode<T>*& root, RBTNode<T>* x);// левый поворот
	void rightRotate(RBTNode<T>*& root, RBTNode<T>* y);// правый поворот

	void insert(RBTNode<T>*& root, RBTNode<T>* node);// Вставка вершины, внутренний интерфейс
	void InsertFixUp(RBTNode<T>*& root, RBTNode<T>* node);	// Корректировка после вставки вершины (чтоб все условия кч соблюдались)
	void clear(RBTNode<T>*& node);		// очистка дерева

	void remove(RBTNode<T>*& root, RBTNode<T>* node);// Удаление вершины, внутренний интерфейс
	void removeFixUp(RBTNode<T>*& root, RBTNode<T>* node, RBTNode<T>* parent); // // Корректировка после удаления вершины

	RBTNode<T>* search(RBTNode<T>* node, T key) const;	// Поиск вершины по ключу

	RBTNode<T>* begin();		// begin для кч дерева (минимальный элемент)
	RBTNode<T>* end();			// end для кч дерева (максимальный элемент)

	void print(RBTNode<T>* node)const;   // вывод дерева внвнутреннийешний интерфейс
	void preTraversal(RBTNode<T>* tree)const;	// перед обходом дерева внутренний интерфейс
	void innerTraversal(RBTNode<T>* tree)const;	// Основной обход дерева внутренний интерфейс
	void postTraversal(RBTNode<T>* tree)const;	 // после обхода дерева внутренний интерфейс

	int size(RBTNode<T>* node)const;		// количество вершин в дереве
};

template<class T>		//Конструктор
RBTree<T>::RBTree() :root(NULL) {
	root = nullptr;
}

template<class T>		//Конструктор копирования
RBTree<T>::RBTree(RBTree<T>& other){
	root = other.root;
	/*root->key = other.root->key;
	root->color = other.root->color;
	root->parent = other.root->parent;
	root->left = other.root->left;
	root->right = other.root->right;*/
}

template<class T>		// Деструктор
RBTree<T>::~RBTree() {
	clear(root);
}

template<class T>		//Левый поворот
void RBTree<T>::leftRotate(RBTNode<T>*& root, RBTNode<T>* x) {
	RBTNode<T>* y = x->right;
	x->right = y->left;
	if (y->left != NULL)
		y->left->parent = x;

	y->parent = x->parent;
	if (x->parent == NULL)
		root = y;
	else {
		if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
};

template<class T>		//Правый поворот
void RBTree<T>::rightRotate(RBTNode<T>*& root, RBTNode<T>* y) {
	RBTNode<T>* x = y->left;
	y->left = x->right;
	if (x->right != NULL)
		x->right->parent = y;

	x->parent = y->parent;
	if (y->parent == NULL)
		root = x;
	else {
		if (y == y->parent->right)
			y->parent->right = x;
		else
			y->parent->left = x;
	}
	x->right = y;
	y->parent = x;
};

template<class T>		// вставка
void RBTree<T>::insert(T key)
{
	RBTNode<T>* z = new RBTNode<T>(key, Red, NULL, NULL, NULL);
	if (search(root, key) == NULL) {
		insert(root, z);

	}
};

template<class T>	
void RBTree<T>::insert(RBTNode<T>*& root, RBTNode<T>* node)
{
	RBTNode<T>* x = root;
	RBTNode<T>* y = NULL;
	while (x != NULL)
	{
		y = x;
		if (node->key > x->key)
			x = x->right;
		else
			x = x->left;
	}
	node->parent = y;
	if (y != NULL)
	{
		if (node->key > y->key)
			y->right = node;
		else
			y->left = node;
	}
	else
		root = node;
	node->color = Red;
	InsertFixUp(root, node);
};
template<class T>
void RBTree<T>::InsertFixUp(RBTNode<T>*& root, RBTNode<T>* node)
{
	RBTNode<T>* parent;
	parent = node->parent;
	while (node != RBTree::root && parent->color == Red)
	{
		RBTNode<T>* gparent = parent->parent;
		if (gparent->left == parent)
		{
			RBTNode<T>* uncle = gparent->right;
			if (uncle != NULL && uncle->color == Red)
			{
				parent->color = Black;
				uncle->color = Black;
				gparent->color = Red;
				node = gparent;
				parent = node->parent;
			}
			else
			{
				if (parent->right == node)
				{
					leftRotate(root, parent);
					swap(node, parent);
				}
				rightRotate(root, gparent);
				gparent->color = Red;
				parent->color = Black;
				break;
			}
		}
		else
		{
			RBTNode<T>* uncle = gparent->left;
			if (uncle != NULL && uncle->color == Red)
			{
				gparent->color = Red;
				parent->color = Black;
				uncle->color = Black;

				node = gparent;
				parent = node->parent;
			}
			else
			{
				if (parent->left == node)
				{
					rightRotate(root, parent);
					swap(parent, node);
				}
				leftRotate(root, gparent);
				parent->color = Black;
				gparent->color = Red;
				break;
			}
		}
	}
	root->color = Black;
}
template<class T>
// Уничтожить красные и черные деревья
void RBTree<T>::clear(RBTNode<T>*& node)
{
	if (node == NULL)
		return;
	clear(node->left);
	clear(node->right);
	delete node;
	node = nullptr;
}

template<class T>
void RBTree<T>::remove(T key)
{
	RBTNode<T>* deletenode = search(root, key);
	if (deletenode != NULL)
		remove(root, deletenode);
}
template<class T>
void RBTree<T>::remove(RBTNode<T>*& root, RBTNode<T>* node)
{
	RBTNode<T>* child, * parent;
	RBTColor color;
	// Левый и правый узлы удаленного узла не пусты (не конечные узлы)
	if (node->left != NULL && node->right != NULL)
	{
		RBTNode<T>* replace = node;
		// Найти узел-преемник (самый нижний левый узел правого поддерева текущего узла)
		replace = node->right;
		while (replace->left != NULL)
		{
			replace = replace->left;
		}
		// Случай, когда удаленный узел не является корневым узлом
		if (node->parent != NULL)
		{
			if (node->parent->left == node)
				node->parent->left = replace;
			else
				node->parent->right = replace;
		}
		// Ситуация с корневым узлом
		else
			root = replace;
		// child - это правильный узел, который заменяет узел и является узлом, который требует последующей корректировки
		// Поскольку замена является преемником, он не может иметь левого дочернего узла
		// Аналогично, у узла-предшественника не может быть правого дочернего узла
		child = replace->right;
		parent = replace->parent;
		color = replace->color;

		// Удаленный узел является родительским узлом замещающего узла (repalce)
		if (parent == node)
			parent = replace;
		else
		{
			// Существование дочернего узла
			if (child != NULL)
				child->parent = parent;
			parent->left = child;

			replace->right = node->right;
			node->right->parent = replace;
		}
		replace->parent = node->parent;
		replace->color = node->color;
		replace->left = node->left;
		node->left->parent = replace;
		if (color == Black)
			removeFixUp(root, child, parent);

		delete node;
		return;
	}
	// Когда в удаленном узле только левый (правый) узел пуст, найдите дочерний узел удаленного узла
	if (node->left != NULL)
		child = node->left;
	else
		child = node->right;

	parent = node->parent;
	color = node->color;
	if (child)
	{
		child->parent = parent;
	}
	// Удаленный узел не является корневым узлом
	if (parent)
	{
		if (node == parent->left)
			parent->left = child;
		else
			parent->right = child;
	}
	// Удаленный узел является корневым узлом
	else
		RBTree::root = child;

	if (color == Black)
	{
		removeFixUp(root, child, parent);
	}
	delete node;

}
template<class T>
void RBTree<T>::removeFixUp(RBTNode<T>*& root, RBTNode<T>* node, RBTNode<T>* parent)
{
	RBTNode<T>* othernode;
	while ((!node) || node->color == Black && node != RBTree::root)
	{
		if (parent->left == node)
		{
			othernode = parent->right;
			if (othernode->color == Red)
			{
				othernode->color = Black;
				parent->color = Red;
				leftRotate(root, parent);
				othernode = parent->right;
			}
			else
			{
				if (!(othernode->right) || othernode->right->color == Black)
				{
					othernode->left->color = Black;
					othernode->color = Red;
					rightRotate(root, othernode);
					othernode = parent->right;
				}
				othernode->color = parent->color;
				parent->color = Black;
				othernode->right->color = Black;
				leftRotate(root, parent);
				node = root;
				break;
			}
		}
		else
		{
			othernode = parent->left;
			if (othernode->color == Red)
			{
				othernode->color = Black;
				parent->color = Red;
				rightRotate(root, parent);
				othernode = parent->left;
			}
			if ((!othernode->left || othernode->left->color == Black) && (!othernode->right || othernode->right->color == Black))
			{
				othernode->color = Red;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if (!(othernode->left) || othernode->left->color == Black)
				{
					othernode->right->color = Black;
					othernode->color = Red;
					leftRotate(root, othernode);
					othernode = parent->left;
				}
				othernode->color = parent->color;
				parent->color = Black;
				othernode->left->color = Black;
				rightRotate(root, parent);
				node = root;
				break;
			}
		}
	}
	if (node)
		node->color = Black;
}

template<class T>
RBTNode<T>* RBTree<T>::search(T key)
{
	return search(root, key);
}
template<class T>
RBTNode<T>* RBTree<T>::search(RBTNode<T>* node, T key) const
{
	if (node == NULL || node->key == key)
		return node;
	else
		if (key > node->key)
			return search(node->right, key);
		else
			return search(node->left, key);
}
template<class T>		// Вывод детальной информации о двоичном дереве
void RBTree<T>::print() {
	if (root == NULL)
		cout << "empty RBtree\n";
	else
		print(root);
}
template<class T>
void RBTree<T>::print(RBTNode<T>* node)const {
	if (node == NULL)
		return;
	if (node->parent == NULL)
		cout << node->key << "(" << node->color << ") is root" << endl;
	else if (node->parent->left == node)
	{
		cout << node->key << "(" << node->color << ") is " << node->parent->key << "'s " << "left child" << endl;
	}
	else
	{
		cout << node->key << "(" << node->color << ") is " << node->parent->key << "'s " << "right child" << endl;
	}
	print(node->left);
	print(node->right);
}
template<class T>		// Предзаказ обхода дерева РБ
void RBTree<T>::preTraversal() {
	if (root == NULL)
		cout << "empty RBtree\n";
	else
		preTraversal(root);
};
template<class T>
void RBTree<T>::preTraversal(RBTNode<T>* tree)const {
	if (tree != NULL) {
		cout << tree->key << " ";
		preTraversal(tree->left);
		preTraversal(tree->right);
	}
}
template<class T>		// Обход дерева RB
void RBTree<T>::innerTraversal() {
	if (root == NULL)
		cout << "empty RBtree\n";
	else
		innerTraversal(root);
};
template<class T>
void RBTree<T>::innerTraversal(RBTNode<T>* tree)const {
	if (tree != NULL) {
		innerTraversal(tree->left);
		cout << tree->key << " ";
		innerTraversal(tree->right);
	}
}
template<class T>      // После обхода дерева RB
void RBTree<T>::postTraversal() {
	if (root == NULL)
		cout << "empty RBtree\n";
	else
		postTraversal(root);
};
template<class T>
void RBTree<T>::postTraversal(RBTNode<T>* tree)const {
	if (tree != NULL) {
		postTraversal(tree->left);
		postTraversal(tree->right);
		cout << tree->key << " ";
	}
}

template<class T>
void RBTree<T>::copy(RBTree<T>& tree, RBTNode<T>* node) {
	if (node == NULL) {
		return;
	}
	tree.insert(node->key);
	copy(tree, node->left);
	copy(tree, node->right);
}

template<class T>
RBTNode<T>* RBTree<T>::begin() {
	RBTNode<T>* node = root;
	while (node->left != NULL) {
		node = node->left;
	}
	return node;
}

template<class T>
RBTNode<T>* RBTree<T>::end() {
	RBTNode<T>* node = root;
	while (node->right != NULL) {
		node = node->right;
	}
	return node;
}

template<class T>
int RBTree<T>::size(RBTNode<T>* node) const{
	if (node == NULL) return 0;
	if (node->left == NULL && node->right == NULL) {
		return 1;
	}
	return size(node->left) + size(node->right) + 1;
}