#include "func.h"
#include <stack>

class Btree
{
	struct Node
	{
	public:
		Node* left, * right;
		string data;

		Node(string data, Node* left = nullptr, Node* right = nullptr)
		{
			this->data = data;
			this->left = left;
			this->right = right;
		}
	};
	Node* root;
	string post_notation;
	void preorder(Node* node);
	void inorder(Node* node);
	void postorder(Node* node);
	void del_all(Node*& current);
	void push_to_Tree(Node*& node, string data);
	void push_to_tree(string data) 
	{
		push_to_Tree(root, data);
	}
public:
	Btree();
	~Btree();
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
	void inf_to_post(string str);
	void pre_to_post(string str);
	void post_to_post(string str)
	{
		this->post_notation = str;
	}
	void creat_tree();
};
char is_operation(char c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

inline void Btree::preorder(Node* node)
{
	if (node != nullptr)
	{
		cout << node->data << " ";
		preorder(node->left);
		preorder(node->right);
	}
}

inline void Btree::inorder(Node* node)
{
	if (node != nullptr)
	{
		if (node->left != nullptr)
			cout << "(";
		inorder(node->left);
		cout << node->data;
		inorder(node->right);
		if (node->right != nullptr)
			cout << ")";
	}
}

inline void Btree::postorder(Node* node)
{
	if (node != nullptr)
	{
		postorder(node->left);
		postorder(node->right);
		cout << node->data << " ";
	}
}

inline void Btree::del_all(Node*& current)
{
	if (current != nullptr)
	{
		del_all(current->left);
		del_all(current->right);
		delete current;
	}
}

Btree::Btree()
{
	root = nullptr;
}

Btree::~Btree()
{
	del_all(this->root);
	root = nullptr;
}

inline void Btree::inf_to_post(string str)//inf to post
{
	string res = "";
	stack<char> stck;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '(')
		{
			stck.push(str[i]);
		}
		if (str[i] == ')')
		{
			while (!stck.empty() && stck.top() != '(')
			{
				res.push_back(stck.top());
				res.push_back(' ');
				stck.pop();
			}
			stck.pop();
		}
		if (str[i]=='^')
		{
			while (!stck.empty() && stck.top() == '^')
			{
				res.push_back(stck.top());
				res.push_back(' ');
				stck.pop();
			}
			stck.push(str[i]);
		}
		if (str[i] == '*' || str[i] == '/')
		{
			while(!stck.empty() && (stck.top() == '^' || stck.top() == '*' || stck.top() == '/'))
			{
				res.push_back(stck.top());
				res.push_back(' ');
				stck.pop();
			}
			stck.push(str[i]);
		}
		if (str[i] == '+' || str[i] == '-')
		{
			stck.push(str[i]);
		}
		if (isdigit(str[i]))
		{
			while (isdigit(str[i]))
			{
				res.push_back(str[i]);
				i++;
			}
			res.push_back(' ');
			i--;
		}
	}
	while (!stck.empty())
	{
		res.push_back(stck.top());
		res.push_back(' ');
		stck.pop();
	}
	this->post_notation = res;
}

inline void Btree::pre_to_post(string str)
{
	stack<string> s;
	stack<char> digit;
	// length of expression
	int length = str.length();
	string temp1;

	// reading from right to left
	for (int i = length - 1; i >= 0; i--)
	{
		// check if symbol is operator
		if (is_operation(str[i]))
		{
			// pop two operands from stack
			string op1 = s.top();
			s.pop();
			string op2 = s.top();
			s.pop();

			// concat the operands and operator
			string temp = op1 + ' ' + op2 + ' ' + str[i];

			// Push string temp back to stack
			s.push(temp);
		}

		// if symbol is an operand
		else if (isdigit(str[i]))
		{
			while (isdigit(str[i]))
			{
				digit.push(str[i]);
				i--;
			}
			while (!digit.empty())
			{
				temp1 += digit.top();
				digit.pop();
			}
			i++;
			// push the operand to the stack
			s.push(temp1);
			temp1 = "";
		}
	}

	// stack contains only the Postfix expression
	this->post_notation = s.top();
}

inline void Btree::creat_tree()
{
	string temp;
	stack<char> digit;
	int i = this->post_notation.length();
	while(i)
	{
		i--;
		if (is_operation(post_notation[i]))
		{
			temp += post_notation[i];
			push_to_tree(temp);
		}
		if (isdigit(post_notation[i]))
		{
			while (i >= 0 && isdigit(post_notation[i]))
			{
				digit.push(post_notation[i]);
				i--;
			}
			while (!digit.empty())
			{
				temp += digit.top();
				digit.pop();
			}
			push_to_tree(temp);
			i++;
		}
		temp = "";
	}
}

inline void Btree::push_to_Tree(Node*& node, string data)
{
	if (node == nullptr)
	{
		node = new Node(data);
	}
	else
	{
		if (node->right == nullptr)
		{
			push_to_Tree(node->right, data);
		}
		else if (is_operation(node->right->data[0]))
		{
			if (node->right->left != nullptr && isdigit(node->right->left->data[0]))
			{
				push_to_Tree(node->left, data);
			}
			else
			{
				push_to_Tree(node->right, data);
			}
		}
		else
		{
			push_to_Tree(node->left, data);
		}
	}
}