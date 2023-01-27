#include <iostream>

#include "utility.hpp"

namespace ft 
{
	template <class Key, class T>
	class Node
	{
		public:
			typedef Key key_type;
			typedef T mapped_type;
			typedef ft::pair<const key_type, mapped_type> value_type;
			typedef Node<Key, T> *node_pointer;
			typedef Node<Key, T> &node_reference;
			// typedef const Node<Key, T> *const_node_pointer; //TODO: 필요함???
			// typedef const Node<Key, T> &const_node_reference;

		private:
			value_type _value;
			node_pointer _left;
			node_pointer _right;
			node_pointer _parent;

		public:
			Node() : _value(), _left(NULL), _right(NULL), _parent(NULL) {}
			Node(const value_type &value) : _value(value), _left(NULL), _right(NULL), _parent(NULL) {}
			Node(const value_type &value, node_pointer left, node_pointer right, node_pointer parent) : _value(value), _left(left), _right(right), _parent(parent) {}
			Node(const Node &node) : _value(node._value), _left(node._left), _right(node._right), _parent(node._parent) {}
			virtual ~Node() {}
			Node &operator=(const Node &node)
			{
				if (*this == node)
					return *this;
				_value = node._value;
				_left = node._left;
				_right = node._right;
				_parent = node._parent;
				return *this;
			}
			value_type &value() { return _value; }
			const value_type &value() const { return _value; }
			node_pointer &left() { return _left; }
			const node_pointer &left() const { return _left; }
			node_pointer &right() { return _right; }
			const node_pointer &right() const { return _right; }
			node_pointer &parent() { return _parent; }
			const node_pointer &parent() const { return _parent; }
	};
	

	template <class Key, class T>
	class BinaryTree
	{
		public:
			typedef Key key_type;
			typedef T mapped_type;
			typedef ft::pair<const key_type, mapped_type> value_type;
			typedef Node<Key, T> *node_pointer;
			typedef Node<Key, T> &node_reference;
			typedef const Node<Key, T> *const_node_pointer;
			typedef const Node<Key, T> &const_node_reference;

		private:
			node_pointer _root;
			size_t _size;

		public:
			BinaryTree() : _root(NULL), _size(0) {}
			BinaryTree(const BinaryTree &tree) : _root(NULL), _size(0)
			{
				*this = tree;
			}
			virtual ~BinaryTree()
			{
				clear();
			}
			BinaryTree &operator=(const BinaryTree &tree)
			{
				if (*this == tree)
					return *this;
				clear();
				_root = copy(tree._root);
				_size = tree._size;
				return *this;
			}

			// TODO: need??
			node_pointer &root() { return _root; }
			const node_pointer &root() const { return _root; }

			size_t &size() { return _size; } // TODO: need??
			const size_t &size() const { return _size; }

			node_pointer copy(const_node_pointer node) // TODO: const_node_pointer??
			{
				if (!node)
					return NULL;
				node_pointer newNode = new Node<Key, T>(node->value());
				newNode->left() = copy(node->left());
				newNode->right() = copy(node->right());
				return newNode;
			}
			void clear()
			{
				clear(_root);
				_root = NULL;
				_size = 0;
			}
			void clear(node_pointer node)
			{
				if (!node)
					return;
				clear(node->left());
				clear(node->right());
				delete node;
			}

			node_pointer find(const key_type &key)
			{
				node_pointer node = _root;
				while (node)
				{
					if (node->value().first == key)
						return node;
					else if (node->value().first < key)
						node = node->right();
					else
						node = node->left();
				}
				return NULL;
			}

			void _insert(node_pointer node, const value_type &value)
			{
				if (!node)
				{
					_root = new Node<Key, T>(value);
					_size++;
					return ;
				}
				if (node->value().first < value.first)
				{
					if (node->right())
						_insert(node->right(), value);
					else
					{
						node->right() = new Node<Key, T>(value);
						node->right()->parent() = node;
						_size++;
					}
				}
				else
				{
					if (node->left())
						_insert(node->left(), value);
					else
					{
						node->left() = new Node<Key, T>(value);
						node->left()->parent() = node;
						_size++;
					}
				}
			}

			void insert(const value_type &value)
			{
				_insert(_root, value);
			}

			void erase(const key_type &key)
			{
				node_pointer node = find(key);
				if (!node)
					return ;
				if (!node->left() && !node->right())
				{
					if (node->parent())
					{
						if (node->parent()->left() == node)
							node->parent()->left() = NULL;
						else
							node->parent()->right() = NULL;
					}
					else
						_root = NULL;
					delete node;
				}
				else if (!node->left() || !node->right())
				{
					node_pointer child = node->left() ? node->left() : node->right();
					if (node->parent())
					{
						if (node->parent()->left() == node)
							node->parent()->left() = child;
						else
							node->parent()->right() = child;
					}
					else
						_root = child;
					child->parent() = node->parent();
					delete node;
				}
				else
				{
					value_type tmp;
					node_pointer successor = node->right();
					while (successor->left())
						successor = successor->left();
					tmp = successor->value();
					erase(tmp.first);
					node->value() = tmp;
				}
				_size--;
			}

			void print() const
			{
				print(_root, 0);
			}
			void print(const_node_pointer node, int depth) const
			{
				if (!node)
					return ;
				print(node->right(), depth + 1);
				for (int i = 0; i < depth; i++)
					std::cout << "   ";
				std::cout << node->value().first << std::endl;
				print(node->left(), depth + 1);
	
			}
	};
};
