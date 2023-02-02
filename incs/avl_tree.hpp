#ifndef AVL_TREE_HPP
# define AVL_TREE_HPP

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
			typedef ft::pair<key_type, mapped_type> value_type;
			typedef Node<Key, T> *node_pointer;
			typedef Node<Key, T> &node_reference;
			// typedef const Node<Key, T> *const_node_pointer; //TODO: 필요함???
			// typedef const Node<Key, T> &const_node_reference;

		private:
			value_type _value;
			node_pointer _left;
			node_pointer _right;
			node_pointer _parent;
			int _height;

		public:
			Node() : _left(NULL), _right(NULL), _parent(NULL), _height(0) {}
			Node(const value_type &value) : _value(value), _left(NULL), _right(NULL), _parent(NULL), _height(0) {}
			Node(const Node &node) : _value(node._value), _left(NULL), _right(NULL), _parent(NULL), _height(0)
			{
				*this = node;
			}
			virtual ~Node() {}
			Node &operator=(const Node &node)
			{
				if (this == &node)
					return *this;
				_value = node._value;
				_left = node._left;
				_right = node._right;
				_parent = node._parent;
				_height = node._height;
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
			int &height() { return _height; }

			int getBalanceFactor() const
			{
				int leftHeight = _left ? _left->height() : 0;
				int rightHeight = _right ? _right->height() : 0;
				return leftHeight - rightHeight;
			}

			node_pointer next()
			{
				if (_right)
				{
					node_pointer node = _right;
					while (node->left())
						node = node->left();
					return node;
				}
				else
				{
					node_pointer node = this;
					while (node->parent() && node->parent()->right() == node)
						node = node->parent();
					node = node->parent();
					if (!node)
						throw std::out_of_range("out of range");
					return node;
				}
			}

			node_pointer prev()
			{
				if (_left)
				{
					node_pointer node = _left;
					while (node->right())
						node = node->right();
					return node;
				}
				else
				{
					node_pointer node = this;
					while (node->parent() && node->parent()->left() == node)
						node = node->parent();
					node = node->parent();
					if (!node)
						throw std::out_of_range("out of range");
					return node;
				}
			}
	};
	

	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<Key, T> > >
	class AvlTree
	{
		public:
			typedef Key key_type;
			typedef T mapped_type;
			typedef ft::pair<key_type, mapped_type> value_type;
			typedef Node<Key, T> *node_pointer;
			typedef Node<Key, T> &node_reference;
			typedef const Node<Key, T> *const_node_pointer;
			typedef const Node<Key, T> &const_node_reference;
			typedef Compare key_compare;
			typedef Allocator allocator_type;

		private:
			node_pointer _root;
			size_t _size;
			key_compare _compare;
			allocator_type _alloc;
			node_pointer _end;

		public:
			// AvlTree() : _root(NULL), _size(0) {}
			// Not good copy constructor
			// AvlTree(const AvlTree &tree) : _root(NULL), _size(0), _compare(tree._compare), _alloc(tree._alloc), _end(tree._end)
			// {
			// 	*this = tree;
			// }
			// AvlTree(const key_compare &compare) : _root(NULL), _size(0), _compare(compare) {}
			AvlTree(const key_compare &compare = key_compare(), const allocator_type &alloc = allocator_type()) : _root(NULL), _size(0), _compare(compare), _alloc(alloc)
			{
				_end = new Node<Key, T>();
			}
			virtual ~AvlTree()
			{
				clear();
				delete _end;
			}
			AvlTree &operator=(const AvlTree &tree)
			{
				if (this == &tree)
					return *this;
				clear();
				_compare = tree._compare;
				_alloc = tree._alloc;
				_end = tree._end;
				_size = tree._size;
				_root = copy(tree._root);
				return *this;
			}

			key_compare &key_comp() { return _compare; }
			const key_compare &key_comp() const { return _compare; }

			// TODO: need??
			node_pointer &root() { return _root; }
			const node_pointer &root() const { return _root; }

			size_t &size() { return _size; } // TODO: need??
			const size_t &size() const { return _size; }

			node_pointer copy(const_node_pointer node)// TODO: const_node_pointer??
			{
				if (!node)
					return NULL;
				node_pointer newNode = new Node<Key, T>(node->value());
				newNode->left() = copy(node->left());
				if (newNode->left())
					newNode->left()->parent() = newNode;
				newNode->right() = copy(node->right());
				if (newNode->right())
					newNode->right()->parent() = newNode;
				return newNode;
			}

			// node_pointer _copy(const_node_pointer node) // TODO: const_node_pointer??
			// {
			// 	if (!node)
			// 		return NULL;
			// 	node_pointer newNode = new Node<Key, T>(node->value());
			// 	newNode->left() = copy(node->left());
			// 	if (newNode->left())
			// 		newNode->left()->parent() = newNode;
			// 	newNode->right() = copy(node->right());
			// 	if (newNode->right())
			// 		newNode->right()->parent() = newNode;
			// 	return newNode;
			// }
			void clear()
			{
				while (!empty())
					erase(begin()->value().first);
			}
			node_pointer find(const key_type &key) const
			{
				node_pointer node = _root;
				while (node && node != _end)
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

			void insert(const value_type &value)
			{
				if (_end->parent())
				{
					_end->parent()->right() = NULL;
					_end->parent() = NULL;
				}
				_insert(_root, value);
				_size++;
				node_pointer node = _root;
				while (node->right())
					node = node->right();
				_end->parent() = node;
				node->right() = _end;
			}

			void erase(const key_type &key)
			{
				if (_end->parent())
				{
					_end->parent()->right() = NULL;
					_end->parent() = NULL;
				}
				_erase(key);
				node_pointer node = _root;
				while (node && node->right())
					node = node->right();
				_end->parent() = node;
				if (node)
					node->right() = _end;
			}

			// TODO: _erase 재귀 remind
			void _erase(const key_type &key)
			{
				node_pointer node = find(key);
				if (!node)
					return ;
				node_pointer parent = node->parent();
				if (!node->left() && !node->right()) // 자식 아무것도 없는 놈
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
					_size--;
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
					_size--;
				}
				else // 자식 둘 다 있을 때
				{
					value_type tmp;
					node_pointer successor = node->right();
					while (successor->left())
						successor = successor->left();
					tmp = successor->value();
					_erase(tmp.first);
					node->value() = tmp;
				}
				_rebalance(parent);
				_update_height(_root);
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


			void _rotate_right(node_pointer node)
			{
				node_pointer left = node->left();
				node->left() = left->right();
				if (left->right())
					left->right()->parent() = node;
				left->parent() = node->parent();
				if (!node->parent())
					_root = left;
				else if (node == node->parent()->left())
					node->parent()->left() = left;
				else
					node->parent()->right() = left;
				left->right() = node;
				node->parent() = left;
			}

			void _rotate_left(node_pointer node)
			{
				node_pointer right = node->right();
				node->right() = right->left();
				if (right->left())
					right->left()->parent() = node;
				right->parent() = node->parent();
				if (!node->parent())
					_root = right;
				else if (node == node->parent()->left())
					node->parent()->left() = right;
				else
					node->parent()->right() = right;
				right->left() = node;
				node->parent() = right;
			}

			void _rebalance(node_pointer node)
			{
				while (node)
				{
					if (node->getBalanceFactor() == 2)
					{
						if (node->left()->getBalanceFactor() == -1)
							_rotate_left(node->left());
						_rotate_right(node);	
					}
					else if (node->getBalanceFactor() == -2)
					{
						if (node->right()->getBalanceFactor() == 1)
							_rotate_right(node->right());
						_rotate_left(node);
					}
					_update_height(node);
					node = node->parent();
				}
			}

			void _insert(node_pointer node, const value_type &value)
			{
				if (!node)
				{
					_root = new Node<Key, T>(value);
					return ;
				}
				if (!Compare()(value.first, node->value().first))
				{
					if (node->right())
						_insert(node->right(), value);
					else
					{
						node->right() = new Node<Key, T>(value);
						node->right()->parent() = node;
						_rebalance(node);
						_update_height(_root);
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
						_rebalance(node);
						_update_height(_root);
					}
				}
			}

			void _update_height(node_pointer root)
			{
				if (!root)
					return ;
				_update_height(root->left());
				_update_height(root->right());
				root->height() = std::max(root->left() ? root->left()->height() : 0, root->right() ? root->right()->height() : 0) + 1;
			}

			node_pointer begin() const
			{
				node_pointer node = _root;
				if (!node)
					return (_end);
				while (node->left())
					node = node->left();
				return node;
			}

			node_pointer end() const
			{
				// if (size() == 0)
				// 	return (_root);
				return _end;
			}

			bool empty() const
			{
				return (size() == 0);
			}

			void swap(AvlTree &x)
			{
				node_pointer tmp = _root;
				_root = x._root;
				x._root = tmp;
				node_pointer tmp2 = _end;
				_end = x._end;
				x._end = tmp2;
				size_t tmp3 = _size;
				_size = x._size;
				x._size = tmp3;
				key_compare tmp4 = _compare;
				_compare = x._compare;
				x._compare = tmp4;
				allocator_type tmp5 = _alloc;
				_alloc = x._alloc;
				x._alloc = tmp5;
			}
	};
};

#endif