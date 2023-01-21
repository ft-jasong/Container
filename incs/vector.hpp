#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "iterator.hpp"
#include "random_access_iterator.hpp"
#include "utility.hpp"
#include <iostream>
namespace ft
{
	template <
		class T,
		class Allocator = std::allocator<T> >
	class vector
	{
	public:
		typedef T value_type;
		typedef Allocator allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef random_access_iterator<const T> const_iterator;
		typedef random_access_iterator<T> iterator;
		typedef reverse_iterator<const_iterator> const_reverse_iterator;
		typedef reverse_iterator<iterator> reverse_iterator;
		typedef typename iterator_traits<iterator>::difference_type difference_type;
		typedef size_t size_type;

	private:
		pointer _data;
		size_type _size;
		size_type _capacity;
		allocator_type _alloc;

	public:
		explicit vector(const allocator_type &alloc = allocator_type()) : _data(NULL), _size(0), _capacity(0), _alloc(alloc) {}
		explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()) : _data(NULL), _size(0), _capacity(0), _alloc(alloc)
		{
			assign(n, val);
		}
		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type()) : _data(NULL), _size(0), _capacity(0), _alloc(alloc)
		{
			assign(first, last);
		}
		vector(const vector &x) : _data(NULL), _size(0), _capacity(0), _alloc(x._alloc)
		{
			assign(x.begin(), x.end());
		}
		~vector()
		{
			clear();
			_alloc.deallocate(_data, _capacity);
		}
		vector &operator=(const vector &x)
		{
			if (this == &x)
				return *this;
			assign(x.begin(), x.end());
			return *this;
		}
		iterator begin() { return iterator(_data); }
		const_iterator begin() const { return const_iterator(_data); }
		iterator end() { return iterator(_data + _size); }
		const_iterator end() const { return const_iterator(_data + _size); }
		reverse_iterator rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
		size_type size() const { return _size; }
		size_type max_size() const { return _alloc.max_size(); }
		void resize(size_type n, value_type val = value_type())
		{
			if (n > _size)
			{
				if (n > _capacity)
					reserve(n);
				for (size_type i = _size; i < n; i++)
					_alloc.construct(_data + i, val);
			}
			else
			{
				for (size_type i = n; i < _size; i++)
					_alloc.destroy(_data + i);
			}
			_size = n;
		}
		size_type capacity() const { return _capacity; }
		bool empty() const { return _size == 0; }
		void reserve(size_type n)
		{
			if (n > _capacity)
			{
				pointer tmp = _alloc.allocate(n);
				for (size_type i = 0; i < _size; i++)
				{
					_alloc.construct(tmp + i, _data[i]);
					_alloc.destroy(_data + i);
				}
				_alloc.deallocate(_data, _capacity);
				_data = tmp;
				_capacity = n;
			}
		}
		reference operator[](size_type n) { return _data[n]; }
		const_reference operator[](size_type n) const { return _data[n]; }
		reference at(size_type n)
		{
			if (n >= _size)
				throw std::out_of_range("vector");
			return _data[n];
		}
		const_reference at(size_type n) const
		{
			if (n >= _size)
				throw std::out_of_range("vector");
			return _data[n];
		}
		reference front() { return _data[0]; }
		const_reference front() const { return _data[0]; }
		reference back() { return _data[_size - 1]; }
		const_reference back() const { return _data[_size - 1]; }
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = NULL)
		{
			clear();
			while (first != last)
			{
				push_back(*first);
				first++;
			}
		}
		void assign(size_type n, const value_type &val)
		{
			clear();
			for (size_type i = 0; i < n; i++)
				push_back(val);
		}
		void push_back(const value_type &val)
		{
			if (_size == _capacity)
				reserve(_capacity == 0 ? 1 : _capacity * 2);
			_alloc.construct(_data + _size, val);
			_size++;
		}
		void pop_back()
		{
			_alloc.destroy(_data + _size - 1);
			_size--;
		}
		iterator insert(iterator position, const value_type &val)
		{
			size_type pos = position - begin();

			insert(position, 1, val);
			return begin() + pos;
		}
		void insert(iterator position, size_type n, const value_type &val)
		{
			size_type pos = position - begin();
			if (_size + n > _capacity)
				reserve(_capacity == 0 ? n : _size + n);
			for (size_type i = _size + n - 1; i >= pos + n; i--)
			{
				_alloc.construct(_data + i, _data[i - n]);
				_alloc.destroy(_data + i - n);
			}
			for (size_type i = pos; i < pos + n; i++)
				_alloc.construct(_data + i, val);
			_size += n;
		}
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = NULL)
		{
			size_type pos = position - begin();
			size_type n = 0;
			for (InputIterator it = first; it != last; it++)
				n++;
			if (_size + n > _capacity)
				reserve(_capacity == 0 ? n : _size + n);
			for (size_type i = _size + n - 1; i >= pos + n; i--)
			{
				_alloc.construct(_data + i, _data[i - n]);
				_alloc.destroy(_data + i - n);
			}
			for (size_type i = pos; i < pos + n; i++)
			{
				_alloc.construct(_data + i, *first);
				first++;
			}
			_size += n;
		}
		iterator erase(iterator position)
		{
			size_type pos = position - begin();
			_alloc.destroy(_data + pos);
			for (size_type i = pos; i < _size - 1; i++)
			{
				_alloc.construct(_data + i, _data[i + 1]);
				_alloc.destroy(_data + i + 1);
			}
			_size--;
			return begin() + pos;
		}
		iterator erase(iterator first, iterator last)
		{
			size_type pos = first - begin();
			size_type n = last - first;
			for (size_type i = pos; i < pos + n; i++)
				_alloc.destroy(_data + i);
			for (size_type i = pos; i < _size - n; i++)
			{
				_alloc.construct(_data + i, _data[i + n]);
				_alloc.destroy(_data + i + n);
			}
			_size -= n;
			return begin() + pos;
		}
		void swap(vector &x)
		{
			pointer tmp_data = _data;
			size_type tmp_size = _size;
			size_type tmp_capacity = _capacity;
			_data = x._data;
			_size = x._size;
			_capacity = x._capacity;
			x._data = tmp_data;
			x._size = tmp_size;
			x._capacity = tmp_capacity;
		}
		void clear()
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(_data + i);
			_size = 0;
		}
		allocator_type get_allocator() const { return _alloc; }
	};

	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		for (size_t i = 0; i < lhs.size(); i++)
		{
			if (lhs[i] != rhs[i])
				return false;
		}
		return true;
	}

	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		size_t i = 0;
		while (i < lhs.size() && i < rhs.size())
		{
			if (lhs[i] < rhs[i])
				return true;
			else if (lhs[i] > rhs[i])
				return false;
			i++;
		}
		if (i == lhs.size() && i != rhs.size())
			return true;
		return false;
	}

	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return rhs < lhs;
	}

	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(lhs < rhs);
	}

	template <class T, class Alloc>
	void swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
	{
		x.swap(y);
	}

}

#endif