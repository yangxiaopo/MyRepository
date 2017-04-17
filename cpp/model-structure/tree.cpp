#include <iostream>
#include "tree.h"

YANGBEGIN

template<class Key,class Value>
void Tree<Key,Value>::transplant(Tree_node *u,Tree_node *v)
{
	if(u->parent == (Tree_node*)0)
		root = v;
	else if(u == u->parent->left)
		u->parent->left = v;
	else u->parent->right = v;

	if(v != (Tree_node*)0)
		v->parent = u->parent;
}

template<class Key,class Value>
void Tree<Key,Value>::_inorder_walk(Tree_node *node)
{
	if(node != 0)
	{
		_inorder_walk(node->left);
		std::cout << "<" <<node->key << "," << node->value << ">\n";
		_inorder_walk(node->right);
	}
}

template<class Key,class Value>
void Tree<Key,Value>::inorder_walk()
{
	_inorder_walk(root);
}

template<class Key,class Value>
typename Tree<Key,Value>::Tree_node* Tree<Key,Value>::iterative_search(Tree_node *root , Value_type& v)
{
	while(root != 0 || v != root->value)
	{
		if(v < root->value)
			root = root->left;
		else
			root = root->right;
	}
	return root;
}

template<class Key,class Value>
typename Tree<Key,Value>::Tree_node* Tree<Key,Value>::minimum(Tree_node *root)
{
	while(root->left != 0)
		root = root->left;
	return root;
}

template<class Key,class Value>
typename Tree<Key,Value>::Tree_node* Tree<Key,Value>::maximum(Tree_node *root)
{
	while(root->right != 0)
		root = root->right;
	return root;
}

template<class Key,class Value>
typename Tree<Key,Value>::Tree_node* Tree<Key,Value>::successor(Tree_node *node)
{
	if(node->right != 0)
		return minimum(node->right);
	Tree_node *p = node->parent;
	while(p != 0 && node == p->right)
	{
		node = p;
		p = p->parent;
	}
	return p;
}

template<class Key,class Value>
typename Tree<Key,Value>::Tree_node* Tree<Key,Value>::predecessor(Tree_node *node)
{
	if(node->left != 0)
		return maximum(node->left);
	Tree_node *p = node->parent;
	while(p != 0 && node == p->left)
	{
		node = p;
		p = p->parent;
	}
	return p;
}

template<class Key,class Value>
void Tree<Key,Value>::insert(Tree_node *node)
{
	Tree_node *y = (Tree_node*)0;
	Tree_node *x = root;

	while(x != (Tree_node*)0)
	{
		y = x;
		if(node->key < x->key)
			x = x->left;
		else x = x->right;
	}
	node->parent = y;
	if(y == (Tree_node*)0)
		root = node;
	else if(node->key < y->key)
		y->left = node;
	else y->right = node;
}

template<class Key,class Value>
void Tree<Key,Value>::_delete(Tree_node *node)
{
	Tree_node *s;

	if(node->left == (Tree_node*)0)
		transplant(node,node->right);
	else if(node->right == (Tree_node*)0)
		transplant(node,node->left);
	else
	{
		s = minimum(node->right);
		if(s->parent != node)
		{
			transplant(s,s->right);
			s->right = node->right;
			s->right->parent = s;
		}
		transplant(node,s);
		s->left = node->left;
		s->left->parent = s;
	}
	delete node;
}

YANGEND

/*
int main()
{
	int i;
	yang::Tree<int,int> *t =new yang::Tree<int,int>();
	yang::Node<int,int> *a = 0,*b = 0;

	for(i = 0;i < 20;++i)
	{
		a = new yang::Node<int,int>(i,i);
		t->insert(a);
		if(i == 3)
			b = a;
	}
	t->inorder_walk();
	t->_delete(b);
	t->inorder_walk();

	delete t;
}*/