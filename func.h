#include <iostream>
#include <queue>
#include <string>
using namespace std;

class Tree
{
	struct Node
	{
	public:
		Node* left, * right;
		int data;

		Node(int data, Node* left = nullptr, Node* right = nullptr)
		{
			this->data = data;
			this->left = left;
			this->right = right;
		}
	};
	Node* root;

	Node* min_elem_ret(Node*& node)
	{
		if (node->left != nullptr)
		{
			min_elem_ret(node->left);
		}
		else
		{
			return node;
		}
	}
	Node* max_elem_ret(Node*& node)
	{
		if (node->right == nullptr)
		{
			return node;
		}
		else
		{
			max_elem_ret(node->right);
		}
	}
	void add_new_elem(Node*& node, int data);
	Node* search_elem(Node*& node, int data)
	{
		if (node == nullptr || node->data == data)
		{
			return node;
		}
		if (data < node->data)
		{
			search_elem(node->left, data);
		}
		else
		{
			search_elem(node->right, data);
		}
	}
	void del_all(Node*& current);
	void preorder(Node* node);
	void inorder(Node* node);
	void postorder(Node* node);
	void print_tree_as_tree(Node* node, int lvl);
	void widthorder(Node* node);
	Node* prev_elem_ret(int data)
	{
		Node* node = root;
		Node* parent = nullptr;
		while (node && node->data != data)
		{
			parent = node;
			if (data < node->data)
			{
				node = node->left;
			}
			else
			{
				node = node->right;
			}
		}
		if (node == nullptr)
		{
			cout << "Нет введённого элемента в дереве" << endl;
			return nullptr;
		}
		if (parent == nullptr)
		{
			cout << "У введённого элемента нет родителя" << endl;
			return nullptr;
		}
		if (parent)
		{
			return parent;
		}
	}
	void next_element(Node* node, int data);

public:
	Tree();
	~Tree();

	void insert(int data) 
	{
		add_new_elem(root, data);
	}

	Node* search(int data)
	{
		return search_elem(root, data);
	}

	void remove(int data);

	void min_elem()
	{
		if (root)
			cout << "Минимальный элемент = " << min_elem_ret(this->root)->data << endl;
		else
			cout << "Дерево пусто" << endl;
	}
	void max_elem()
	{
		if (root)
			cout << "Максимальный элемент = " << max_elem_ret(this->root)->data << endl;
		else
			cout << "Дерево пусто" << endl;
	}

	void Preorder()
	{
		preorder(root);
		cout << endl;
	}
	void Inorder()
	{
		inorder(root);
		cout << endl;
	}
	void Postorder()
	{
		postorder(root);
		cout << endl;
	}
	void Widthorder()
	{
		widthorder(root);
	}

	void prev_elem(int data)
	{
		if (Node* temp = prev_elem_ret(data))
		{
			cout << "Значение родителя " << "числа " << data << " = " << temp->data << endl;
		}
	}
	void next_elem(int data)
	{
		next_element(root, data);
	}

	void Print_tree_as_tree()
	{
		print_tree_as_tree(root, 0);
	}
};

inline void Tree::next_element(Node* node, int data)
{
	if (node==nullptr)
	{
		cout << "такого элемента нет" << endl;
	}
	if (data < node->data)
	{
		next_element(node->left, data);
	}
	if (data > node->data)
	{
		next_element(node->right, data);
	}
	if (node->data == data)
	{
		if (node->left)
			cout << "следующий меньший элемент числа " << data << " = " << node->left->data << endl;
		if (node->right)
			cout << "следующий больший элемент числа " << data << " = " << node->right->data << endl;
		if (!node->left && !node->right)
		{
			cout << "Следующих элементов числа " << data << " нет" << endl;
		}
	}
}

Tree::Tree()
{
	root = nullptr;
}

Tree::~Tree()
{
	this->del_all(this->root);
	this->root = nullptr;
}

inline void Tree::remove(int data)
{
	Node* node = root;
	Node* parent = nullptr;
	while (node && node->data != data)
	{
		parent = node;
		if (data < node->data)
		{
			node = node->left;
		}
		else
		{
			node = node->right;
		}
	}
	if (node == nullptr)
	{
		cout << "такого элемента нет в дереве" << endl;
		return;
	}
	if (node->left == nullptr && node->right == nullptr)
	{
		if (parent->left == node)
			parent->left = nullptr;
		if (parent->right == node)
			parent->right = nullptr;
		delete node;
		return;
	}
	if (node->left == nullptr)
	{
		if (parent->left == node)
			parent->left = node->right;
		if (parent->right == node)
			parent->right = node->right;
		delete node;
		return;
	}
	if (node->right == nullptr)
	{
		if (parent->left == node)
			parent->left = node->left;
		if (parent->right == node)
			parent->right = node->left;
		delete node;
		return;
	}
	if (node->left && node->right)
	{
		Node* temp = min_elem_ret(node->right);
		remove(temp->data);
		if (parent->left == node)
		{
			parent->left = temp;
			temp->left = node->left;
			temp->right = node->right;
		}
		if (parent->right == node)
		{
			parent->right = temp;
			temp->left = node->left;
			temp->right = node->right;
		}
		delete node;
		return;
	}
}

inline void Tree::print_tree_as_tree(Node* node, int lvl)
{
	if (node != nullptr)
	{
		print_tree_as_tree(node->right, lvl+1);
		for (int i = 0; i < lvl; i++)
			cout << "\t";
		cout << "————————" << node->data << endl;
		print_tree_as_tree(node->left, lvl+1);
	}
}

inline void Tree::preorder(Node* node)
{
	if (node != nullptr)
	{
		cout << node->data << "\t";
		preorder(node->left);
		preorder(node->right);
	}
}

inline void Tree::inorder(Node* node)
{
	if (node != nullptr)
	{
		inorder(node->left);
		cout << node->data << "\t";
		inorder(node->right);
	}
}

inline void Tree::postorder(Node* node)
{
	if (node != nullptr)
	{
		postorder(node->left);
		postorder(node->right);
		cout << node->data << "\t";
	}
}

inline void Tree::widthorder(Node* node)
{
	if (node == nullptr) 
		return;
	queue<Node*> q;
	q.push(node);

	while (!q.empty())
	{
		Node* temp = q.front();
		q.pop();
		cout << temp->data << " ";

		if (temp->left != nullptr)
			q.push(temp->left);

		if (temp->right != nullptr)
			q.push(temp->right);
	}
}

inline void Tree::add_new_elem(Node*& node, int data)
{
	if (node == nullptr) 
	{
		node = new Node(data);
	}
	else 
	{
		if (data < node->data) 
		{
			add_new_elem(node->left, data);
		}
		else if (data > node->data) 
		{
			add_new_elem(node->right, data);
		}
		//если data == node->data, то такой ключ уже есть в дереве, поэтому мы ничего не делаем
	}
}

inline void Tree::del_all(Node*& current)
{
	if (current != nullptr)
	{
		del_all(current->left);
		del_all(current->right);
		delete current;
	}
}