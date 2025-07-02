#pragma once
//----------------------- RBTree node ----------------------------

enum RBTColor { Black, Red };

template<class KeyType>
struct  RBTNode
{
	KeyType key;		// значение ноды
	RBTColor color;		// цвет ноды
	RBTNode<KeyType>* left;	// левый ребенок
	RBTNode<KeyType>* right;	// правый ребенок
	RBTNode<KeyType>* parent;	// родитель
	RBTNode(KeyType k, RBTColor c, RBTNode* p, RBTNode* l, RBTNode* r) :	// дефолтный конструктор
		key(k), color(c), parent(p), left(l), right(r) { };
};

//------------------------------------------------------------------

