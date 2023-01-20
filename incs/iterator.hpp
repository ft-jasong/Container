#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iterator>
#include <type_traits>
#include <cstddef>

namespace ft
{
	template <class Category, class T, class Distance = ptrdiff_t,
			  class Pointer = T *, class Reference = T &>
	struct iterator
	{
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
		typedef Category iterator_category;
	};

	template <class Iterator> // iterator 자체가 들어오는 경우
	class iterator_traits
	{
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};
	template <class T>
	class iterator_traits<T *> // pointer가 들어오는 경우
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef std::random_access_iterator_tag iterator_category;
	};
	template <class T>
	class iterator_traits<const T *>
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef const T *pointer;
		typedef const T &reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	// Reverse Iterator
	template <class Iterator>
	class reverse_iterator
	{
	protected:
		Iterator _current;

	public:
		typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
		typedef typename iterator_traits<Iterator>::value_type value_type;
		typedef typename iterator_traits<Iterator>::difference_type difference_type;
		typedef typename iterator_traits<Iterator>::pointer pointer;
		typedef typename iterator_traits<Iterator>::reference reference;

		reverse_iterator() : _current() {}
		explicit reverse_iterator(Iterator x) : _current(x) {}
		template <class Iter>
		reverse_iterator(const reverse_iterator<Iter> &rev_it) : _current(rev_it.base()) {}
		Iterator base() const { return _current; }
		reference operator*() const
		{
			Iterator tmp = _current;
			return *--tmp;
		}
		reverse_iterator operator+(difference_type n) const { return reverse_iterator(_current - n); }
		reverse_iterator &operator++()
		{
			--_current;
			return *this;
		}
		reverse_iterator operator++(int)
		{
			reverse_iterator tmp = *this;
			--_current;
			return tmp;
		}
		reverse_iterator &operator+=(difference_type n)
		{
			_current -= n;
			return *this;
		}
		reverse_iterator operator-(difference_type n) const { return reverse_iterator(_current + n); }
		reverse_iterator &operator--()
		{
			++_current;
			return *this;
		}
		reverse_iterator operator--(int)
		{
			reverse_iterator tmp = *this;
			++_current;
			return tmp;
		}
		reverse_iterator &operator-=(difference_type n)
		{
			_current += n;
			return *this;
		}
		pointer operator->() const { return &(operator*()); }
		reference operator[](difference_type n) const { return *(*this + n); }
	};

	template <class Iterator>
	bool operator==(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <class Iterator>
	bool operator!=(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs)
	{
		return lhs.base() != rhs.base();
	}

	template <class Iterator>
	bool operator<(const reverse_iterator<Iterator> &lhs,
				   const reverse_iterator<Iterator> &rhs)
	{
		return lhs.base() > rhs.base();
	}

	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs)
	{
		return lhs.base() >= rhs.base();
	}

	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator> &lhs,
				   const reverse_iterator<Iterator> &rhs)
	{
		return lhs.base() < rhs.base();
	}

	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n,
										 const reverse_iterator<Iterator> &rev_it)
	{
		return reverse_iterator<Iterator>(rev_it.base() - n);
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator> &lhs,
																   const reverse_iterator<Iterator> &rhs)
	{
		return rhs.base() - lhs.base();
	}

}

#endif