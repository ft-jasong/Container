// measure the time of the ft::STL implementation
#include <iostream>
#include "map.hpp"
#include "stack.hpp"
#include "vector.hpp"
#include <map>
#include <stack>
#include <vector>
#include <sys/time.h>
#include <cstdlib>
#include <unistd.h>

// ANSI colors
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define WHITE "\033[0;37m"
#define RESET "\033[0m"
#define GRAY "\033[1;30m"
#define BOLD "\033[1m"

typedef long long ll;

ll get_time(timeval start, timeval end)
{
	return (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
}

int main(void)
{
	timeval ft_start;
	timeval ft_end;
	timeval std_start;
	timeval std_end;
// vector push_back
	std::cout << YELLOW << BOLD << "------------- vector push_back -------------" << RESET << std::endl;
	/* ft::vector push_back */
	gettimeofday(&ft_start, NULL);
	{
		ft::vector<int> vector_int;
		for (int i = 0; i < 10000; i++)
			vector_int.push_back(i);
	}
	gettimeofday(&ft_end, NULL);
	/* ft::vector output */
	std::cout << BLUE << BOLD << "ft  :\t" << get_time(ft_start, ft_end) << " ms" << RESET << std::endl;

	/* std::vector push_back */
	gettimeofday(&std_start, NULL);
	{
		std::vector<int> std_vector_int;
		for (int i = 0; i < 10000; i++)
			std_vector_int.push_back(i);
	}
	gettimeofday(&std_end, NULL);

	/* std::vector output */
	std::cout << MAGENTA << BOLD << "std :\t" << get_time(std_start, std_end) << " ms" << RESET << std::endl;
	if (get_time(ft_start, ft_end) > 20 * get_time(std_start, std_end))
	{
		std::cout << RED << BOLD << "ft::vector - push_back is " << (double)get_time(ft_start, ft_end) / get_time(std_start, std_end) << " times slow" <<  RESET << std::endl;
		exit(1);
	}
	else
		std::cout << GREEN << BOLD << "ft::vector - push_back is OK" << RESET << std::endl;

// vector pop_back
	std::cout << YELLOW << BOLD << "------------- vector pop_back -------------" << RESET << std::endl;
	/* ft::vector pop_back */
	gettimeofday(&ft_start, NULL);
	{
		ft::vector<int> vector_int(10000, 0);
		for (int i = 0; i < 10000; i++)
			vector_int.pop_back();
	}
	gettimeofday(&ft_end, NULL);
	/* ft::vector output */
	std::cout << BLUE << BOLD << "ft  :\t" << get_time(ft_start, ft_end) << " ms" << RESET << std::endl;

	/* std::vector pop_back */
	gettimeofday(&std_start, NULL);
	{
		std::vector<int> std_vector_int(10000, 0);
		for (int i = 0; i < 10000; i++)
			std_vector_int.pop_back();
	}
	gettimeofday(&std_end, NULL);

	/* std::vector output */
	std::cout << MAGENTA << BOLD << "std :\t" << get_time(std_start, std_end) << " ms" << RESET << std::endl;
	if (get_time(ft_start, ft_end) > 20 * get_time(std_start, std_end))
	{
		std::cout << RED << BOLD << "ft::vector - pop_back is " << (double)get_time(ft_start, ft_end) / get_time(std_start, std_end) << " times slow" <<  RESET << std::endl;
		exit(1);
	}
	else
		std::cout << GREEN << BOLD << "ft::vector - pop_back is OK" << RESET << std::endl;
// vector insert
	std::cout << YELLOW << BOLD << "------------- vector insert -------------" << RESET << std::endl;
	/* ft::vector insert */
	gettimeofday(&ft_start, NULL);
	{
		ft::vector<int> vector_int;
		for (int i = 0; i < 10000; i++)
			vector_int.insert(vector_int.begin(), i);
	}
	gettimeofday(&ft_end, NULL);
	/* ft::vector output */
	std::cout << BLUE << BOLD << "ft  :\t" << get_time(ft_start, ft_end) << " ms" << RESET << std::endl;
	/* std::vector insert */
	gettimeofday(&std_start, NULL);
	{
		std::vector<int> std_vector_int;
		for (int i = 0; i < 10000; i++)
			std_vector_int.insert(std_vector_int.begin(), i);
	}
	gettimeofday(&std_end, NULL);

	/* std::vector output */
	std::cout << MAGENTA << BOLD << "std :\t" << get_time(std_start, std_end) << " ms" << RESET << std::endl;
	if (get_time(ft_start, ft_end) > 20 * get_time(std_start, std_end))
	{
		std::cout << RED << BOLD << "ft::vector - insert is " << (double)get_time(ft_start, ft_end) / get_time(std_start, std_end) << " times slow" <<  RESET << std::endl;
		exit(1);
	}
	else
		std::cout << GREEN << BOLD << "ft::vector - insert is OK" << RESET << std::endl;

// vector erase
	std::cout << YELLOW << BOLD << "------------- vector erase -------------" << RESET << std::endl;
	/* ft::vector erase */
	gettimeofday(&ft_start, NULL);
	{
		ft::vector<int> vector_int(10000, 0);
		for (int i = 0; i < 10000; i++)
			vector_int.erase(vector_int.begin());
	}
	gettimeofday(&ft_end, NULL);
	/* ft::vector output */
	std::cout << BLUE << BOLD << "ft  :\t" << get_time(ft_start, ft_end) << " ms" << RESET << std::endl;
	/* std::vector erase */
	gettimeofday(&std_start, NULL);
	{
		std::vector<int> std_vector_int(10000, 0);
		for (int i = 0; i < 10000; i++)
			std_vector_int.erase(std_vector_int.begin());
	}
	gettimeofday(&std_end, NULL);

	/* std::vector output */
	std::cout << MAGENTA << BOLD << "std :\t" << get_time(std_start, std_end) << " ms" << RESET << std::endl;
	if (get_time(ft_start, ft_end) > 20 * get_time(std_start, std_end))
	{
		std::cout << RED << BOLD << "ft::vector - erase is " << (double)get_time(ft_start, ft_end) / get_time(std_start, std_end) << " times slow" <<  RESET << std::endl;
		exit(1);
	}
	else
		std::cout << GREEN << BOLD << "ft::vector - erase is OK" << RESET << std::endl;

// vector swap
	std::cout << YELLOW << BOLD << "------------- vector swap -------------" << RESET << std::endl;
	/* ft::vector swap */
	gettimeofday(&ft_start, NULL);
	{
		ft::vector<int> vector_int(10000, 0);
		ft::vector<int> vector_int2(10000, 0);
		for (int i = 0; i < 10000; i++)
			vector_int.swap(vector_int2);
	}
	gettimeofday(&ft_end, NULL);
	/* ft::vector output */
	std::cout << BLUE << BOLD << "ft  :\t" << get_time(ft_start, ft_end) << " ms" << RESET << std::endl;
	/* std::vector swap */
	gettimeofday(&std_start, NULL);
	{
		std::vector<int> std_vector_int(10000, 0);
		std::vector<int> std_vector_int2(10000, 0);
		for (int i = 0; i < 10000; i++)
			std_vector_int.swap(std_vector_int2);
	}
	gettimeofday(&std_end, NULL);

	/* std::vector output */
	std::cout << MAGENTA << BOLD << "std :\t" << get_time(std_start, std_end) << " ms" << RESET << std::endl;
	if (get_time(ft_start, ft_end) > 20 * get_time(std_start, std_end))
	{
		std::cout << RED << BOLD << "ft::vector - swap is " << (double)get_time(ft_start, ft_end) / get_time(std_start, std_end) << " times slow" <<  RESET << std::endl;
		exit(1);
	}
	else
		std::cout << GREEN << BOLD << "ft::vector - swap is OK" << RESET << std::endl;

// vector clear
	std::cout << YELLOW << BOLD << "------------- vector clear -------------" << RESET << std::endl;
	/* ft::vector clear */
	gettimeofday(&ft_start, NULL);
	{
		ft::vector<int> vector_int(10000, 0);
		for (int i = 0; i < 10000; i++)
			vector_int.clear();
	}
	gettimeofday(&ft_end, NULL);
	/* ft::vector output */
	std::cout << BLUE << BOLD << "ft  :\t" << get_time(ft_start, ft_end) << " ms" << RESET << std::endl;
	/* std::vector clear */
	gettimeofday(&std_start, NULL);
	{
		std::vector<int> std_vector_int(10000, 0);
		for (int i = 0; i < 10000; i++)
			std_vector_int.clear();
	}
	gettimeofday(&std_end, NULL);

	/* std::vector output */
	std::cout << MAGENTA << BOLD << "std :\t" << get_time(std_start, std_end) << " ms" << RESET << std::endl;
	if (get_time(ft_start, ft_end) > 20 * get_time(std_start, std_end))
	{
		std::cout << RED << BOLD << "ft::vector - clear is " << (double)get_time(ft_start, ft_end) / get_time(std_start, std_end) << " times slow" <<  RESET << std::endl;
		exit(1);
	}
	else
		std::cout << GREEN << BOLD << "ft::vector - clear is OK" << RESET << std::endl;

// vector relational operators
	std::cout << YELLOW << BOLD << "------------- vector relational operators -------------" << RESET << std::endl;
	/* ft::vector relational operators */
	gettimeofday(&ft_start, NULL);
	{
		ft::vector<int> vector_int(10000, 0);
		ft::vector<int> vector_int2(10000, 0);
		for (int i = 0; i < 10000; i++)
			if (vector_int != vector_int2)
			{
				std::cout << RED << BOLD <<  "ft::vector - relational operators is wrong" << RESET << std::endl;
				exit(1);
			}
	}
	gettimeofday(&ft_end, NULL);
	/* ft::vector output */
	std::cout << BLUE << BOLD << "ft  :\t" << get_time(ft_start, ft_end) << " ms" << RESET << std::endl;
	/* std::vector relational operators */
	gettimeofday(&std_start, NULL);
	{
		std::vector<int> std_vector_int(10000, 0);
		std::vector<int> std_vector_int2(10000, 0);
		for (int i = 0; i < 10000; i++)
		{
			if (std_vector_int != std_vector_int2)
			{
				std::cout << RED << BOLD << "std::vector - relational operators is wrong" << RESET << std::endl;
				exit(1);
			}
		}
	}
	gettimeofday(&std_end, NULL);

	/* std::vector output */
	std::cout << MAGENTA << BOLD << "std :\t" << get_time(std_start, std_end) << " ms" << RESET << std::endl;
	if (get_time(ft_start, ft_end) > 20 * get_time(std_start, std_end))
	{
		std::cout << RED << BOLD << "ft::vector - relational operators is " << (double)get_time(ft_start, ft_end) / get_time(std_start, std_end) << " times slow" <<  RESET << std::endl;
		exit(1);
	}
	else
		std::cout << GREEN << BOLD << "ft::vector - relational operators is OK" << RESET << std::endl;
}