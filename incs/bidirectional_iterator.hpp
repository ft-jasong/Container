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
		typedef typename iterator_traits<ft::pair<Key, Value> *>::value_type value_type;
		typedef typename iterator_traits<ft::pair<Key, Value> *>::difference_type difference_type;
		typedef typename iterator_traits<ft::pair<Key, Value> *>::pointer pointer;
		typedef typename iterator_traits<ft::pair<Key, Value> *>::reference reference;
		typedef std::bidirectional_iterator_tag iterator_category;

		bidirectional_iterator() : _current() {}
		bidirectional_iterator(Node<Key, Value> *current) : _current(current) {}
		bidirectional_iterator(const bidirectional_iterator &bidirectional_iter) : _current(bidirectional_iter._current) {}
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

		pointer operator->() const
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
		Node<Key, Value> *base() const { return _current; }

		operator bidirectional_iterator<const Key, const Value>() const
		{
			return (bidirectional_iterator<const Key, const Value>((Node <const Key, const Value> *)(this->_current)));
		}
		// operator bidirectional_iterator<Key, Value>() const
		// {
		// 	return bidirectional_iterator<Key, Value>(const_cast<Node<Key, Value>* >(this->_current));
		// }
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
