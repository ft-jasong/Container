#ifndef MAP_HPP
#define MAP_HPP

#include "utility.hpp"
#include "iterator.hpp"
#include "avl_tree.hpp"
#include "bidirectional_iterator.hpp"
#include <iostream>

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T> > >
	class map
	{
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const key_type, mapped_type> value_type;
		typedef Compare key_compare;
		typedef Allocator allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef bidirectional_iterator<value_type> iterator;
		typedef bidirectional_iterator<const value_type> const_iterator;
		typedef reverse_iterator<const_iterator> const_reverse_iterator;
		typedef reverse_iterator<iterator> reverse_iterator;
		typedef typename iterator_traits<iterator>::difference_type difference_type;
		typedef size_t size_type;

	private:
		struct node
		{
			value_type _data;
			node *_left;
			node *_right;
			node *_parent;
			node(const value_type &data = value_type(), node *left = NULL, node *right = NULL, node *parent = NULL) : _data(data), _left(left), _right(right), _parent(parent) {}
		};
		node *_root;
		size_type _size;
		allocator_type _alloc;
		key_compare _comp;

	public:
		explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _root(NULL), _size(0), _alloc(alloc), _comp(comp) {}
		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _root(NULL), _size(0), _alloc(alloc), _comp(comp)
		{
			insert(first, last);
		}
		map(const map &x) : _root(NULL), _size(0), _alloc(x._alloc), _comp(x._comp)
		{
			insert(x.begin(), x.end());
		}
		~map()
		{
			clear();
		}
		map &operator=(const map &x)
		{
			if (this == &x)
				return *this;
			clear();
			insert(x.begin(), x.end());
			return *this;
		}

		iterator begin()
		{
			return iterator(tree_min(_root));
		}
		const_iterator begin() const
		{
			return const_iterator(tree_min(_root));
		}
		iterator end()
		{
			return iterator(tree_max(_root));
		}
		const_iterator end() const
		{
			return const_iterator(tree_max(_root));
		}
		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}
		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(end());
		}
		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}
		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
		}
		bool empty() const
		{
			return _size == 0;
		}
		size_type size() const
		{
			return _size;
		}
		size_type max_size() const
		{
			return _alloc.max_size();
		}

		mapped_type &operator[](const key_type &k)
		{
			iterator it = find(k);
			if (it == end())
				it = insert(value_type(k, mapped_type())).first;
			return it->second;
		}

		std::pair<iterator, bool> insert(const value_type &val)
		{
			node *new_node = new node(val);
			node *parent = NULL;
			node *tmp = _root;
			while (tmp)
			{
				parent = tmp;
				if (_comp(val.first, tmp->_data.first))
					tmp = tmp->_left;
				else if (_comp(tmp->_data.first, val.first))
					tmp = tmp->_right;
				else
				{
					delete new_node;
					return std::pair<iterator, bool>(iterator(tmp), false);
				}
			}
			new_node->_parent = parent;
			if (!parent)
				_root = new_node;
			else if (_comp(val.first, parent->_data.first))
				parent->_left = new_node;
			else
				parent->_right = new_node;
			++_size;
			return std::pair<iterator, bool>(iterator(new_node), true);
		}
		iterator insert(iterator position, const value_type &val)
		{
			(void)position;
			return insert(val).first;
		}
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			while (first != last)
				insert(*first++);
		}

		void erase(iterator position, iterator last)
		{
			while (position != last)
				erase(position++);
		}
		size_type erase(const key_type &k)
		{
			iterator it = find(k);
			if (it == end())
				return 0;
			erase(it);
			return 1;
		}
		void clear()
		{
			erase(begin(), end());
		}
		iterator find(const key_type &k)
		{
			node *tmp = _root;
			while (tmp)
			{
				if (_comp(k, tmp->_data.first))
					tmp = tmp->_left;
				else if (_comp(tmp->_data.first, k))
					tmp = tmp->_right;
				else
					return iterator(tmp);
			}
			return end();
		}
		const_iterator find(const key_type &k) const
		{
			node *tmp = _root;
			while (tmp)
			{
				if (_comp(k, tmp->_data.first))
					tmp = tmp->_left;
				else if (_comp(tmp->_data.first, k))
					tmp = tmp->_right;
				else
					return const_iterator(tmp);
			}
			return end();
		}

		size_type count(const key_type &k) const
		{
			return find(k) == end() ? 0 : 1;
		}

		iterator lower_bound(const key_type &k)
		{
			iterator it = begin();
			while (it != end() && _comp(it->first, k))
				++it;
			return it;
		}

		const_iterator lower_bound(const key_type &k) const
		{
			const_iterator it = begin();
			while (it != end() && _comp(it->first, k))
				++it;
			return it;
		}

		iterator upper_bound(const key_type &k)
		{
			iterator it = begin();
			while (it != end() && !_comp(k, it->first))
				++it;
			return it;
		}

		const_iterator upper_bound(const key_type &k) const
		{
			const_iterator it = begin();
			while (it != end() && !_comp(k, it->first))
				++it;
			return it;
		}

		std::pair<const_iterator, const_iterator> equal_range(const key_type &k) const
		{
			return std::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
		}

		std::pair<iterator, iterator> equal_range(const key_type &k)
		{
			return std::pair<iterator, iterator>(lower_bound(k), upper_bound(k));
		}

		key_compare key_comp() const
		{
			return _comp;
		}

		value_compare value_comp() const
		{
			return value_compare(_comp);
		}

		void swap(map &x)
		{
			std::swap(_root, x._root);
			std::swap(_size, x._size);
			std::swap(_comp, x._comp);
			std::swap(_alloc, x._alloc);
		}

		template <class K1, class T1, class Compare1, class Alloc1>
		friend bool operator==(const map<K1, T1, Compare1, Alloc1> &lhs, const map<K1, T1, Compare1, Alloc1> &rhs);
		template <class K1, class T1, class Compare1, class Alloc1>
		friend bool operator!=(const map<K1, T1, Compare1, Alloc1> &lhs, const map<K1, T1, Compare1, Alloc1> &rhs);
		template <class K1, class T1, class Compare1, class Alloc1>
		friend bool operator<(const map<K1, T1, Compare1, Alloc1> &lhs, const map<K1, T1, Compare1, Alloc1> &rhs);
		template <class K1, class T1, class Compare1, class Alloc1>
		friend bool operator<=(const map<K1, T1, Compare1, Alloc1> &lhs, const map<K1, T1, Compare1, Alloc1> &rhs);
		template <class K1, class T1, class Compare1, class Alloc1>
		friend bool operator>(const map<K1, T1, Compare1, Alloc1> &lhs, const map<K1, T1, Compare1, Alloc1> &rhs);
		template <class K1, class T1, class Compare1, class Alloc1>
		friend bool operator>=(const map<K1, T1, Compare1, Alloc1> &lhs, const map<K1, T1, Compare1, Alloc1> &rhs);
	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		typename map<Key, T, Compare, Alloc>::const_iterator it1 = lhs.begin();
		typename map<Key, T, Compare, Alloc>::const_iterator it2 = rhs.begin();
		while (it1 != lhs.end())
		{
			if (*it1 != *it2)
				return false;
			++it1;
			++it2;
		}
		return true;
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		typename map<Key, T, Compare, Alloc>::const_iterator it1 = lhs.begin();
		typename map<Key, T, Compare, Alloc>::const_iterator it2 = rhs.begin();
		while (it1 != lhs.end() && it2 != rhs.end())
		{
			if (*it1 < *it2)
				return true;
			else if (*it2 < *it1)
				return false;
			++it1;
			++it2;
		}
		return lhs.size() < rhs.size();
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return !(rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return rhs < lhs;
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return !(lhs < rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	void swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y)
	{
		x.swap(y);
	}
}

#endif