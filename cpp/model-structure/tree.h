#ifndef __TREE_H__
#define __TREE_H__

#define YANGBEGIN namespace yang {
#define YANGEND }

YANGBEGIN

template<class Key,class Value> struct Node
{
	typedef Node* Node_ptr;

	Node_ptr parent;
	Node_ptr left;
	Node_ptr right;
	Key key;
	Value value;

	Node(Key k =0,Value v =0)
		:key(k),value(v),parent(0),left(0),right(0)
	{
	}
};

template<class Key,class Value> class Tree
{
	typedef Value Value_type;
	typedef Key Key_type;
	typedef Node<Key,Value> Tree_node;

	Tree_node *root;

private:
	void transplant(Tree_node *u,Tree_node *v);
	void _inorder_walk(Tree_node *node);
public:
	Tree()
		:root(0)
	{}
	void inorder_walk();
	Tree_node *iterative_search(Key_type v);
	Tree_node *minimum(Tree_node *root);
	Tree_node *maximum(Tree_node *root);
	Tree_node *successor(Tree_node *node);
	Tree_node *predecessor(Tree_node *node);
	void insert(Tree_node *node);
	void _delete(Tree_node *node);
};

YANGEND

#endif