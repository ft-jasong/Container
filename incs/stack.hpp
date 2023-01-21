#ifndef STACK_HPP
# define STACK_HPP

#include "vector.hpp"

namespace ft
{
	template <class T, class Container = vector<T> >
	class stack
	{
	public:
		typedef Container container_type;
		typedef Container::value_type value_type;
		typedef Container::size_type size_type;
		typedef Container::reference reference;
		typedef Container::const_reference const_reference;

	protected:
		container_type	_c;
	
	public:
		explicit stack( const Container& cont = Container() ) : _data(NULL) {}
		virtual ~stack();
		stack& operator=( const stack& other )
		{
			if (this == &other)
				return *this;
			_c = other._c;
			return *this;
		}
		stack(const stack &s)
		{
			stack ret;

			ret = s;
			return ret;
		}
	};

}

#endif