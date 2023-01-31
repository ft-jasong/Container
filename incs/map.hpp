#ifndef MAP_HPP
#define MAP_HPP

#include "utility.hpp"
#include "iterator.hpp"
#include "avl_tree.hpp"
#include "bidirectional_iterator.hpp"
#include <iostream>

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const Key, T> value_type;
		typedef Compare key_compare;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename allocator_type::difference_type difference_type;
		typedef typename allocator_type::size_type size_type;
		typedef bidirectional_iterator<key_type, mapped_type> iterator;
		typedef bidirectional_iterator<const key_type, mapped_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef typename ft::AvlTree<key_type, mapped_type, key_compare, allocator_type>::node_pointer node_pointer;

	private:
		ft::AvlTree<key_type, mapped_type, key_compare, allocator_type> _tree;
		allocator_type _alloc;

	public:
		explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _tree(comp), _alloc(alloc) {}
		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _tree(comp), _alloc(alloc)
		{
			insert(first, last);
		}
		map(const map &x) : _tree(x._tree), _alloc(x._alloc) {}
		map &operator=(const map &x)
		{
			if (this == &x)
				return *this;
			_tree = x._tree;
			_alloc = x._alloc;
			return *this;
		}
		~map() {}

		class value_compare
		{   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
			friend class map;
			protected:
				Compare comp;
				value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
			public:
				typedef bool result_type;
				typedef value_type first_argument_type;
				typedef value_type second_argument_type;
			bool operator() (const value_type& x, const value_type& y) const
			{
				return comp(x.first, y.first);
			}
		};
		iterator begin()
		{
			return iterator(_tree.begin());
		}
		const_iterator begin() const
		{
			return const_iterator(_tree.begin());
		}
		iterator end()
		{
			return iterator(_tree.end());
		}
		const_iterator end() const
		{
			return const_iterator(_tree.end());
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
			return _tree.empty();
		}
		size_type size() const
		{
			return _tree.size();
		}
		size_type max_size() const
		{
			return _alloc.max_size();
		}
		mapped_type &operator[](const key_type &k)
		{
			iterator it = find(k);
			if (it == end())
				it = insert(ft::make_pair(k, mapped_type())).first;
			return it->second;
		}
		ft::pair<iterator, bool> insert(const value_type &val)
		{
			iterator it = find(val.first);
			if (it == end()) {
				_tree.insert(val);
				return ft::make_pair(iterator(_tree.find(val.first)), true);
			}
			return ft::make_pair(it, false);
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
		void erase(iterator position)
		{
			_tree.erase(position);
		}
		size_type erase(const key_type &k)
		{
			return _tree.erase(k);
		}
		void erase(iterator first, iterator last)
		{
			while (first != last)
				erase(first++);
		}
		void swap(map &x)
		{
			_tree.swap(x._tree);
		}
		void clear()
		{
			_tree.clear();
		}
		key_compare key_comp() const
		{
			return _tree.key_comp();
		}
		value_compare value_comp() const
		{
			return _tree.value_comp();
		}
		iterator find(const key_type &k)
		{
			node_pointer node_ptr = _tree.find(k);
			if (node_ptr == NULL)
				return end();
			return iterator(node_ptr);
		}
		const_iterator find(const key_type &k) const
		{
			node_pointer node_ptr = _tree.find(k);
			if (node_ptr == NULL)
				return end();
			return const_iterator(node_ptr);
		}
		iterator lower_bound(const key_type &k) // TODO: tree lower bound does not exist
		{
			iterator it = begin();
			while (it != end() && key_comp()(it->first, k))
				++it;
			return it;
		}
		const_iterator lower_bound(const key_type &k) const
		{
			iterator it = begin();
			while (it != end() && key_comp()(it->first, k))
				++it;
			return it;
		}
		iterator upper_bound(const key_type &k) // TODO: tree upper bound does not exist
		{
			iterator it = begin();
			std::cout << it->first << std::endl;
			while (it != end() && !key_comp()(k, it->first))
				++it;
			return it;
		}
		const_iterator upper_bound(const key_type &k) const
		{
			iterator it = begin();
			while (it != end() && !key_comp()(k, it->first))
				++it;
			return it;
		}
		size_type count(const key_type& k)
		{
			return _tree.count(k);
		}
		ft::pair<const_iterator, const_iterator> equal_range(const key_type &k) const
		{
			//TODO: upper bound does not exist
			return ft::make_pair(lower_bound(k), upper_bound(k)); 
		}
		ft::pair<iterator, iterator> equal_range(const key_type &k)
		{
			//TODO: upper bound does not exist
			return ft::make_pair(lower_bound(k), upper_bound(k));
		}
		allocator_type get_allocator() const
		{
			return _alloc;
		}
	};
}

#endif