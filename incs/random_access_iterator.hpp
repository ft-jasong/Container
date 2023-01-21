#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "iterator.hpp"

namespace ft
{
	template <class T>
	class random_access_iterator
	{
	private:
		T *_current;

	public:
		typedef typename iterator_traits<T *>::iterator_category iterator_category;
		typedef typename iterator_traits<T *>::value_type value_type;
		typedef typename iterator_traits<T *>::difference_type difference_type;
		typedef typename iterator_traits<T *>::pointer pointer;
		typedef typename iterator_traits<T *>::reference reference;

		random_access_iterator() : _current() {}
		random_access_iterator(T *current) : _current(current) {}
		template <typename U>
		random_access_iterator(const random_access_iterator<U> &random_iter) : _current(random_iter.base()) {}
		random_access_iterator &operator=(const random_access_iterator &random_iter)
		{
			if (*this == random_iter)
				return *this;
			_current = random_iter._current;
			return *this;
		}
		virtual ~random_access_iterator() {}
		reference operator*() const
		{
			return *_current;
		}
		random_access_iterator operator+(difference_type n) const { return random_access_iterator(_current + n); }
		random_access_iterator &operator++()
		{
			++_current;
			return *this;
		}
		random_access_iterator operator++(int)
		{
			random_access_iterator tmp = *this;
			++_current;
			return tmp;
		}
		random_access_iterator &operator+=(difference_type n)
		{
			_current += n;
			return *this;
		}
		random_access_iterator operator-(difference_type n) const { return random_access_iterator(_current - n); }
		random_access_iterator &operator--()
		{
			--_current;
			return *this;
		}
		random_access_iterator operator--(int)
		{
			random_access_iterator tmp = *this;
			--_current;
			return tmp;
		}
		random_access_iterator &operator-=(difference_type n)
		{
			_current -= n;
			return *this;
		}
		pointer operator->() const { return _current; }
		reference operator[](difference_type n) const { return _current[n]; }
		pointer base() const { return _current; }
	};

	template <class T1, class T2>
	bool operator==(const random_access_iterator<T1> &lhs,
					const random_access_iterator<T2> &rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <class T1, class T2>
	bool operator!=(const random_access_iterator<T1> &lhs,
					const random_access_iterator<T2> &rhs)
	{
		return lhs.base() != rhs.base();
	}

	template <class T1, class T2>
	bool operator<(const random_access_iterator<T1> &lhs,
				   const random_access_iterator<T2> &rhs)
	{
		return lhs.base() < rhs.base();
	}

	template <class T1, class T2>
	bool operator<=(const random_access_iterator<T1> &lhs,
					const random_access_iterator<T2> &rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template <class T1, class T2>
	bool operator>(const random_access_iterator<T1> &lhs,
				   const random_access_iterator<T2> &rhs)
	{
		return lhs.base() > rhs.base();
	}

	template <class T1, class T2>
	bool operator>=(const random_access_iterator<T1> &lhs,
					const random_access_iterator<T2> &rhs)
	{
		return lhs.base() >= rhs.base();
	}

	template <class T1, class T2>
	random_access_iterator<T1> operator+(T1 n, const random_access_iterator<T2> &random_iter)
	{
		return random_iter + n;
	}

	template <class T1, class T2>
	typename random_access_iterator<T1>::difference_type operator-(const random_access_iterator<T1> &lhs,
																  const random_access_iterator<T2> &rhs)
	{
		return lhs.base() - rhs.base();
	}
}

#endif