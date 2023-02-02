#include "map.hpp"

#define T1 int
#define T2 int

struct ft_more {
	bool	operator()(const T1 &first, const T1 &second) const {
		return (first > second);
	}
};

int		main(void)
{
	ft::map<T1, T2> mp;

	mp[42] = 1;
	mp[25] = 2;
	mp[80] = 3;
	mp[12] = 4;
	mp[27] = 5;
	mp[90] = 6;

	return (0);
}
