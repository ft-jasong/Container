#ifndef BIDIRECTIONAL_ITERATOR_HPP
#define BIDIRECTIONAL_ITERATOR_HPP

#include "iterator.hpp"
#include "avl_tree.hpp"

namespace ft
{
	template <class Key, class Value>
	class bidirectional_iterator
	{
	private:
		Node<Key, Value> *_current;

	public:
		typedef typename iterator_traits<Node<Key, Value> *>::iterator_category iterator_category;
		typedef typename iterator_traits<Node<Key, Value> *>::value_type value_type;
		typedef typename iterator_traits<Node<Key, Value> *>::difference_type difference_type;
		typedef typename iterator_traits<Node<Key, Value> *>::pointer pointer;
		typedef typename iterator_traits<Node<Key, Value> *>::reference reference;

		bidirectional_iterator() : _current() {}
		bidirectional_iterator(T *current) : _current(current) {}
		bidirectional_iterator(const bidirectional_iterator &bidirectional_iter) : _current(bidirectional_iter.base()) {}
		bidirectional_iterator &operator=(const bidirectional_iterator &bidirectional_iter)
		{
			if (*this == bidirectional_iter)
				return *this;
			_current = bidirectional_iter._current;
			return *this;
		}
		virtual ~bidirectional_iterator() {}
		reference operator*() const
		{
			return _current->value();
		}

		pointer operator->()
		{
			return &_current->value();
		}

		bidirectional_iterator &operator++()
		{
			_current = _current->next();
			return *this;
		}
		bidirectional_iterator operator++(int)
		{
			bidirectional_iterator tmp = *this;
			_current = _current->next();
			return tmp;
		}
		bidirectional_iterator &operator--()
		{
			_current = _current->prev();
			return *this;
		}
		bidirectional_iterator operator--(int)
		{
			bidirectional_iterator tmp = *this;
			_current = _current->prev();
			return tmp;
		}
		pointer base() const { return _current; }

	};

	template <class Key, class Value>
	bool operator==(const bidirectional_iterator<Key, Value> &lhs, const bidirectional_iterator<Key, Value> &rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <class Key, class Value>
	bool operator!=(const bidirectional_iterator<Key, Value> &lhs, const bidirectional_iterator<Key, Value> &rhs)
	{
		return lhs.base() != rhs.base();
	}
}
#endif
